# Philosophers
Dining philosophers problem using multithreading. This project is part of the school 42 cursus.

# Usage
### Running Philosophers
You can compile by running `make` command and then execute with `./philo`

### Principle
There are `nb_philo` philosophers sit at a round table. There is a large bowl of spaghetti in the middle.

Each philosopher has a fork. A philosopher needs two forks to eat.

A philosopher can only take the fork on his right and the fork on his left.

When a philosopher has two forks, he eats `time_to_eat` ms.

When a philosopher is done eating, he sleeps `time_to_sleep` ms.

When a philosopher is done thinking, he starts thinking.

If a philosopher did not eat `time_to_die` ms after his last meal, he dies.

The death of a philosopher has to be announced in less than 10ms after he dies.

### Goal of the project
The goal of this project is to correctly use mutexs so philosophers eat when they need and take the correct forks.

You need to make sure each philosopher eat and they exchange their fork so no one dies of starvation.

Each action of a philosopher has to be displayed with the timestamp.

### Arguments

Example : `./philo 5 800 200 300 2`

`5` : Number of philosophers

`800` : Time for a philosopher to die (in ms)

`200` : Time for a philosopher to eat (in ms)

`300` : Time for a philosopher to sleep (in ms)

`2` : Number of times each philosopher must eat (optional)

#### Output

![Output](https://i.imgur.com/YPppyqY.png)

`0 1 has taken a fork`

`0` : Current timestamp (in ms)

`1` : Index of the philosopher

`has taken a fork` : Action the philosopher just did

Each philosopher ate 2 times.

`./philo  1 800 200 200`

#### Output

![Output](https://i.imgur.com/L6Etg1X.png)

Philosopher 1 died after 800ms since there is only one fork and he can't eat.
