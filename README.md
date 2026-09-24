# 🍝 Philosophers

> **A concurrent simulation of the Dining Philosophers problem in C, using POSIX threads and mutexes to coordinate shared resources while avoiding deadlocks and data races.**

*This project was created as part of the 42 curriculum.*

Philosophers explores the fundamentals of **concurrent programming**: multiple threads execute independently while competing for shared resources and modifying shared state.

Each philosopher runs in its own thread and repeatedly cycles through:

```text
eat → sleep → think → repeat
```

To eat, a philosopher must acquire two shared forks. Each fork is protected by a `pthread_mutex_t`, requiring careful synchronization to prevent **deadlocks, race conditions and starvation** while maintaining accurate timing.

---

# 🧠 The Problem

The Dining Philosophers problem is a classic concurrency problem originally formulated by Edsger Dijkstra.

Imagine several philosophers sitting around a circular table:

```text
                   Philosopher 1
                        ●
                    F1 / \ F2

          Philosopher 5 ●   ● Philosopher 2
                      F5     F3

              Philosopher 4 ●───● Philosopher 3
                           F4
```

There is one fork between every pair of philosophers.

Each philosopher alternates between:

```text
💭 Thinking
     │
     ▼
🍴 Acquiring two forks
     │
     ▼
🍝 Eating
     │
     ▼
😴 Sleeping
     │
     └──────────────▶ repeat
```

A philosopher requires **both adjacent forks** to eat.

If every philosopher acquires one fork and waits for the second, the entire program can stop making progress:

```text
P1 holds F1 → waits for F2
P2 holds F2 → waits for F3
P3 holds F3 → waits for F4
P4 holds F4 → waits for F5
P5 holds F5 → waits for F1

                 DEADLOCK
```

The challenge is therefore not simply creating threads. It is coordinating them safely under timing constraints.

---

# ✨ Features

- one POSIX thread per philosopher
- one mutex-protected fork per philosopher
- synchronized access to shared simulation state
- asymmetric fork acquisition
- deadlock avoidance
- staggered philosopher startup
- special handling for odd/even philosopher counts
- starvation/death detection
- dedicated monitoring thread
- optional meal-count termination
- synchronized console output
- millisecond timing with `gettimeofday()`
- interruptible sleep implementation
- single-philosopher edge-case handling
- argument and integer-range validation
- mutex and thread cleanup
- GitHub Actions CI

---

# 🏗️ Architecture

The simulation separates philosopher behavior from global supervision.

```text
                         main()
                           │
                           ▼
                  Parse & Validate Args
                           │
                           ▼
                Initialize Shared State
                           │
               ┌───────────┴───────────┐
               │                       │
               ▼                       ▼
        Philosopher Threads      Monitoring Thread
               │                       │
       ┌───────┼────────┐              │
       ▼       ▼        ▼              │
      Eat    Sleep    Think            │
       │                               │
       ▼                               ▼
   Fork Mutexes                Check Last Meal
                               Check Meal Count
                               Detect Death
                                      │
                                      ▼
                              Stop Simulation
```

Each philosopher thread controls its own routine while sharing synchronization state with the rest of the simulation.

The monitoring thread independently observes the philosophers and determines when the simulation must terminate.

---

# 🧵 Thread Model

Each philosopher is represented by a structure containing its thread and synchronization state.

Conceptually:

```text
Philosopher
│
├── philosopher ID
├── pthread ID
├── fork mutex
├── last meal timestamp
├── number of meals eaten
├── meal-state mutex
└── shared simulation parameters
```

The program creates:

```text
N philosophers
      │
      ▼
N pthreads
      +
1 monitoring pthread
```

Once all philosopher threads have been created, a shared start flag releases them into the simulation.

This prevents early-created threads from beginning significantly before later threads have been initialized.

---

# 🍴 Forks as Shared Resources

Every philosopher owns one fork represented by a mutex:

```c
pthread_mutex_t fork_mutex;
```

A philosopher's two required forks are:

```text
left fork  → its own fork mutex
right fork → neighboring philosopher's fork mutex
```

