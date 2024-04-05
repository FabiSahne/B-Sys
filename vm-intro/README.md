# Questions

1. Read `free` manual.
2. Use `free`.
    - I have 15773 MB total.
    - Depending on what programs are running, and how many Firefox tabs are open, I have between 3000 MB and 10000 MB used and between 11000 MB and 4000 MB available.
    - These numbers match my intuition (though I was shocked how much Firefox uses with about 20\~25 tabs opened).
    - Additionaly I have 8191 MB of swap memory from which about 1700 MB is used.
3. Write `memory-user.c`.
4. Use `memory-user` and see changing memory usage in `free`.
    - These memory usages change about how I expect them to, it's just hard to pinpoint how much the `memory-user` is using exactly, since the numbers reported by `free` are constantly changing.
    - Trying to allocate more memory than is available, causes the terminal to crash after about 10 sec. Tried with `./memory-user 20000`, which was kind of scary.
5. Read `pmap` manual.
6. Use `pmap` with different programs.
7. Use `pmap -X` with different programs. What do I see?
    - see `pmap-X-*.txt`
    - Many many different libraries are being shown in these memory maps.
8. Use `pmap -X` with `memory-user` and different amounts of memory allocated.
    - see `pmap-X-memory-⟨mem in mb⟩.txt`
    - `pmap`s output does more or less match my expectations. One can see the allocated array right under the `[heap]` label with always 4 KB more memory allocated than requested. One can also see the linker library `ld-linux-x86-64.so` and the C standard library `libc.so`.
