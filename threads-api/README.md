# Questions
### 1. Does it point to the right lines of code? What other information does it give you?
Yes, it shows lines 8 and 15 as conflicting, which are both accesses to the balance variable.

It also shows when and where which threads are created.

### 2. What does `helgrind` report in each of these cases?
1. remove one of the lines: nothing
2. add a lock to one of the lines: data race occurs
3. add a lock to both lines: nothing

### 3. Can you see the problem?
If thread `p1` locks `m1` at about the same time `p2` locks `m2`, both thread now try to lock the other lock, but cant, and are therefore stuck.

### 4. What does `helgrind` report?
`Thread #3: lock order "0x404060 before 0x4040A0" violated`

### 5. Does it have the same problem? Should `helgrind` be reporting the same error? What does this tell you about tools like `helgrind`?
No, since this now uses a global lock `g` before messing with `m1` or `m2`, the threads now never access `m1` or `m2` at the same time, therefore the problem should be resolved.

Helgrind however still reports this issue. My guess is these tools just look at what the code could do, based on observed, known patterns and report that.

### 6. Why is this code inefficient?
Like the example in the last chapter, the main thread just does nothing until the worker thread ran. This can take a while until the scheduler decides to run the thread.

### 7. What does `helgrind` report? Is the code correct?
`helgrind` reports a data race since the main thread and the worker thread access `done` simultaneously. But since one of these accesses is a continuous read, this should not matter.

### 8. Why is this code preferred to the previous version? Is it correctness, performance, or both?
Both

### 9. `helgrind` that bic
reports nuttin


# Overview

In this homework, you'll use a real tool on Linux to find problems in
multi-threaded code. The tool is called `helgrind` (available as part of the
valgrind suite of debugging tools).

See `http://valgrind.org/docs/manual/hg-manual.htm` for details about
the tool, including how to download and install it (if it's not
already on your Linux system).

You'll then look at a number of multi-threaded C programs to see how you can
use the tool to debug problematic threaded code.

First things first: download and install `valgrind` and the related `helgrind` tool. 

Then, type `make` to build all the different programs. Examine the `Makefile`
for more details on how that works.

Then, you have a few different C programs to look at:
- `main-race.c`: A simple race condition
- `main-deadlock.c`: A simple deadlock
- `main-deadlock-global.c`: A solution to the deadlock problem
- `main-signal.c`: A simple child/parent signaling example
- `main-signal-cv.c`: A more efficient signaling via condition variables
- `common_threads.h`: Header file with wrappers to make code check errors and be more readable

With these programs, you can now answer the questions in the textbook.




