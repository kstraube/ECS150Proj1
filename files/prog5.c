#include<stdio.h>

int main(int argc, char* argv[]){
	//printf("%d\n", sizeof(argv));
	printf("Simple Sum program \nAll non-number inputs become 0s and non-integers are rounded down \n");
	if (argc < 3){
		printf("Too few arguments\n");
	}
	else{
	harder_sum(atoi(argv[1]),atoi(argv[2]));
	}
}

int simple_sum(int a,int b){
	//printf("A = %d, B = %d", a ,b);
	int ans = 0;
	int status = 0;
	//printf("started\n");
	int cpid = fork();
	//printf("pid %d\n", cpid);
	if (cpid == 0)
	{
		//printf("child\n %d %d\n", a, b);
		ans = a+b;
		//printf("child Answer: %d\n", ans);
		return ans;
	}
	else if (cpid < 0)
	{
		printf("Fork failed\n");
		return -1;
	}
	else
	{
		//printf("parent\n");
		waitpid(cpid, &status,0);
		status = status >> 8;
		printf("Answer is: %d\n",status);
		return status;
	}
}	
	int harder_sum(int a,int b){
	//printf("A = %d, B = %d", a ,b);
	int ans = 0;
	int status = 0;
	//printf("started\n");
	int cpid = fork();
	//printf("pid %d\n", cpid);
	if (cpid == 0)
	{
		//printf("child\n %d %d\n", a, b);
		int cpid2 = fork();
		//printf("pid %d\n", cpid2);
		if (cpid2 == 0)
		{
			ans = a+b;
			return ans;
		}
		else if (cpid < 0)
		{
			printf("Fork failed\n");
			return -1;
		}
		else{
			waitpid(cpid, &status,0);
			status = status >> 8;
			return status;
		}
	}
	else if (cpid < 0)
	{
		printf("Fork failed\n");
		return -1;
	}
	else
	{
		//printf("parent\n");
		waitpid(cpid, &status,0);
		status = status >> 8;
		printf("Answer is: %d\n",status);
		return status;
	}
}