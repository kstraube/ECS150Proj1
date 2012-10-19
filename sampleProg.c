#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int cpid = 0;
int main(int argc, char* argv[]){
	int i = 0;
	while (i<5)
	{
		printf("%d\n", i);
		sleep(1);
	}
}