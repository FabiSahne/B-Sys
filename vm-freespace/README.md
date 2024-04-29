# Questions
#### 1. Run with flags `-n 10 -H 0 -p BEST -s 0` and predict the free list
```
ptr[0] = malloc(3);
  --> [addr: 1003, len 97]

free(ptr[0]);
  --> [addr: 1000, len 3][addr: 1003, len 97]

prt[1] - malloc(5);
  --> [addr: 1000, len 3][addr: 1008, len 92]

free(ptr[1]);
  --> [addr: 1000, len 3][addr: 1003, len 5][addr: 1008, len 92]

ptr[2] = malloc(8);
  --> [addr: 1000, len 3][addr:1003, len 5][addr: 1016, len 84]

free(ptr[2]);
  --> [addr: 1000, len 3][addr: 1003, len 5][addr: 1008, len 8][addr: 1016, len 84]

ptr[3] = malloc(8);
  -> [addr: 1000, len 3][addr:1003, len 5][addr: 1016, len 84]

free(ptr[3]);
  --> [addr: 1000, len 3][addr: 1003, len 5][addr: 1008, len 8][addr: 1016, len 84]

ptr[4] = malloc(2);
  --> [addr: 1002, len 1][addr: 1003, len 5][addr: 1008, len 8][addr: 1016, len 84]

ptr[5] = malloc(7);
  --> [addr: 1002, len 1][addr: 1003, len 5][addr: 1015, len 1][addr: 1016, len 84]
```

### 2. What happenes when using a WORST fit policy
The allocated areas get assined in the largest, in this case last, free area.

### 3. What about FIRST
In this case nothing changes since the first fitting free area ist also the best.
But since the allocator doesn't have to traverse the whole list when allocating, and just returns the first fitting area, it is faster.

### 4. Use the different orderings `ADDRSORT` `SIZESORT+` and `SIZESORT-` and see how the policy and list orderings change
The allocations themselves dont change, only how the freelist itself is saved. With `SIZESORT-` the list is reversed from `ADDRSORT` or `SIZESORT+`

### 5. Use 1000 allocatins. What happenes to larger allocation requests over time? Run with and without coalescing. Does ordering matter?
When coalescing, the freelist stays very small (around 1 to 5 elements, rarely up to 8) while without coalescing, the freelist continually grows non stop up to 35 elements in this case. When not coalescing and using `SIZESORT+` a lot more allocations fail, then with other orderings.

### 6. What happenes when you change the percent allocated fraction `-P` to higher than 50?
Whithout coalescing, the allocations quickly fail even though theoretically the heap had enough free memory. And with coalescing it just delays the enevitable, as the heap still fills, though more effectively now.

### 7. How can you fragmentate the freelist as much as possible.
Request many many small aloocations, and then free only every second one.


---
# Overview

This program, malloc.py, allows you to see how a simple memory allocator
works. Here are the options that you have at your disposal:

```
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -S HEAPSIZE, --size=HEAPSIZE
                        size of the heap
  -b BASEADDR, --baseAddr=BASEADDR
                        base address of heap
  -H HEADERSIZE, --headerSize=HEADERSIZE
                        size of the header
  -a ALIGNMENT, --alignment=ALIGNMENT
                        align allocated units to size; -1->no align
  -p POLICY, --policy=POLICY
                        list search (BEST, WORST, FIRST)
  -l ORDER, --listOrder=ORDER
                        list order (ADDRSORT, SIZESORT+, SIZESORT-, INSERT-FRONT, INSERT-BACK)
  -C, --coalesce        coalesce the free list?
  -n OPSNUM, --numOps=OPSNUM
                        number of random ops to generate
  -r OPSRANGE, --range=OPSRANGE
                        max alloc size
  -P OPSPALLOC, --percentAlloc=OPSPALLOC
                        percent of ops that are allocs
  -A OPSLIST, --allocList=OPSLIST
                        instead of random, list of ops (+10,-0,etc)
  -c, --compute         compute answers for me
```

One way to use it is to have the program generate some random allocation/free
operations and for you to see if you can figure out what the free list would
look like, as well as the success or failure of each operation. 

Here is a simple example:

```
prompt> ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 

ptr[0] = Alloc(3)  returned ?
List?

Free(ptr[0]) returned ?
List?

ptr[1] = Alloc(5)  returned ?
List?

Free(ptr[1]) returned ?
List?

ptr[2] = Alloc(8)  returned ?
List?
```

In this example, we specify a heap of size 100 bytes (-S 100), starting at
address 1000 (-b 1000). We specify an additional 4 bytes of header per
allocated block (-H 4), and make sure each allocated space rounds up to the
nearest 4-byte free chunk in size (-a 4). We specify that the free list be
kept ordered by address (increasing). Finally, we specify a "best fit"
free-list searching policy (-p BEST), and ask for 5 random operations to be
generated (-n 5). The results of running this are above; your job is to figure
out what each allocation/free operation returns, as well as the state of the
free list after each operation.

Here we look at the results by using the -c option.

```
prompt> ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c

ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

Free(ptr[0]) returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:92 ]

ptr[1] = Alloc(5)  returned 1012 (searched 2 elements)
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1020 sz:80 ]

Free(ptr[1]) returned 0
Free List [ Size 3 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:12 ] [ addr:1020 sz:80 ]

ptr[2] = Alloc(8)  returned 1012 (searched 3 elements)
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1020 sz:80 ]

As you can see, the first allocation operation (an allocation) returns the
following information:

ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]
```

Because the initial state of the free list is just one large element, it is
easy to guess that the Alloc(3) request will succeed. Further, it will just
return the first chunk of memory and make the remainder into a free list. The
pointer returned will be just beyond the header (address:1004), and the
allocated space is rounded up to 4 bytes, leaving the free list with 92 bytes
starting at 1008. 

The next operation is a Free, of "ptr[0]" which is what stores the results of
the previous allocation request. As you can expect, this free will succeed
(thus returning "0"), and the free list now looks a little more complicated:

```
Free(ptr[0]) returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:92 ]
```

Indeed, because we are NOT coalescing the free list, we now have two elements
on it, the first being 8 bytes large and holding the just-returned space, and
the second being the 92-byte chunk. 

We can indeed turn on coalescing via the -C flag, and the result is:

```
prompt> ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c -C
ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

Free(ptr[0]) returned 0
Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

ptr[1] = Alloc(5)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1012 sz:88 ]

Free(ptr[1]) returned 0
Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

ptr[2] = Alloc(8)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1012 sz:88 ]
```

You can see that when the Free operations take place, the free list is
coalesced as expected.

There are some other interesting options to explore:

* `-p BEST` or `-p WORST` or `-p FIRST`: This option lets you use these three different strategies to look for a chunk of memory to use during an allocation request 
* `-l ADDRSORT` or `-l SIZESORT+` or `-l SIZESORT-` or `-l INSERT-FRONT` or `-l INSERT-BACK`: This option lets you keep the free list in a particular order, say sorted by address of the free chunk, size of free chunk (either increasing with a + or decreasing with a -), or simply returning free chunks to the front (INSERT-FRONT) or back (INSERT-BACK) of the free list.
* `-A list_of_ops`: This option lets you specify an exact series of requests instead of randomly-generated ones. For example, running with the flag "-A +10,+10,+10,-0,-2" will allocate three chunks of size 10 bytes (plus header), and then free the first one ("-0") and then free the third one ("-2"). What will the free list look like then?

Those are the basics. Use the questions from the book chapter to explore more,
or create new and interesting questions yourself to better understand how
allocators function.





  

  
