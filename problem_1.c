#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int checks(int argc, char* argv[], int* opts);
int compare(char* buffer1, char* buffer2, int fd1, int fd2, int counter, int* opts);
void print(int fd, int position);
 
int main (int argc, char* argv[])
{
  int fd1, fd2, nread1, nread2, rcomp=0, counter=0;
  char buffer1[1024], buffer2[1024];
  int options[3]={0,0,0}; //correspoding to options[s,d,u]
  int arg = checks(argc, argv, options); 
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
      rcomp=compare(buffer1, buffer2, fd1, fd2, counter, options);
    }      
    counter++;
  } 

  //option -d
  if(options[1]==1)
  {
    int difference, lpos1, lpos2;
    lpos1=lseek(fd1, 0, 2);
    lpos2=lseek(fd2, 0, 2);
    if(lpos1>lpos2)
      difference=lpos1-lpos2;
    else
      difference=lpos2-lpos1;
    printf("The difference in File Lengths of %s and %s is %d\n", argv[1], argv[2], difference);
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

int compare(char* buff1, char* buff2, int fd1, int fd2, int counter, int* opts){
  int i, position=counter*1024, val=1;
  for(i=0; i<1024; i++) {
    position++;
    if((buff1[i]=='\0')&&(buff2[i]=='\0')){
      val=-1;
      break;
    }
    else if(buff1[i]=='\0'){
      if(opts[0]==0)
        print(fd2, position); 
      val=-1;
      break;
    }
    else if(buff2[i]=='\0'){
      if(opts[0]==0)
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

int checks(int argc, char* argv[], int* opts)
{
    //Checks
  int rval, i;

  //Basic command implementation: % ./compare.out path1 path2 -option
  if(argc < 3)
  {
    printf("Incorrect arguments! Expecting: <path_to_file1> <path_to_file2> <no option/ option -s,-d,-u>\n");
    return -1;
  }
  else if(argc>3)
  { 
    for(i=3; i<argc; i++) { 
      if(strcmp(argv[i], "-s")==0)
        opts[0]=1;
      else if(strcmp(argv[i], "-d")==0)
        opts[1]=1;
      else if(strcmp(argv[i], "-u")==0)
        opts[2]=1; 
      else {
        printf("Incorrect option %s.Will be ignored\n",argv[i]); 
      }
    }
  }

    //check for read permissions
  for(i=1; i<3; i++) {
    rval = access (argv[i], R_OK);
    if (rval != 0) {
      printf("%s is not readable.\n", argv[i]);
      argc=-1;
    }
  }

  //printf("arg_count: %d\n", argc); 
  return argc; 
}          
