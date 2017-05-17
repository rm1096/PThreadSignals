//PART D: Multiple processes each spawning more processes

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int readInputFile(int arr[]);

//void outputToConsole(FILE* out);



int read_pidMAX2 = -5000;
int read_pidMIN2 = -5000;
int read_pidSUM2 = -5000;
int read_pidMAX = -5000;
int read_pidMIN = -5000;
int read_pidSUM = -5000;

int max1val = INT_MIN;
int max2val = INT_MIN;
int min1val = INT_MAX;
int min2val = INT_MAX;
int sum1val = 0;
int sum2val = 0;

int max1chk = 0;
int max2chk = 0;
int min1chk = 0;
int min2chk = 0;
int sum1chk = 0;
int sum2chk = 0;

//int arr[5] = {3, 2, 7, 8, 5};
//int size = 5;
//int half;
//int i = 0;

int size;
int half;
int i = 0;
int startingPID;






//&&&&&&&&&&&&&&&&&&&&&&&&&&&& BEGINNING OF MAIN &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

int main (void){


	// SELECT initialization
	fd_set rfds;
	struct timeval tv;
	int retval;

	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	// SELECT initialization END

	startingPID = (int) getpid();
	pid_t orginal = getpid();
	//printf("original: %d\n", original);

	FILE* out = fopen("outputB.txt", "w");
	fprintf(out, "Hi I'm process %d", (int) getpid());
	fprintf(out, " and my parent is %d.\n", (int) getppid());
	fprintf(out,"Hi I'm the OG: %d\n", (int) getpid());
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
		FILE* out3 = fopen("input.txt", "a");	//NOTE: APPENDING TEXT SO WILL HAVE TO DELETE FILE BEFORE RUNNING AGAIN
		r = rand() % 1001;	//random number up to 1000
		arr[j] = r;
		fprintf(out3, "%d\n", arr[j]);
		printf("number %d\n", r);
		fclose(out3);

	}

    FILE* in = fopen("input.txt", "r");	//open input file
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


	//&&&&&&&&& LICENSE TO KILL &&&&&&&&&&&&&&
void sigxfsz(int signo, siginfo_t *info, void *ptr){
	union sigval valval=info->si_value;
	int temptempPID = valval.sival_int;


	fprintf(out,"KILL KILL KILL KILL %d\n", temptempPID);
	printf("KILL KILL KILL KILL %d\n", temptempPID);
	
	kill(temptempPID,SIGKILL);
}

//&&&&&&& SECOND FUNCTIONS SENDING PIDS &&&&&&&&&&

//MIN 2 PID SEND
void sigtrap(int signo, siginfo_t *info, void *ptr){
	union sigval value=info->si_value;
	read_pidMIN2 = value.sival_int;
	
	fprintf(out,"Min2's pid transferred");
	printf("Min2's pid transferred");
}

//MAX 2 PID SEND
void sigfpe(int signo, siginfo_t *info, void *ptr){

	union sigval value=info->si_value;
	read_pidMAX2 = value.sival_int;
	
	fprintf(out,"Max2's pid transferred");
	printf("Max2's pid transferred");
}

//SUM 2 PID SEND
void sigsegv(int signo, siginfo_t *info, void *ptr){
	union sigval value=info->si_value;
	read_pidSUM2 = value.sival_int;
	
	fprintf(out,"Sum2's pid transferred");
	printf("Sum2's pid transferred");
}


//FROM CHILDREN TO PARENT &&&&&&&&&&&&&& SIGNAL OVERWRITES

