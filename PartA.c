/*
*kill -s SIGKILL ORIGINAL_PID
*With INPUT / OUTPUT FILE
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int readInputFile(int arr[]);

void outputToConsole(FILE* out);


int read_pidMAX2;
int read_pidMIN2;
int read_pidSUM2;

int max1val;
int max2val;
int min1val;
int min2val;
int sum1val;
int sum2val;

//int arr[5] = {3, 2, 7, 8, 5};
int size;
int half;
int i = 0;
unsigned int time_to_sleep = 5; // sleep 5 seconds
int startingPID;




//&&&&&&&&&&&&&&&&&&&&&&&&&&&& BEGINNING OF MAIN &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

int main (void){


	// SELECT initialization

	startingPID = (int) getpid();


	FILE* out = fopen("outputA.txt", "w");
	fprintf(out, "Hi I'm OG: %d", (int) getpid());
	//fprintf(out, " and my parent is %d.\n", (int) getppid());
	printf("Hi I'm the OG: %d\n", (int) getpid());
	//printf(" and my parent is %d.\n", (int) getppid());
	int n = 0;


	printf("Enter the size of the array: \n");	//for now the size is 3
    	scanf("%d", &size);


    int arr[size];
    //createInputFile END

    half = size / 2;

    int j;
    int r;

 	for (j = 0; j < size; j++){

		//srand(time(NULL));	would have to invoke sleep, which takes too long
		FILE* out3 = fopen("inputA.txt", "a");	//NOTE: APPENDING TEXT SO WILL HAVE TO DELETE FILE BEFORE RUNNING AGAIN
		r = rand() % 1001;	//random number up to 1000
		arr[j] = r;
		fprintf(out3, "%d\n", arr[j]);
		printf("number %d\n", r);
		fclose(out3);

	}

    FILE* in = fopen("inputA.txt", "r");	//open input file
 	fprintf(out, "Hi I'm process %d", (int) getpid());
	fprintf(out, " and my parent is %d.\n", (int) getppid());
    printf("Hi I'm process %d", (int) getpid());
	printf(" and my parent is %d.\n", (int) getppid());

	while( fscanf(in, "%d\n", &n) > 0 ) //read file, parse by new line
    {
        arr[i++] = n;
    }

    fclose(in);
    //read input file END


//&&&&&& SECOND FUNCTIONS SENDING PIDS &&&&&&&&&&


//FROM CHILDREN TO PARENT &&&&&&&&&&&&&& SIGNAL OVERWRITES

//MAX 1
void sigcont(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	max1val = value.sival_int;
	//max1chk = true;
	fprintf(out, "%d\n", value.sival_int);
	fprintf(out, "From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out, "My PID: %d\n", getpid());		//shows which process received info
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}


//MAX 2
void sigio(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	max2val = value.sival_int;
	//max2chk = true;

	fprintf(out, "%d\n", value.sival_int);
	fprintf(out, "From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out, "My PID: %d\n", getpid());		//shows which process received info
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}


//MIN 1
void sigurg(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	min1val = value.sival_int;
	//min1chk = true;


	fprintf(out, "%d\n", value.sival_int);
	fprintf(out, "From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out, "My PID: %d\n", getpid());		//shows which process received info
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}

//MIN 2
void sigxcpu(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	min2val = value.sival_int;
	//min2chk = true;
	while(time_to_sleep){

						     time_to_sleep = sleep(time_to_sleep);
				    	}

	fprintf(out, "%d\n", value.sival_int);
	fprintf(out, "From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out, "My PID: %d\n", getpid());		//shows which process received info
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}

//SUM 1
void sigprof(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	sum1val = value.sival_int;
	//sum1chk = true;


	fprintf(out, "%d\n", value.sival_int);
	fprintf(out, "From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out, "My PID: %d\n", getpid());		//shows which process received info
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}


//SUM 2
void sigwinch(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	sum2val = value.sival_int;
	//sum2chk = true;


	fprintf(out, "%d\n", value.sival_int);
	fprintf(out, "From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out, "My PID: %d\n", getpid());		//shows which process received info
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}




//FROM PARENT TO CHILDREN &&&&&&&&&&&&&& SIGNAL OVERWRITES

//FIRST HALF SUM
void sigpwr(int signo) {
	signal(SIGPWR,sigpwr);
printf("SUM CHILD SLEEP 5 SECONDS\n");
	struct timespec timeout;
		timeout.tv_sec = 5;
		timeout.tv_nsec = 0;
		while (nanosleep(&timeout, &timeout) && errno == EINTR);
	int sum1 = arr[0];
	int i = 0;
	for(i = 1; i < half; i++){
		sum1 = sum1 + arr[i];
	}
	fprintf(out, "CHILD: RECEIVED SIGPWR\n");
	printf("CHILD: RECEIVED SIGPWR\n");
    //printf("CHILD: My DADDY has Killed me!!!\n");
    union sigval value;
    value.sival_int = sum1;
    fprintf(out, "SUM1: \n");
    printf("SUM1: \n");
    sigqueue(getppid(), SIGPROF, value);
}

//SECOND HALF SUM
void sigttou(int signo){
	signal(SIGTTOU,sigttou);

	int sum2 = arr[half];
	int i = 0;
	for(i = half+1; i < size; i++){
		sum2 = sum2 + arr[i];
	}
	fprintf(out, "CHILD: I have received SIGTTOU\n");
	printf("CHILD: I have received SIGTTOU\n");
	union sigval value;
	value.sival_int = sum2;
	fprintf(out, "SUM2: \n");
	printf("SUM2: \n");
	sigqueue(startingPID, SIGWINCH, value);
}



//FIRST HALF MAX
void sighup(int signo) {
    signal(SIGHUP,sighup);
	printf("MAX CHILD SLEEP 5 SECONDS\n");
	struct timespec timeout;
		timeout.tv_sec = 5;
		timeout.tv_nsec = 0;
		while (nanosleep(&timeout, &timeout) && errno == EINTR);


    int max1 = arr[0];
	int i = 0;
        for(i = 0; i < half; i++){
        	if (arr[i] > max1)
        	{
        		max1 = arr[i];
        	}
        }
    //printf("MAX: %d\n", max1);
    fprintf(out, "CHILD: I have received a SIGHUP\n");
    fprintf(out, "MAX: \n");
    printf("CHILD: I have received a SIGHUP\n");
    printf("MAX: \n");
    union sigval value;
    value.sival_int=max1;
    sigqueue(getppid(), SIGCONT, value);
}

//SECOND HALF MAX
void sigsys(int signo) {
    signal(SIGSYS,sigsys);

    int max2 = arr[half];
	int i = 0;
        for(i = half + 1; i < size; i++){
        	if (arr[i] > max2)
        	{
        		max2 = arr[i];
        	}
        }

    fprintf(out, "CHILD: I have received a SIGSYS\n");
    fprintf(out, "MAX2: \n");
    printf("CHILD: I have received a SIGSYS\n");
    printf("MAX2: \n");
    union sigval value;
    value.sival_int = max2;
    sigqueue(startingPID, SIGIO, value);
}

//FIRST HALF MIN
void sigbus(int signo) {
    signal(SIGBUS,sigbus);
printf("MIN CHILD SLEEP 5 SECONDS\n");
	struct timespec timeout;
		timeout.tv_sec = 5;
		timeout.tv_nsec = 0;
		while (nanosleep(&timeout, &timeout) && errno == EINTR);

    int min1 = arr[0];
	int i = 0;
        for(i = 0; i < half; i++)
        {
        		if (arr[i] < min1)
        		{
        			min1 = arr[i];
        		}
        }
        fprintf(out, "CHILD: I have received a SIGBUS, %d\n", getpid());
        printf("CHILD: I have received a SIGBUS, %d\n", getpid());
        union sigval value;
        value.sival_int = min1;
        fprintf(out, "MIN: \n");
        printf("MIN: \n");

        sigqueue(getppid(), SIGURG, value);

}

//SECOND HALF MIN
void sigill(int signo) {
    signal(SIGILL,sigill);

    int min2 = arr[half];
	int i = 0;
        for(i = half+1; i < size; i++)
        {
        		if (arr[i] < min2)
        		{
        			min2 = arr[i];
        		}
        }
        fprintf(out, "CHILD: I have received a SIGILL\n");
        printf("CHILD: I have received a SIGILL\n");
        union sigval value;
        value.sival_int = min2;
        fprintf(out, "MIN2: \n");
        printf("MIN2: \n");
        sigqueue(startingPID, SIGXCPU, value);

}



    	struct sigaction sigact;
        sigact.sa_flags = SA_SIGINFO;
        sigemptyset(&sigact.sa_mask);


	//MAX HANDLERS
        sigact.sa_handler = sighup;
        if (sigaction(SIGHUP, &sigact, NULL) < 0) {
            perror("sigaction()");
            exit(1);
        }

        sigact.sa_handler = sigsys;
        if (sigaction(SIGSYS, &sigact, NULL) < 0){
        	perror("sigaction()");
        	exit(1);
        }


	//MIN HANDLERS
        sigact.sa_handler = sigbus;			//min 1
        if (sigaction(SIGBUS, &sigact, NULL) < 0) {
            perror("sigaction()");
            exit(1);
        }

        sigact.sa_handler = sigill;			//min 2
        if (sigaction(SIGILL, &sigact, NULL) < 0) {
        	perror("sigaction()");
        	exit(1);
        }


	//SUM HANDLERS
        sigact.sa_handler = sigpwr;
        if (sigaction(SIGPWR, &sigact, NULL) < 0) {
            perror("sigaction()");
            exit(1);
        }

        sigact.sa_handler = sigttou;
        if (sigaction(SIGTTOU, &sigact, NULL) < 0) {
        	perror("sigaction()");
        	exit(1);
        }

	//&&&&&&&&&& BACK TO PARENT HANDLER &&&&&&&&&&&&

	//MAX1
        sigact.sa_handler = sigcont;
            if (sigaction(SIGCONT, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//MAX2
	sigact.sa_handler = sigio;
            if (sigaction(SIGIO, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//MIN1
	sigact.sa_handler = sigurg;
            if (sigaction(SIGURG, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//MIN2
	sigact.sa_handler = sigxcpu;
            if (sigaction(SIGXCPU, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//SUM1
	sigact.sa_handler = sigprof;
            if (sigaction(SIGPROF, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//SUM2
	sigact.sa_handler = sigwinch;
            if (sigaction(SIGWINCH, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }
    //&&&&&&&&&&&&&&&&&&&& FINISHED INITIALIZING ARRAY &&&&&&&&&&&&&&&&&&&&&&&&

	int child_status1;

	pid_t read_pid;

	pid_t read_pidMAX; //CHANGE

	pid_t read_pidMIN;

	pid_t read_pidSUM;


	read_pidMAX = fork();	//CHANGE
	if (read_pidMAX == 0){

		fprintf(out, "MAX1 Hi I'm process %d", (int) getpid());
		fprintf(out, " and my parent is %d.\n", (int) getppid());
		printf("MAX1 Hi I'm process %d", (int) getpid());
		printf(" and my parent is %d.\n", (int) getppid());
		int child_status2;

		read_pid = fork();
		if (read_pid == 0){
			fprintf(out, "Hi I'm process %d", (int) getpid());
			fprintf(out, " and my parent is %d.\n", (int) getppid());
			printf("MAX2 Hi I'm process %d", (int) getpid());
			printf(" and my parent is %d.\n", (int) getppid());
			int child_status3;

			wait(&child_status3);
		}
		else{

			//sigaction(SIGCONT, &sigact, NULL);
			sigaction(SIGSYS, &sigact, NULL);
			printf("\nSending SIGSYS\n\n");
			kill(read_pid,SIGSYS);
			//sleep(2); /* pause for 2 secs */



			wait (&child_status2);
		}
	}
	else{

		read_pidMIN = fork();
		if (read_pidMIN == 0){
			fprintf(out, "MIN1 Hi I'm process %d", (int) getpid());
			fprintf(out, " and my parent is %d.\n", (int) getppid());
			printf("MIN1 Hi I'm process %d", (int) getpid());
			printf("and my parent is %d.\n", (int) getppid());
			int child_status4;

			read_pid = fork();
			if(read_pid == 0){
				fprintf(out, "MIN2 Hi I'm process %d", (int) getpid());
				fprintf(out, " and my parent is %d.\n", (int) getppid());
				printf("MIN2 Hi I'm process %d", (int) getpid());
				printf("and my parent is %d.\n", (int) getppid());
				int child_status5;



				wait(&child_status5);
			}
			else{
				//min1 = findMin1(array);

				//dup2(fd[1], 1);
				//close(fd[0]);
				//close(fd[1]);
				//printf("%s %d\n","min1", min1);
				//sigaction(SIGCONT, &sigact, NULL);
				sigaction(SIGILL, &sigact, NULL);
				printf("\nSending SIGILL\n\n");
			    kill(read_pid,SIGILL);
				//sleep(2); /* pause for 2 secs */
				wait(&child_status4);
			}
		}
		else{

			read_pidSUM = fork();
			if(read_pidSUM == 0){
				fprintf(out, "SUM 1Hi I'm process %d", (int) getpid());
				fprintf(out, " and my parent is %d.\n", (int) getppid());
				printf("SUM1 Hi I'm process %d", (int) getpid());
				printf("and my parent is %d.\n", (int) getppid());
				int child_status6;

				read_pid = fork();
				if(read_pid == 0){
					fprintf(out, "SUM 2 Hi I'm process %d", (int) getpid());
					fprintf(out, " and my parent is %d.\n", (int) getppid());
					printf("SUM2 Hi I'm process %d", (int) getpid());
					printf("and my parent is %d.\n", (int) getppid());
					int child_status7;


					wait(&child_status7);
				}
				else{

					sigaction(SIGTTOU, &sigact, NULL);
					printf("\nSending SIGTTOU\n\n");
					kill(read_pid,SIGTTOU);
					//sleep(5); /* pause for 2 secs */
					wait(&child_status6);
				}
			}
		}
	}

	if(getpid() == startingPID){
		//dup2(fd[0], 0);
		//close(fd[0]);
		//close(fd[1]);
		//while(fgets(buffer, 100, stdin) != NULL){
		//bigChecker(buffer);
		//printf("TRUE: %d\n",max2);
		//printf("%s", buffer);

		sigact.sa_handler = SIG_DFL;
		sigaction(SIGHUP, &sigact, NULL);
		sigaction(SIGBUS, &sigact, NULL);
		sigaction(SIGPWR, &sigact, NULL);


		/* parent */
		/* pid hold id of child */

		//MAX SIGNAL
		fprintf(out, "\nPARENT: sending SIGHUP (max1 signal)\n\n");
		printf("\nPARENT: sending SIGHUP (max1 signal)\n\n");
	    kill(read_pidMAX,SIGHUP);

		//MIN SIGNAL
	    fprintf(out, "\nPARENT: sending SIGBUS (min1 signal)\n\n");
		printf("\nPARENT: sending SIGBUS (min1 signal)\n\n");
		kill(read_pidMIN,SIGBUS);


		//SUM SIGNAL
		fprintf(out, "\nPARENT: sending SIGPWR\n\n");
		printf("\nPARENT: sending SIGPWR (sum1 signal)\n\n");
		kill(read_pidSUM,SIGPWR);



		}

		wait (&child_status1);

		//outputToConsole(out);

		
		if(getpid() == startingPID){
		printf("PARENT SLEEP 5 SECONDS\n");
		struct timespec timeout;
		timeout.tv_sec = 5;
		timeout.tv_nsec = 0;
		while (nanosleep(&timeout, &timeout) && errno == EINTR);
		
           					int max;
           					int min;

           					if (max1val > max2val){
           						max = max1val;
           					}
           					else{
           						max = max2val;
           					}

           					if (min1val < min2val){
           						min = min1val;
           					}
           					else{
           						min = min2val;
           					}

           					int sum = sum1val + sum2val;

           					fprintf(out, "Min: %d\n", min);
           					fprintf(out, "Max: %d\n", max);
           					fprintf(out, "Sum: %d\n", sum);

           					printf("Min: %d\n", min);

           					printf("Max: %d\n", max);

           					printf("Sum: %d\n", sum);

           	}
           	
	//}




	fclose(out);

	return 0;
}