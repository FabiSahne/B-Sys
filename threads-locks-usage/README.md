# Tasks
## 1. What is the smallest interval `gettimeofday()` can measure?
Microseconds.

The `rdtsc` instruction is not accurate, since the clock frequency varies.

## 2. Measure the time it takes to increment the counter, with a varying number of threads.
NuOfThreads | Time in us
---:|---:
1 | 184
2 | 202
4 | 301
8 | 400
16 | 712
32 | 1735
64 | 2292
128 | 4735

## 3. 