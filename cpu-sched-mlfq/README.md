# Questions

1. 2 random jobs, 2 queues, no IO
- `./mlfq.py -s 0 -M 0 -j 2 -n 2`
  - Job 0 starts at 0, runs for 84
  - Job 1 starts at 0, runs for 42
    - Job 0 runs for 10 at priority 1
    - Job 1 runs for 10 at priority 1
    - Job 0 runs for 10 at priority 0
    - Job 1 runs for 10 at priority 0
      - repeat last to steps 6 times
    - Job 0 runs for 10, then Job 1 runs for 2 at priority 0
    - Job 0 runs for another 43
  - Job 0: response 0, turnaround 126
  - Job 1: response 10, turnaround 92
  - Avg: response 5, turnaround 109\
- `./mlfq.py -s 1 -M 0 -j 2 -n 2`
  - Job 0 starts at 0, runs for 14
  - Job 1 starts at 0, runs for 76
    - Job 0 runs for 10 at priority 1
    - Job 1 runs for 10 at priority 1
    - Job 0 runs for 4 at prio 0, then Job 1 runs for 10 at priority 0
    - Job 1 runs for another 56
  - Job 0: response 0, turnaround 24
  - Job 1: response 10, turnaround 90
  - Avg: response 5, turnaround 57
2. repeat all the examples
- Figure 8.2
  - `./mlfq.py -l 0,200,0`
- Figure 8.3 (left)
  - `./mlfq.py -l 0,180,0:100,20,0`
- Figure 8.3 (right)
  - `./mlfq.py -l 0,180,0:50,20,1 -a 2`
- Figure 8.4 (left)
  - `./mlfq.py -l 0,180,0:100,50,5:100,50,5 -a 10`
- Figure 8.4 (right)
  - `./mlfq.py -l 0,180,0:100,50,5:100,50,5 -a 10 -B 100`
- Figure 8.5 (left)
  - `./mlfq.py -l 0,180,0:100,100,9 -S`
- Figure 8.5 (right)
  - `./mlfq.py -l 0,180,0:100,100,9`
- Figure 8.6
  - `./mlfq.py -l 0,150,0:0,150,0 -Q 10,20,40 -a 2`
3. How to configure, so MLFQ is the same as RR
  - by having only one queue
4. Craft a workload that will result in a job abusing the old rules 4a and 4b so that it will have 99% of the CPU time
  - `./mlfq.py -l 0,200,0:100,100,9 -S -i 0`
5. How often to boost so that a long running job has at least 5% of the CPU time
  - I guess every 8ms
6. ¯\\\_(ツ)_/¯