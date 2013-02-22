NOTE: **Conclusion at the end of the file.**


# Producer-Consumer Algorithm
-----------------------------------------

Producer-consumer is a common pattern in many computer processing systems (printing services). In the simplest case, we have a producer creating objects (for example, documents to print) and enqueuing them in a buffer that will be serviced by the consumer (for example, printer server). You can easily extend this to multiple producers and consumers.


## What Do You Need To Do?

Read the notes on Synchronization and POSIX threads.
Consider a toy producer-consumer problem. The producer is creating a integer and buffering it in a queue. The value of the integer is uninteresting (randomly created - could be even undefined in your program!). The consumer is consuming the integer from the queue. In this case, it will just read the integer value and discard it. Create 10 producers and one consumer. The producers and consumers are created using Pthreads. That is, a producer is a single thread.
Remember that a thread creation function in Pthreads takes a *start_function()* as an argument and launches the *start_function()* once the thread begins running.

Each producer creates N number of items (integers) and buffer them for the consumer. Ideally, the consumer should report to have consumed 10N items (integers). If you do not use any synchronization primitives, the consumer can report a number different from 10N as the items consumed.

Assume an infinite buffer size. The producer-consumer we discussed in the class and presented in the notes is a bounded-buffer producer-consumer.

First, implement the producer-consumer with multiple threads without any
synchronization primitive. That is, no mutexes and condition variables. You are still using POSIX threads for the producers and consumer. Run it for different N values and observe the reported value by the consumer. Document your experimental observations in the README file you submit with the assignment.
Next, you modify the program to include the necessary synchronization primitive so that the race conditions can be prevented. Now, report the experimental observations. You need to do many experiments because there cannot be race condition.

Measure the running time of the program using the **gettimeofday** function.
What is the overhead of synchronization?


# How to Use

You can run the program by using the ./**run.sh** bash script.

If you want to run the program on its own, the available commands are:

>**-async**	Disables sync mode (no use of mutex and conditions variables).

>**-profile**	Will only output the running time.

>**-produce N**	Specifies that each producers should produce *N* units. (default=50)

If you want more options, you can play around with the values in the header file **factory.h**. Especially the number of producer and consumer threads that should be produced:

	#define NB_PROD_THREAD 10
	#define NB_CONS_THREAD 1

# Conclusion

With no synchronisation, the threads are running into race conditions. They are writing the same spot multiple times in the queue with different values.

	Uncomment "PRINT_CONS" and "PRINT_PROD" to see the result.

With synchronisation, no such behavious can be observed, and all the units produced are being consumed as well.

	Again, you can uncomment "PRINT_CONS" and "PRINT_PROD" to see the result.

To observe the overhead of synchronisation, you can run the profiler executing the ./**profile.sh** bash file. One of my run can be seen in the **report.csv** file.

The csv file format was used to be able to import it quickly on a spreadsheet. The resulting graph can be seen in the folder as **overhead_graph.png**.

