#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

//Alex Boswell
//301261407
/*
Write a multi-threaded Linux program named fibonacci.c which accepts a single integer parameter from the command line (N), and then prints out the first N Fibonacci numbers to the screen.

    You must launch one thread which computes all N Fibonacci numbers, storing them into a data structure accessible by the main thread.
        Hint: a dynamically allocated array is simple! Declare a global variable that is a pointer to ints. In main(), dynamically allocate enough space to hold the N values. Have your thread function then use the global variable (pointer to the ints) to store the values.
        You could also have the thread function dynamically allocate the space and then return the pointer via pthread_exit(). See tutorial video posted to YouTube on dynamic memory allocation and threads for more.
    After launching the calculating thread, the main thread must wait until the calculating thread completes.
    Once the calculating thread completes, the main thread writes the results to the screen.
        The calculating thread must not write any text to the screen.
    As in the previous question, print the process ID and username using:

    printf("\nPID is: %d \t Username: %s\n", getpid(), getlogin());

    which will print the process ID and username. You need to include #include<unistd.h>.
*/





    //****************************COMPILE USING THE FOLLOWING IN THE LINUX TERMINAL**********************************************************
    //cc -g -std=c99 fibonacci.c -lpthread
    //otherwise it will not work


int *intS;
void fibonacci(int n){

    //printf("Entered Fib\n");

    if(n ==1){
        intS[0] = 1;    //first value is 1
    }
    else if (n == 2){
        intS[0] = 1;    //first value is 1
        intS[1] = 1;    //second value is 1
    }
    else{

        intS[0] = 1;    //set initial 2 values and then loop through the rest
        intS[1] = 1;

        for(int j = 2; j!= n; j++){

            intS[j] = intS[j-1] + intS[j-2]; 

        }

    }

    pthread_exit(0); 
}

void print_fib(int n){

    //int i = myInt;

    for(int i = 0; i != n; i++){
        printf("%d\n", intS[i]);
    }

}


int main (int argc, char *argv[]) {

    int myInt = 0;

    printf("Please enter a positive integer:\n");
    scanf("%d", &myInt);

    while(myInt <= 0){
               printf("Sorry, the integer you entered is not valid, please try again:\n");
            scanf("%d", &myInt);
    }

    printf("\nPID is: %d \t Username: %s\n", getpid(), getlogin());
 
    intS = (int *)malloc(myInt * sizeof(int));  //declare dynamically the size of the array based off the input


    pthread_t tid;      //create thread
    pthread_attr_t attr;
	
	pthread_attr_init(&attr);  // default attributes 
	pthread_create(&tid,&attr,fibonacci,myInt);
 	pthread_join(tid, NULL);    //suspends until the tid thread finishes and then prints all the fib numbers

    print_fib(myInt);

free(intS);
//printf("Finished Main\n");
return 0;
}