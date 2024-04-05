# Questions
1. What happenes when dereferencing a pointer that is not initialized?
    - When dereferencing a pointer that is not initialized, the program will crash. This is because the pointer is pointing to a random memory location that is not allocated to the program.
2. What does `gdb` show when dereferencing a pointer that is not initialized?
    - When dereferencing a pointer that is not initialized, `gdb` will show the following error message: 
```
Program received signal SIGSEGV, Segmentation fault.
0x0000000000401150 in main () at null.c:8
8           printf("The value of *ptr is : %d\t\n", *ptr);
```
3. What does valgrinds output mean?
    - The following error message means that the program is trying to access a memory location that is not allocated to the program.
```
Access not within mapped region at address 0x0
    at 0x401150: main (null.c:8)
```
4. What happenes when forgetting to `free` `malloc`ed memory?
    - gdb showes nothing unusual.
    - valgrind shows the following error message meaning that the program has a memory leak:
```
LEAK SUMMARY:
    definitely lost: 4 bytes in 1 blocks
```
5. What happens when accessing an array out of bounds?
    - the program runs normally
    - gdb shows nothing unusual
    - valgrind shows the following error message:
```
Invalid write of size 4
    at 0x401170: main (null.c:9)
 Address 0x484280F is 0 bytes after a block of size 400 alloc'd
    at 0x484280F: malloc (vg_replace_malloc.c:442)
    by 0x401157: main (null.c:6)
```
6. What happens when accessing data that has been free'd?
    - the program runs normally
    - gdb does not complain
    - valgrind shows following error
```
Invalid write of size 4
   at 0x40117C: main (null.c:11)
 Address 0x4a43108 is 200 bytes inside a block of size 400 free'd
   at 0x4845B2C: free (vg_replace_malloc.c:985)
   by 0x401167: main (null.c:8)
 Block was alloc'd at
   at 0x484280F: malloc (vg_replace_malloc.c:442)
   by 0x401157: main (null.c:6)
```
7. What happenes if free is called in the middle of the array?
    - The program complies, but gcc gives following warning:
```
null.c: In function ‘main’:
null.c:8:5: warning: ‘free’ called on pointer ‘array’ with nonzero offset 200 [-Wfree-nonheap-object]
    8 |     free(&array[50]);
      |     ^~~~~~~~~~~~~~~~
null.c:6:18: note: returned from ‘malloc’
    6 |     int *array = malloc(100*sizeof(int));
      |                  ^~~~~~~~~~~~~~~~~~~~~~~
```
- running the program gives:
```
free(): invalid pointer
Aborted (core dumped)
``` 
