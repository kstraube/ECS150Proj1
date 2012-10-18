#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int checks(int, char* argv[]);
char* init_read(char*);

int main (int argc, char* argv[])
{
  int arg = checks(argc, argv); 
  if(arg < 0)
    return -1;
  
  init_read(argv[1]);  
 
}

int init_read(char* path) {
  char buff[1024];
  int fd = open(path, o);
  read(fd, buff, 1024);  
  return 1;
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
