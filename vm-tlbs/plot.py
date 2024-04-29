#!/usr/bin/env python
import matplotlib.pyplot as plt # type: ignore


# read data from times.txt
with open('times.csv', 'r') as f:
    lines = f.readlines()

# extract data as (iteration, time) pairs
times = []
iterations = []
for line in lines:
    iteration, time = line.split(',')
    times.append(float(time))
    iterations.append(int(iteration))

# plot data with log x scale
plt.plot(iterations, times, 'go-')
plt.xlabel('Number Of Pages')
plt.ylabel('Time per Acces (ns)')
plt.xscale('log')

plt.show()
