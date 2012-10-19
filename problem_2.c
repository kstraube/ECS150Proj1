#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void reverse(char*, int);
void compare(char*, char*); 

int main()
{
  char prompt[400], string[400], original[400], string_caps[400], string_cat[800];
  
  //prompting
  printf("Enter: ");
  scanf("%s", prompt);
  printf("Entered: %s\n", prompt);
  int size=strlen(prompt);
  int pfd[2], check, i;
  check = pipe(pfd);
  if(check<0)
    printf("Error with setting up pipe\n");
  check = write(pfd[1], prompt, size);
  if(read(pfd[0], string, check)) {
  //reversing string
    reverse(string, size);
    printf("Reverse: %s\n", string);
  }
  else
    printf("Read error at inverse!\n");
  close(pfd[0]);
  close(pfd[1]);  
   
  int pfd_2[2];
  char c;
  check = pipe(pfd_2);
  if(check<0)
    printf("Error with setting up pipe\n");
  check = write(pfd_2[1], string, size);
  if(check<0)
    printf("Error writing");
  if(read(pfd_2[0], string_caps, check)) {
  //converting string to uppercase
    for(i=0; i<size; i++){
      if(!isupper(string_caps[i])) {
        c=toupper(string_caps[i]);
        string_caps[i]=c;
      }
    }
    printf("Capitals: %s\n", string_caps);
  }
  else
    printf("Read error at upper");
  close(pfd_2[1]);
  close(pfd_2[0]); 
 
 //sending back
  int pfd_3[2];
  check = pipe(pfd_3);
  if(check<0)
    printf("Error with setting up pipe\n"); 
  check = write(pfd_3[1], string_caps, size);
  if(check<0)
    printf("Error writing"); 
  if(read(pfd_3[0], string_cat, check))
  {
    strcat(prompt, string_cat);
    printf("concatenation: %s\n", prompt);
  }
  close(pfd_2[0]);
  close(pfd_2[1]);
  
  //back to process 1
  int pfd_bak[2];
  check = pipe(pfd_bak);
  if(check<0)
    printf("Error with setting up pipe\n");
  check = write(pfd_bak[1], prompt, strlen(prompt));
  if(read(pfd_bak[0], string_cat, check)){
    strncpy(original, string_cat, size);
    compare(original, string_cat);
  }
  
  close(pfd_bak[0]);
  close(pfd_bak[1]);
 //close(pfd_2[0]);
 // close(pfd_2[1]);
    
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
}
