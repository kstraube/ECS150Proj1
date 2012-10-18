#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int checks(int argc, char* argv[]);
int compare(char* buffer1, char* buffer2, int fd1, int fd2, int counter);
void print(int fd, int position);
 
int main (int argc, char* argv[])
{
  int fd1, fd2, nread1, nread2, rcomp=0, counter=0;
  char buffer1[1024], buffer2[1024];
  int arg = checks(argc, argv); 
  if(arg < 0)
    return -1;
  
  fd1 = open(argv[1], 0);
  fd2 = open(argv[2], 0);
  int i; 
  while (rcomp >= 0) {
    nread1 = read(fd1, buffer1, 1024);
    nread2 = read(fd2, buffer2, 1024);
    if(nread1<0 || nread2<0 )
    {
      printf("Error in reading!\n"); 
      rcomp=-1;
    }
    else
    {
      rcomp=compare(buffer1, buffer2, fd1, fd2, counter);
    }      
    counter++;
  } 

  close(fd1);
  close(fd2);
      
}

void print(int fd, int position){
  int i, count=0, val=0;
  char buffer[1024];
  count=lseek(fd,position,0);
  printf("%c -----", buffer[count]);
  do {
    read(fd, buffer, 1024);
    for(i=0; i<1024; i++) {
      if(buffer[i]=='\0') {
        count=-1;
        break;
      }
      else { 
        count++;
        printf("At position %d, %c of single buffer\n", count, buffer[i]);
      }
    }
  } while(count>0);  
}

int compare(char* buff1, char* buff2, int fd1, int fd2, int counter){
  int i, position=counter*1024, val=1;
  for(i=0; i<1024; i++) {
    position++;
    if((buff1[i]=='\0')&&(buff2[i]=='\0')){
      val=-1;
      break;
    }
    else if(buff1[i]=='\0'){
      print(fd2, position); 
      val=-1;
      break;
    }
    else if(buff2[i]=='\0'){
      print(fd1, position);
      val=-1;
      break;
    } 
    else if(buff1[i] != buff2[i]) {
      printf("At position %d, %c, %c\n",position, buff1[i], buff2[i]);
    }
  }
  return val;
}

int checks(int argc, char* argv[])
{
    //Checks
  int rval, i;

  //Basic command implementation: % ./compare.out path1 path2 -option
  if(argc < 3 || argc > 4)
  {
    printf("Incorrect arguments! Expecting: <path_to_file1> <path_to_file2> <no option/ option -s,-d,-u>\n");
    return -1;
  }
  else if(argc==4)
  {
    if((strcmp(argv[3], "-s")==0) || (strcmp(argv[3], "-d")==0) || (strcmp(argv[3], "-u")==0)); 
    else {
      printf("Incorrect option. Try -s,-d,-u next time. Undertaking Default Actions.\n"); 
      argc--;
    }
  }

    //check for read permissions
  for(i=1; i<3; i++) {
    rval = access (argv[i], R_OK);
    if (rval != 0) {
      printf("%s is not readable.\n", argv[i]);
      return -1;
    }
  }

  //printf("arg_count: %d\n", argc); 
  return argc; 
}          
