#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<limits.h>
int cpid = 0;
int main(int argc, char* argv[]){
	printf("Kill It program \n");
	if (argc != 3){
		printf("Incorrect number of arguments. Should be 2\n");
	}
	else{
		int error = kill_it(argv[1], atoi(argv[2]));
	}
}

void alrm_action(int);

int kill_it(char* program, int n)
{
	int status = 0;
	// static struct sigacton act;
	
	// act.sa_handler = alrm_action;
	// sigfillset(&(act.sa_mask)); 
	
	// sigaction(SIGALRM, &act, NULL);
	
	signal(SIGALRM, alrm_action);
	cpid = fork();
	if (cpid == 0)
	{	//child
		printf("child\n");
		int err = execlp(program, program, NULL);// (char*) 0);
		//printf("postprog\n");
		// int i =0;
		// while(i<5){
			// sleep(1);
			// printf("dur\n");
		// }
		//printf("working %i\n", err);
		return 0;
	}
	else if (cpid < 0){
		printf("Fork failed\n");
		return -1;
	}
	else
	{	//parent
		//set alarm here
		alarm(n);
		printf("alarm set for %i\n", n);
		waitpid(cpid, &status,0);
		return 0;
	}
	//psuedocode: fork, if child then run prog, if parent then set alarm then wait
	//if child exits end alarm otherwise when alarm goes off, kill child
}

void alrm_action(int signo)
{
	printf("ALARM\n");
	kill(cpid, SIGKILL);
	printf("Signal sent\n");
	exit(1);
}