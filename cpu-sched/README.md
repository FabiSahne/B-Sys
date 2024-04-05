# Questions

1. Same length Jobs:
    - `./scheduler -p FIFO -l 200,200,200`:
      - Response Time = (0+200+400)/3 = 200
      - Turnaround Time = (200+400+600)/3 = 400
    - `./scheduler -p SJF -l 200,200,200`:
      - Response Time = 200
      - Turnaround Time = 400
2. Different length Jobs:
    - `./scheduler -p FIFO -l 100,200,300`:
      - Response Time = (0+100+300)/3 = 133
      - Turnaround Time = (100+300+600)/3 = 333
    - `./scheduler -p SJF -l 100,200,300`:
      - Response Time = 133
      - Turnaround Time = 333
3. Round Robin (time sclice = 1):
    - `./scheduler -p RR -l 200,200,200`:
      - Response Time = (0+1+2)/3 = 1
      - Turnaround Time = 600
    - `./scheduler -p RR -l 100,200,300`:
      - Response Time = (0+1+2)/3 = 1
      - Turnaround Time = (300+500+600)/3 = 466
4. SJF and FIFO will have the same turnaround and response times if the jobs are already sorted by time, or are the same length.
5. Only if the quantum length equals the job length do RR and SJF deliver the same response times.
6. The response time for longer jobs will increase
    ```
    > ./scheduler -p SJF -l 1,2,3
      Average -- Response: 1.33
    > ./scheduler -p SJF -l 2,4,6
      Average -- Response: 2,67
    > ./scheduler -p SJF -l 3,6,9
      Average -- Response: 4
    ```
7. The response time for longer quantum lengths will increase:
    - Response Time = $q\cdot(0+1+2+...+(N-1))/N = \frac{q}{N}\cdot\displaystyle\sum_{i=0}^{n-1}n$