//MAX 1
void sigcont(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;
	
	max1val = value.sival_int;
	max1chk = 1;


	fprintf(out,"%d\n", value.sival_int);
	fprintf(out,"From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out,"My PID: %d\n", getpid());
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}


//MAX 2
void sigtstp(int signo, siginfo_t *info, void *ptr)
{

	union sigval value=info->si_value;

	max2val = value.sival_int;
	max2chk = 1;	

	fprintf(out,"%d\n", value.sival_int);
	fprintf(out,"From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out,"My PID: %d\n", getpid());
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}


//MIN 1
void sigurg(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	min1val = value.sival_int;
	min1chk = 1;

	fprintf(out,"%d\n", value.sival_int);
	fprintf(out,"From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out,"My PID: %d\n", getpid());
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}

//MIN 2
void sigxcpu(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	min2val = value.sival_int;
	min2chk = 1;

	fprintf(out,"%d\n", value.sival_int);
	fprintf(out,"From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out,"My PID: %d\n", getpid());
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}

//SUM 1
void sigprof(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	sum1val = value.sival_int;
	sum1chk = 1;

	fprintf(out,"%d\n", value.sival_int);
	fprintf(out,"From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out,"My PID: %d\n", getpid());
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}


//SUM 2
void sigwinch(int signo, siginfo_t *info, void *ptr)
{
	union sigval value=info->si_value;

	sum2val = value.sival_int;
	sum2chk = 1;

	fprintf(out,"%d\n", value.sival_int);
	fprintf(out,"From %d\n",info->si_pid);		//shows where signal is from
	fprintf(out,"My PID: %d\n", getpid());
	printf("%d\n", value.sival_int);
	printf("From %d\n",info->si_pid);		//shows where signal is from
	printf("My PID: %d\n", getpid());		//shows which process received info

}




//FROM PARENT TO CHILDREN &&&&&&&&&&&&&& SIGNAL OVERWRITES

//FIRST HALF SUM
void sigquit(int signo) {

	//while(1){}

	int sum1 = arr[0];
	int i = 0;
	for(i = 1; i < half; i++){
		sum1 = sum1 + arr[i];
	}
	fprintf(out,"CHILD: RECEIVED SIGQUIT\n");
	printf("CHILD: RECEIVED SIGQUIT\n");
    union sigval value;
    value.sival_int = sum1;

	fprintf(out,"SUM1: \n");
    printf("SUM1: \n");
    sigqueue(getppid(), SIGPROF, value);
}

//SECOND HALF SUM
void sigttou(int signo){

	//while(1){}

	int sum2 = arr[half];
	int i = 0;
	for(i = half+1; i < size; i++){
		sum2 = sum2 + arr[i];
	}
	
	fprintf(out,"CHILD: I have received SIGTTOU\n");
	printf("CHILD: I have received SIGTTOU\n");
	union sigval value;
	value.sival_int = sum2;
	printf("SUM2: \n");
	sigqueue(startingPID, SIGWINCH, value);
}



//FIRST HALF MAX
void sighup(int signo) {	

	//while(1){}

    int max1 = arr[0];
	int i = 0;
        for(i = 0; i < half; i++){
        	if (arr[i] > max1)
        	{
        		max1 = arr[i];
        	}
        }

	
	fprintf(out,"CHILD: I have received a SIGHUP\n");
    fprintf(out,"MAX: \n");
    printf("CHILD: I have received a SIGHUP\n");
    printf("MAX: \n");
    union sigval value;
    value.sival_int=max1;
    sigqueue(getppid(), SIGCONT, value);
}

//SECOND HALF MAX
void sigsys(int signo) {

	//union sigval valval;

	//int tempPID = (int) getpid();
	//valval.sival_int = tempPID;
	//sigqueue(startingPID, SIGFPE, valval);

	//while(1){}

    int max2 = arr[half];
	int i = 0;
        for(i = half + 1; i < size; i++){
        	if (arr[i] > max2)
        	{
        		max2 = arr[i];
        	}
        }

	 fprintf(out,"CHILD: I have received a SIGSYS\n");
    fprintf(out,"MAX2: \n");
    printf("CHILD: I have received a SIGSYS\n");
    printf("MAX2: \n");
    union sigval value;
    value.sival_int = max2;
    sigqueue(startingPID, SIGTSTP, value);
}

//FIRST HALF MIN
void sigbus(int signo) {


	//while(1){}

    int min1 = arr[0];
	int i = 0;
        for(i = 0; i < half; i++)
        {
        		if (arr[i] < min1)
        		{
        			min1 = arr[i];
        		}
        }
	fprintf(out,"CHILD: I have received a SIGBUS, %d\n", getpid());
        printf("CHILD: I have received a SIGBUS, %d\n", getpid());
        union sigval value;
        value.sival_int = min1;
	fprintf(out,"MIN: \n");
        printf("MIN: \n");
	
        sigqueue(getppid(), SIGURG, value);

}

//SECOND HALF MIN
void sigill(int signo) {

	//union sigval valval;

	//int tempPID = (int) getpid();
	//valval.sival_int = tempPID;
	//sigqueue(startingPID, SIGTRAP, valval);

	//while(1){}

    int min2 = arr[half];
	int i = 0;
        for(i = half+1; i < size; i++)
        {
        		if (arr[i] < min2)
        		{
        			min2 = arr[i];
        		}
        }

	fprintf(out,"CHILD: I have received a SIGILL\n");
        printf("CHILD: I have received a SIGILL\n");
        union sigval value;
        value.sival_int = min2;
	fprintf(out,"MIN2: \n");
        printf("MIN2: \n");
        sigqueue(startingPID, SIGXCPU, value);

}


    	struct sigaction sigact;
        sigact.sa_flags = SA_SIGINFO;
        sigemptyset(&sigact.sa_mask);


	//LICENSE TO KILL HANDLER
	 sigact.sa_handler = sigxfsz;
        if (sigaction(SIGXFSZ, &sigact, NULL) < 0) {
            perror("sigaction()");
            exit(1);
        }

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
        sigact.sa_handler = sigquit;
        if (sigaction(SIGQUIT, &sigact, NULL) < 0) {
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
	sigact.sa_handler = sigtstp;
            if (sigaction(SIGTSTP, &sigact, NULL) < 0) {
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

	//&&&&&&&&& SENDING PID HANDLERS &&&&&&&&&&&&&

	//MIN2 PID SEND
	sigact.sa_handler = sigtrap;
            if (sigaction(SIGTRAP, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//MAX2 PID SEND
	sigact.sa_handler = sigfpe;
            if (sigaction(SIGFPE, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }

	//SUM2 PID SEND
	sigact.sa_handler = sigsegv;
            if (sigaction(SIGSEGV, &sigact, NULL) < 0) {
                perror("sigaction()");
                exit(1);
            }


    //&&&&&&&&&&&&&&&&&&&& FINISHED INITIALIZING ARRAY &&&&&&&&&&&&&&&&&&&&&&&&

	//int child_status1;

	pid_t read_pid;

	read_pid = fork();	//CHANGE
	if (read_pid == 0){
		//fprintf(out, "Hi I'm process %d", (int) getpid());
		//fprintf(out, " and my parent is %d.\n", (int) getppid());
		fprintf(out,"MAX1 Hi I'm process %d", (int) getpid());
		fprintf(out," and my parent is %d.\n", (int) getppid());
		printf("MAX1 Hi I'm process %d", (int) getpid());
		printf(" and my parent is %d.\n", (int) getppid());
		//int child_status2;

		read_pid = fork();
		if (read_pid == 0){

			//sending PID to first parent
			union sigval value;

			int tempPID = (int) getpid();
			value.sival_int = tempPID;
			sigqueue(startingPID, SIGFPE, value);
			//printf("LETS SEE: %s\n", strerror(errno));
			//sending PID to first parent END

			//fprintf(out, "Hi I'm process %d", (int) getpid());
			//fprintf(out, " and my parent is %d.\n", (int) getppid());
			fprintf(out,"MAX2 Hi I'm process %d", (int) getpid());
			fprintf(out," and my parent is %d.\n", (int) getppid());
			printf("MAX2 Hi I'm process %d", (int) getpid());
			printf(" and my parent is %d.\n", (int) getppid());
			while(1){}

			//wait(&child_status3);
		}
		else{
			while(1){}
			//sigaction(SIGCONT, &sigact, NULL);---------------------------------------------------------------------------
			//sigaction(SIGSYS, &sigact, NULL);
			//printf("\nSending SIGSYS\n\n");
			//kill(read_pid,SIGSYS);
			//sleep(2); /* pause for 2 secs */

			//dup2(fd[1], 1);
			//close(fd[0]);
			//close(fd[1]);
			//printf("%s %d\n","max1", max1);

			//wait (&child_status2);
		}
	}
	else{
		if(getpid() == startingPID){
				read_pidMAX = read_pid	;	
			}
		
		read_pid = fork();
		if (read_pid == 0){
			//fprintf(out, "Hi I'm process %d", (int) getpid());
			//fprintf(out, " and my parent is %d.\n", (int) getppid());
			fprintf(out,"MIN1 Hi I'm process %d", (int) getpid());
			fprintf(out,"and my parent is %d.\n", (int) getppid());
			printf("MIN1 Hi I'm process %d", (int) getpid());
			printf("and my parent is %d.\n", (int) getppid());
			//int child_status4;

			read_pid = fork();
			if(read_pid == 0){

				//sending PID to first parent
				union sigval value;

				int tempPID = (int) getpid();
				value.sival_int = tempPID;
				sigqueue(startingPID, SIGTRAP, value);
				//sending PID to first parent END

				//fprintf(out, "Hi I'm process %d", (int) getpid());
				//fprintf(out, " and my parent is %d.\n", (int) getppid());
				fprintf(out,"MIN2 Hi I'm process %d", (int) getpid());
				fprintf(out,"and my parent is %d.\n", (int) getppid());
				printf("MIN2 Hi I'm process %d", (int) getpid());
				printf("and my parent is %d.\n", (int) getppid());
				while(1){}
				//int child_status5;

				//wait(&child_status5);
			}
			else{
				while(1){}
				//min1 = findMin1(array);

				//dup2(fd[1], 1);
				//close(fd[0]);
				//close(fd[1]);
				//printf("%s %d\n","min1", min1);
				//sigaction(SIGCONT, &sigact, NULL);---------------------------------------------------------------
				//sigaction(SIGILL, &sigact, NULL);
				//printf("\nSending SIGILL\n\n");
			    	//kill(read_pid,SIGILL);
				//sleep(2); /* pause for 2 secs */
				//wait(&child_status4);
			}
		}
		else{
		if(getpid() == startingPID){
				read_pidMIN = read_pid	;	
			}
			
			read_pid = fork();
			if(read_pid == 0){
				//fprintf(out, "Hi I'm process %d", (int) getpid());
				//fprintf(out, " and my parent is %d.\n", (int) getppid());

				read_pidSUM = (int) getpid();

				fprintf(out,"SUM1 Hi I'm process %d", (int) getpid());
				fprintf(out,"and my parent is %d.\n", (int) getppid());
				printf("SUM1 Hi I'm process %d", (int) getpid());
				printf("and my parent is %d.\n", (int) getppid());
				//int child_status6;

				read_pid = fork();
				if(read_pid == 0){

					//sending PID to first parent

					union sigval value;

					int tempPID = (int) getpid();
					value.sival_int = tempPID;
					sigqueue(startingPID, SIGSEGV, value);
					//sending PID to first parent END

					//fprintf(out, "Hi I'm process %d", (int) getpid());
					//fprintf(out, " and my parent is %d.\n", (int) getppid());
					fprintf(out,"SUM2 Hi I'm process %d", (int) getpid());
					fprintf(out,"and my parent is %d.\n", (int) getppid());
					printf("SUM2 Hi I'm process %d", (int) getpid());
					printf("and my parent is %d.\n", (int) getppid());

					while(1){}
					//int child_status7;

					
					//sum2 = findSum2(array);
					//sigaction(SIGCONT, &sigact, NULL);
					//wait(&child_status7);
				}
				else{
					while(1){}
					//sum1 = findSum1(array);

					//sigaction(SIGCONT, &sigact, NULL);---------------------------------------------------------------------------
					//sigaction(SIGTTOU, &sigact, NULL);
					//printf("\nSending SIGTTOU\n\n");
					//kill(read_pid,SIGTTOU);
					//sleep(5); /* pause for 2 secs */
					//wait(&child_status6);
				}
			}
			
			if(getpid() == startingPID){
				read_pidSUM = read_pid	;	
			}

		}
	}

	if(getpid() == startingPID){
		sleep(1);
		sleep(1);
		sleep(1);
		

		sigact.sa_handler = SIG_DFL;
		sigaction(SIGHUP, &sigact, NULL);
		sigaction(SIGBUS, &sigact, NULL);
		sigaction(SIGQUIT, &sigact, NULL);
		sigaction(SIGTTOU, &sigact, NULL);
		sigaction(SIGILL, &sigact, NULL);
		sigaction(SIGSYS, &sigact, NULL);

		/* parent */
		/* pid hold id of child */

		//MAX SIGNAL
		fprintf(out,"\nPARENT: sending SIGHUP (max1 signal)\n\n");
		printf("\nPARENT: sending SIGHUP (max1 signal)\n\n");
	    	kill(read_pidMAX,SIGHUP);
		//sleep(2); /* pause for 2 secs */

		//MIN SIGNAL
		fprintf(out,"\nPARENT: sending SIGBUS (min1 signal)\n\n");
		printf("\nPARENT: sending SIGBUS (min1 signal)\n\n");
		kill(read_pidMIN,SIGBUS);
		//sleep(2); /* pause for 2 secs */

		

		//MAX2 SIG
		fprintf(out,"\nSending SIGSYS\n\n");
		printf("\nSending SIGSYS\n\n");
		kill(read_pidMAX2,SIGSYS);
		
		//MIN2 SIG
		fprintf(out,"\nSending SIGILL\n\n");
		printf("\nSending SIGILL\n\n");
		kill(read_pidMIN2,SIGILL);


		//SUM SIGNAL
		fprintf(out,"\nPARENT: sending SIGQUIT\n\n");
		printf("\nPARENT: sending SIGQUIT\n\n");
		kill(read_pidSUM,SIGQUIT);
		//sleep(5);

		//SUM2 SIG
		fprintf(out,"\nSending SIGTTOU\n\n");
		printf("\nSending SIGTTOU\n\n");
		kill(read_pidSUM2,SIGTTOU);
		//sleep(5); /* pause for 2 secs */


		fprintf(out,"WAITING 3 SECONDS\n");
		printf("WAITING 3 SECONDS\n");
		struct timespec timeout;
		timeout.tv_sec = 3;
		timeout.tv_nsec = 0;
		while (nanosleep(&timeout, &timeout) && errno == EINTR);

		if (max1chk == 0){
			union sigval value;

			value.sival_int = read_pidMAX;
			if (max2chk == 1){
				sigqueue(read_pidMAX2, SIGXFSZ, value);
			}
			if (min1chk == 1){
				sigqueue(read_pidMIN, SIGXFSZ, value);
			}
			if (min2chk == 1){
				sigqueue(read_pidMIN2, SIGXFSZ, value);

			}
			if (sum1chk == 1){
				sigqueue(read_pidSUM, SIGXFSZ, value);
			}
			if (sum2chk == 1){
				sigqueue(read_pidSUM2, SIGXFSZ, value);
			}
		}

		if (max2chk == 0){
			union sigval value;

			value.sival_int = read_pidMAX2;
			if (max1chk == 1){
				sigqueue(read_pidMAX, SIGXFSZ, value);
			}
			if (min1chk == 1){
				sigqueue(read_pidMIN, SIGXFSZ, value);
			}
			if (min2chk == 1){
				sigqueue(read_pidMIN2, SIGXFSZ, value);

			}
			if (sum1chk == 1){
				sigqueue(read_pidSUM, SIGXFSZ, value);
			}
			if (sum2chk == 1){
				sigqueue(read_pidSUM2, SIGXFSZ, value);
			}
		}

		if (min1chk == 0){
			union sigval value;

			printf("IN KILL MIN1 %d\n", read_pidMAX2);

			value.sival_int = read_pidMIN;
			if (max2chk == 1){
				sigqueue(read_pidMAX2, SIGXFSZ, value);	
			}
			if (max1chk == 1){
				sigqueue(read_pidMAX, SIGXFSZ, value);
			}
			if (min2chk == 1){
				sigqueue(read_pidMIN2, SIGXFSZ, value);

			}
			if (sum1chk == 1){
				sigqueue(read_pidSUM, SIGXFSZ, value);
			}
			if (sum2chk == 1){
				sigqueue(read_pidSUM2, SIGXFSZ, value);
			}
		}
		
		
		if (min2chk == 0){
			union sigval value;

			value.sival_int = read_pidMIN2;
			if (max2chk == 1){
				sigqueue(read_pidMAX2, SIGXFSZ, value);
			}
			if (min1chk == 1){
				sigqueue(read_pidMIN, SIGXFSZ, value);
			}
			if (max1chk == 1){
				sigqueue(read_pidMAX, SIGXFSZ, value);

			}
			if (sum1chk == 1){
				sigqueue(read_pidSUM, SIGXFSZ, value);
			}
			if (sum2chk == 1){
				sigqueue(read_pidSUM2, SIGXFSZ, value);
			}
		}
			
		if (sum1chk == 0){
			union sigval value;

			value.sival_int = read_pidSUM;
			if (max2chk == 1){
				sigqueue(read_pidMAX2, SIGXFSZ, value);
				
			}
			if (min1chk == 1){
				sigqueue(read_pidMIN, SIGXFSZ, value);
			}
			if (min2chk == 1){
				sigqueue(read_pidMIN2, SIGXFSZ, value);

			}
			if (max1chk == 1){
				sigqueue(read_pidMAX, SIGXFSZ, value);
			}
			if (sum2chk == 1){
				sigqueue(read_pidSUM2, SIGXFSZ, value);
			}
		}

		if (sum2chk == 0){
			union sigval value;

			value.sival_int = read_pidSUM2;
			if (max2chk == 1){
				sigqueue(read_pidMAX2, SIGXFSZ, value);
			}
			if (min1chk == 1){
				sigqueue(read_pidMIN, SIGXFSZ, value);
			}
			if (min2chk == 1){
				sigqueue(read_pidMIN2, SIGXFSZ, value);

			}
			if (sum1chk == 1){
				sigqueue(read_pidSUM, SIGXFSZ, value);
			}
			if (max1chk == 1){
				sigqueue(read_pidMAX, SIGXFSZ, value);
			}
		}

		fprintf(out,"ParentPID: %d\n", startingPID);
		fprintf(out,"Min1PID: %d\n", read_pidMIN);
		fprintf(out,"Min2PID: %d\n", read_pidMIN2);
		fprintf(out,"Max1PID: %d\n", read_pidMAX);
		fprintf(out,"Max2PID: %d\n", read_pidMAX2);
		fprintf(out,"Sum1PID: %d\n", read_pidSUM);
		fprintf(out,"Sum2PID: %d\n\n", read_pidSUM2);

		fprintf(out,"Min1 check: %d\n", min1chk);
		fprintf(out,"Min2 check: %d\n", min2chk);
		fprintf(out,"Max1 check: %d\n", max1chk);
		fprintf(out,"Max2 check: %d\n", max2chk);
		fprintf(out,"Sum1 check: %d\n", sum1chk);
		fprintf(out,"Sum2 check: %d\n\n", sum2chk);

		fprintf(out,"Min1 val: %d\n", min1val);
		fprintf(out,"Min2 val: %d\n", min2val);
		fprintf(out,"Max1 val: %d\n", max1val);
		fprintf(out,"Max2 val: %d\n", max2val);
		fprintf(out,"Sum1 val: %d\n", sum1val);
		fprintf(out,"Sum2 val: %d\n\n", sum2val);


		printf("ParentPID: %d\n", startingPID);
		printf("Min1PID: %d\n", read_pidMIN);
		printf("Min2PID: %d\n", read_pidMIN2);
		printf("Max1PID: %d\n", read_pidMAX);
		printf("Max2PID: %d\n", read_pidMAX2);
		printf("Sum1PID: %d\n", read_pidSUM);
		printf("Sum2PID: %d\n\n", read_pidSUM2);

		printf("Min1 check: %d\n", min1chk);
		printf("Min2 check: %d\n", min2chk);
		printf("Max1 check: %d\n", max1chk);
		printf("Max2 check: %d\n", max2chk);
		printf("Sum1 check: %d\n", sum1chk);
		printf("Sum2 check: %d\n\n", sum2chk);

		printf("Min1 val: %d\n", min1val);
		printf("Min2 val: %d\n", min2val);
		printf("Max1 val: %d\n", max1val);
		printf("Max2 val: %d\n", max2val);
		printf("Sum1 val: %d\n", sum1val);
		printf("Sum2 val: %d\n\n", sum2val);

		fprintf(out,"WAITING 5 SECONDS BEFORE PARENT KILLS ALL\n");
		printf("WAITING 5 SECONDS BEFORE PARENT KILLS ALL\n");
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

		fprintf(out,"Min: %d\n", min);
		fprintf(out,"Max: %d\n", max);
		fprintf(out,"Sum: %d\n\n", sum);

		printf("Min: %d\n", min);
		printf("Max: %d\n", max);
		printf("Sum: %d\n\n", sum);
		
	
		kill(read_pidMIN,SIGKILL);
		kill(read_pidMIN2,SIGKILL);
		kill(read_pidMAX,SIGKILL);
		kill(read_pidMAX2,SIGKILL);
		kill(read_pidSUM,SIGKILL);
		kill(read_pidSUM2,SIGKILL);
	}
		
		

	//} MAY NEED THIS NOT SURE

fclose(out);

	return 0;
}