Because the table is circular, philosopher `1` receives the final philosopher's fork as its second adjacent resource.

Conceptually:

```text
P1 ─ F1 ─ P2 ─ F2 ─ P3 ─ F3 ─ P4
│                              │
└────────────── F4 ────────────┘
```

A fork can only be held by one philosopher at a time because access is controlled by `pthread_mutex_lock()` and `pthread_mutex_unlock()`.

---

# 🔒 Deadlock Avoidance

A naive implementation might make every philosopher acquire forks in the same order:

```text
lock left fork
lock right fork
```

This creates the possibility of circular waiting.

Philosophers avoids this by changing the acquisition order depending on philosopher ID:

```text
Odd philosopher
    │
    ├── lock left
    └── lock right

Even philosopher
    │
    ├── lock right
    └── lock left
```

Conceptually:

```text
P1: left  → right
P2: right → left
P3: left  → right
P4: right → left
```

This breaks the uniform resource-acquisition pattern that can produce a circular wait.

Forks are released in the corresponding order after eating.

---

# ⚙️ Scheduling the First Meal

Avoiding deadlock does not automatically produce good scheduling.

If every philosopher immediately competes for forks when the threads start, contention can be unnecessarily high.

The implementation therefore staggers the first meal.

For an even number of philosophers:

```text
Odd IDs   → begin first
Even IDs  → delayed slightly
```

For an odd number of philosophers, the final philosopher receives an additional delay.

Conceptually:

```text
time ───────────────────────────────▶

P1  ███ eat
P2       ███ eat
P3  ███ eat
P4       ███ eat
P5              ███ eat
```

This intentionally desynchronizes competing threads and improves fork availability.

---

# 💭 Eat → Sleep → Think

After initialization, every philosopher executes the same state machine:

```text
       ┌─────────────┐
       │             │
       ▼             │
   ┌───────┐         │
   │  EAT  │         │
   └───┬───┘         │
       │             │
       ▼             │
   ┌───────┐         │
   │ SLEEP │         │
   └───┬───┘         │
       │             │
       ▼             │
   ┌───────┐         │
   │ THINK │─────────┘
   └───────┘
```

Before performing each state, the thread checks whether the simulation has been stopped.

This allows philosopher threads to terminate cleanly after a death or after the optional meal target has been reached.

---

# 🍝 Eating

Eating requires exclusive ownership of two forks.

The process is:

```text
Acquire first fork
        │
        ▼
Acquire second fork
        │
        ▼
Update last meal time
        │
        ▼
Increment meal count
        │
        ▼
Eat for time_to_eat
        │
        ▼
Release both forks
```

The philosopher's `last_meal_time` and `times_eaten` values are protected by their own mutex because they are accessed concurrently by both:

```text
philosopher thread
        +
monitoring thread
```

Without this protection, reading and updating those values would introduce data races.

---

# 👁️ Monitoring Thread

The program uses a dedicated thread to monitor the entire simulation.

```text
                Monitoring Thread
                       │
                       ▼
              Philosopher 1 state
                       │
                       ▼
              Philosopher 2 state
                       │
                       ▼
                     ...
                       │
                       ▼
              Philosopher N state
```

For each philosopher, it calculates:

```text
current_time - last_meal_time
```

If the result exceeds `time_to_die`, the philosopher is considered dead.

The monitor then:

```text
print death
     │
     ▼
set stop flag
     │
     ▼
all philosopher threads terminate
```

The monitor also tracks the optional meal target.

If every philosopher has eaten the required number of times, it stops the simulation cleanly.

---

# 🛡️ Protecting Shared State

Several pieces of data can be accessed concurrently.

The implementation uses separate mutexes for different responsibilities:

```text
fork_mutex
    │
    └── protects ownership of a fork

last_meal_time_and_times_eaten_mutex
    │
    └── protects philosopher meal state

stop_sim_mutex
    │
    └── protects global termination flag

begin_to_eat_mutex
    │
    └── protects synchronized simulation start

print_mutex
    │
    └── serializes terminal output
```

