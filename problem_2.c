#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void reverse(char*, int);
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
    printf("Reverse: %s\n, Original: %s\n", string, original);
  }
  else
    printf("Read error at inverse!\n");
 
  printf("%s\n",prompt);
  //close(pfd[0]);
  //close(pfd[1]);
  
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
    printf("%s\n", string_caps);
  }
  else
    printf("Read error at upper");
  
  //sending back
  check = write(pfd_2[1], string_caps, size);
  if(check<0)
    printf("Error writing"); 
  if(read(pfd_2[0], string_cat, check))
  {
    strcat(prompt, string_cat);
    printf("%s\n", prompt);
  }
  
  

  close(pfd[0]);
  close(pfd[1]);
  close(pfd_2[0]);
  close(pfd_2[1]);
    
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
