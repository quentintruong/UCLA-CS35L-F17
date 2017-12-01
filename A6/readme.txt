Name: Quentin Truong
Assignment 6. Multithreaded performance

---

Using pthreads improved performance significantly. 
The precise timings may be viewed in file make-log.txt
The program runs roughly 2x as fast using 2 pthreads and 8x as fast using 8 pthreads.

Initial problems with using pthreads was the non-intuitive api.
Another problem was how to write out the output in order.
This was solved by using a global array and printing it out afterwards.
The pthread-modified program uses more memory because we had to store the output in an array.

---