Using different mutexes for independent resources avoids unnecessarily placing the entire program behind one global lock.

---

# 🖨️ Synchronized Output

Multiple threads may attempt to print simultaneously.

Without synchronization, output could become interleaved:

```text
123 2 is ea124 3 has taken a fting
```

The program protects output with a dedicated mutex:

```text
lock print_mutex
      │
      ▼
print timestamp + philosopher + state
      │
      ▼
unlock print_mutex
```

This keeps each event message atomic from the user's perspective.

---

# ⏱️ Timing

Timing is central to the project.

The simulation tracks time using:

```c
gettimeofday()
```

and converts elapsed time into milliseconds.

The monitor uses those timestamps to determine how long each philosopher has gone without beginning another meal.

---

# 💤 Interruptible Sleep

Calling one long `usleep()` can make a worker slow to react when another philosopher dies.

Instead, the implementation provides a segmented sleep mechanism.

Conceptually:

```text
desired sleep duration
        │
        ▼
sleep briefly
        │
        ▼
check stop flag
        │
        ├── stopped → return immediately
        │
        ▼
check elapsed time
        │
        ├── finished → return
        │
        └── continue
```

This lets sleeping philosopher threads periodically observe the shared termination state rather than remaining blocked for the entire requested duration.

The same mechanism is also reused for startup staggering and think delays.

---

# ⚖️ Odd vs. Even Philosopher Counts

An odd number of philosophers creates a less symmetric scheduling pattern.

For example:

```text
5 philosophers
5 forks
```

cannot be divided into perfectly alternating pairs.

The implementation accounts for this by adjusting:

- initial meal ordering;
- startup delays;
- think timing.

For odd philosopher counts, the think phase can introduce an additional delay based on the relationship between `time_to_eat` and `time_to_sleep`.

The goal is to prevent philosophers from repeatedly returning to fork acquisition at exactly the same time.

---

# ☝️ Single Philosopher Edge Case

One philosopher creates a special case:

```text
Philosopher
    │
    ▼
1 available fork
    │
    ▼
needs 2 forks
    │
    ▼
cannot eat
```

The implementation handles this separately.

The philosopher takes the only available fork and waits until the monitoring logic detects starvation.

This avoids incorrectly attempting to lock the same fork as two independent resources.

---

# 🛑 Simulation Termination

The simulation can end in two ways.

### A philosopher dies

```text
time since last meal > time_to_die
```

The monitor reports the death and sets the shared stop flag.

### Everyone has eaten enough

When the optional argument is supplied:

```text
number_of_times_each_philosopher_must_eat
```

the monitor tracks each philosopher's meal count.

Once every philosopher reaches the target, the simulation terminates without a death.

---

# 🧹 Thread & Mutex Cleanup

After the simulation ends, the main thread waits for the worker threads:

```c
pthread_join(...)
```

The program then destroys initialized mutexes and releases allocated philosopher structures.

This includes cleanup for:

```text
fork mutexes
meal-state mutexes
print mutex
simulation-state mutexes
allocated philosopher data
```

Error paths during initialization also destroy resources that were already successfully created.

---

# 🔄 Simulation Lifecycle

The full program flow can be summarized as:

```text
                 ./philo ...
                      │
                      ▼
             Validate Arguments
                      │
                      ▼
             Initialize Parameters
                      │
                      ▼
        Initialize Philosophers + Mutexes
                      │
                      ▼
          Create Philosopher Threads
                      │
                      ▼
             Release Start Barrier
                      │
              ┌───────┴─────────┐
              ▼                 ▼
      Philosopher Loops      Monitor
              │                 │
       Eat/Sleep/Think      Death checks
              │             Meal checks
              │                 │
              └────────┬────────┘
                       ▼
                Stop Simulation
                       │
                       ▼
                  Join Threads
                       │
                       ▼
                 Destroy Mutexes
                       │
                       ▼
                    Free
```

---

# ✍️ Build & Usage

## Compile

```bash
cd philo
make
```

