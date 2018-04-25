To test the program, use 

"make check1"
to run on a multi-thread test on the program

"make check"
to run on t-test1 with forking

commented the "#define TEST_FORK 1" in t-test1 to tested on non-forking per-core test

Per core Arena Implemetation:
Each thread will have a id by a global counter, Fist thread will initialize all the arenas
based on the number of cores. Then each thread will be bound to a specific arena number,
Then they will lock the arena to get permission to use it.

Support forking:
use pthread_atfork(prepare, afterfork, afterfork);

in prepare() we lock all public locks, in afterfork() we unlock all public locks
this will prevent the deaklock problem in forking when another thread is lock some mutex.



