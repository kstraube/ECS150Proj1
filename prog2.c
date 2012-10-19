#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void test();
void reverse(char*, int);
void compare(char*, char*); 
int prompting(char*);
void alpha(char*);
void cat(char*, char*, char*);

void cat(char* array, char* original, char* inverse){
  printf("array: %s\n", array);
  printf("original: %s\n",original);
  printf("inverse: %s\n", inverse);
  strcat(array, original);
  strcat(array, inverse);
  printf("The concatenated string: %s\n", array);
}
  
void alpha(char* array){
  int i; char c;
  // printf(array);
  for(i=0; i<strlen(array); i++){
    if(!isupper(array[i])) {
      c=toupper(array[i]);
      array[i]=c;
    }
  }
  printf("Big Alpha: %s\n", array);
}

int prompting(char* prompt){
  printf("Enter: ");
  scanf("%s", prompt);
  printf("Entered: %s\n", prompt); 
  return(strlen(prompt));
}

int main()
{
  char prompt[400], string[400], original[400], string_caps[400], string_cat[400], final[400];
  char inverse[400];
  int fd[2], fd2[2], pfd[2], pfd2[2];
  int status = 0, cpid = 0, rval = 0;
  int size = prompting(original);
  pipe(fd); pipe(fd2); pipe(pfd); pipe(pfd2);
  cpid=fork();
  if(cpid > 0){
    close(fd[0]);
    //close(1); 
    dup(fd[1]);
    write(fd[1], original, size);
    close(fd[1]);
    
    waitpid(cpid, &status, 0);
    close(fd2[1]); 
    close(0);
    dup(fd2[0]);
    rval = read(fd2[0], final, status);
	// printf(final);
    close(fd2[0]);
    compare(original, final);
    if(rval)
      return 1;
    else
      return -1;
  }
  else if(cpid == 0){
    close(fd[1]); close(0);
    dup(fd[0]);
    read(fd[0], inverse, size);
	// printf(inverse);
    close(fd[0]);
    reverse(inverse, size);
	// printf("%s\n",inverse);
    //forking to  grandchild
    int gpid = fork();
    if(gpid > 0){
      close(pfd[0]); 
      dup(pfd[1]);
      rval = write(pfd[1], inverse, size);
      close(pfd[1]);
      
      waitpid(gpid, &status, 0);  
      close(pfd2[1]); close(0);
      dup(pfd2[0]);
      rval = read(pfd2[0], string_cat, status);
      close(pfd2[0]);
	  char* prompt2 = "";
      cat(prompt2, original, string_cat);
      close(fd2[0]); close(1);
      dup(fd2[1]);
      rval = write(fd2[1], prompt, strlen(prompt));
      close(fd2[1]);
      status = strlen(prompt);
      if(rval)
        return(status);
      else
        return(-1);
    }
    else if(gpid == 0){
      close(pfd[1]); close(0);
      dup(pfd[0]);
      rval = read(pfd[0], string_caps, size);
      close(pfd[0]);
      alpha(string_caps);
      close(1); close(pfd2[0]);
      dup(pfd2[1]);
      rval = write(pfd2[1], string_caps, size);
      close(pfd2[1]);
      status = strlen(string_caps);
      if(rval){
        return(status);}
      else
        return(-1); 
    } 
  } 
  else
  {
    printf("Error\n");
  }
}

void test(){
  printf("testing\n");
}
void compare(char* string1, char* string2){
  int rval=strcmp(string1, string2);
  if(rval==0)
    printf("The strings are Equal\n");
  else
    printf("The strings are unequal\n");
}

void reverse(char* array, int size){
  int i, j = size -1;
  char tmp;
  for(i=0; i<j; i++, j--) {
    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }
  printf("The reverse is: %s\n", array);
}