This builds:

```text
philo
```

with:

```text
-Wall -Wextra -Werror -pthread
```

---

## Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are expressed in **milliseconds**.

For example:

```bash
./philo 5 800 200 200
```

runs five philosophers with:

```text
time_to_die   = 800 ms
time_to_eat   = 200 ms
time_to_sleep = 200 ms
```

The optional fifth argument specifies how many times every philosopher must eat before the simulation terminates:

```bash
./philo 5 800 200 200 7
```

---

# 🖥️ Output

During execution, the simulation reports philosopher actions:

```text
timestamp philosopher_id action
```

For example:

```text
1757000000000 1 has taken a fork
1757000000000 1 has taken a fork
1757000000000 1 is eating
1757000000200 1 is sleeping
1757000000400 1 is thinking
```

Possible states include:

```text
has taken a fork
is eating
is sleeping
is thinking
died
```

Output is protected by a mutex so multiple philosopher threads cannot corrupt each other's messages.

---

# 🏗️ Project Structure

```text
philosophers/
│
├── .github/
│   └── workflows/
│       └── CI build / Norminette checks
│
└── philo/
    │
    ├── includes/
    │   └── philo.h
    │
    ├── srcs/
    │   ├── main.c
    │   ├── parse.c
    │   ├── init.c
    │   ├── start_routine.c
    │   ├── routines.c
    │   ├── routine_eat_actions.c
    │   ├── routine_utils.c
    │   ├── monitoring_thread.c
    │   ├── time_utils.c
    │   └── utils.c
    │
    └── Makefile
```

---

# 🧠 Engineering Challenges

### 🔒 Avoiding Deadlocks

Multiple threads need two shared resources simultaneously.

Changing fork-acquisition order between odd and even philosophers breaks the simple circular-wait pattern.

### 🏎️ Reducing Contention

Correct synchronization alone does not guarantee good scheduling.

Staggering philosopher startup and accounting for odd/even table sizes reduces unnecessary simultaneous competition for forks.

### 🧵 Avoiding Data Races

The monitor reads state that philosopher threads modify.

Meal timestamps, meal counts, termination state and output therefore require explicit synchronization.

### ⏱️ Timing Under Concurrency

The program needs sufficiently accurate timing while many threads are simultaneously sleeping, waiting on mutexes and being scheduled by the operating system.

### 🛑 Responsive Termination

A philosopher should not remain inside a long sleep after the simulation has already ended.

Segmented sleeps allow threads to periodically check the termination condition.

### ☝️ Handling Edge Cases

The one-philosopher case behaves fundamentally differently because acquiring two distinct forks is impossible.

It requires explicit handling rather than relying on the normal multi-philosopher routine.

---

# 🎯 What I Learned

This project provided practical experience with concepts that are difficult to understand from sequential programs alone:

### 🧵 Concurrency

- POSIX threads
- thread creation and joining
- independent execution
- scheduling and timing
- shared memory between threads

### 🔒 Synchronization

- mutexes
- critical sections
- shared-resource ownership
- race-condition prevention
- deadlock avoidance
- lock granularity

### ⚙️ Systems Programming

- `pthread_create`
- `pthread_join`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`
- `gettimeofday`
- `usleep`
- memory/resource cleanup

Most importantly, the project demonstrates that concurrent correctness is not only about protecting memory.

The **order in which resources are acquired, the timing of competing threads, and the visibility of shared state** all influence whether a concurrent system continues making progress.

---

# 🤖 Use of AI

AI tools were used during the project as a **learning and documentation aid**, primarily for:

- explanations of unfamiliar concurrency concepts;
- helping clarify threads, mutexes and synchronization behavior;
- improving understanding of deadlocks, race conditions and timing issues;
- discussing approaches to testing concurrent behavior;
- generating and structuring project documentation, including this README.

The synchronization strategy, implementation, debugging, testing and technical decisions were carried out as part of the project work.

---

# 👨‍💻 Author

**Mi Zhou (mzhou / miouz)**

*Philosophers — 42 School*
