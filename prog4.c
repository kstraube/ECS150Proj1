#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
	printf("Move Files program \n");
	// printf("%i",argc);
	// printf("\n%i", sizeof(argv));
	// printf(argv[argc-1]);
	// printf("\n");
	if (argc < 2){
		printf("Too few arguments\n");
	}
	else{
		int error = move_files(argc, argv);
	}
}

int move_files(int argc, char* argv[]){
	DIR *dir;
	DIR *dir2;
	struct dirent *entry;
	int size = argc;
	
	char* directory = argv[size-1];
	char buf[256];
	// printf(directory,'\n');
	dir2 = opendir(".");
	
	if (dir2 == NULL)
	{
		printf("Current directory not open-able\n");
		return;
	}
	dir = opendir(directory);
	if (dir == NULL)
	{
		mkdir(directory, 777);
		dir = opendir(directory);
	}
	// printf("start\n");
	// while ((entry = readdir(dir)) != NULL)
	// {
		// printf("\n %s ", entry->d_name);
		// printf("%i", entry->d_fileno);
	// }
	
	int i;
	int statStatus;
	for (i = 1; i < size-1; i++){
		struct stat fileStat;
		char* fileOn = argv[i];
		// printf("\n");
		char str[128] = "";
		strcat(str,directory);
		strcat(str,"/");
		strcat(str,fileOn);
		statStatus = stat(fileOn, &fileStat);
		printf("Current file: ");
		printf(fileOn);
		if (!S_ISREG(fileStat.st_mode)|statStatus<0)
		{
			
			printf("\nSpecial file or file does not exist. Exiting now.");
			return;
		}
		link(fileOn, str);
		unlink(fileOn);
		printf("\nSuccess!\n");
	}
	
	// printf("\nNEXT");
	// rewinddir(dir);
	// while ((entry = readdir(dir)) != NULL)
	// {
		// printf("\n %s ", entry->d_name);
		// printf("%i", entry->d_fileno);
	// }
	closedir(dir);
	printf("Completed successfully!");
	return 0;
}