#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//redundant signal processing for clarity purposes
void ChildProcess();
void ParentProcess(pid_t pid);
void testContact(int sig);
void parFileReady(int sig);
void childFileReady(int sig);
void childTerminate(int sig);

int countSetBits(int number);

int invalidCount = 0;
int validCount = 0;

int main(){
  //forks and starts child and parent
  pid_t pid;
  pid = fork();
  int running = 1;
  if (pid == 0)
    ChildProcess();
  else
    ParentProcess(pid);
}

void ChildProcess(){
  //establish connection
  kill(getppid(), SIGUSR1);
  //command processing
  while(1){ 
    //receive file

    signal(SIGUSR1, parFileReady);
    pause();

    signal(SIGUSR2, childTerminate);

    //get command
    FILE * fp;
    fp = fopen("ptor_parent_file", "r");
    char* command = malloc(sizeof(50));
    fgets(command, 50, fp);
    fclose(fp);

    //process commands here
    if(command[0] == 'H' && command[1] == ' '){
      validCount++;
      int x = 0;
      int firstBreak = 0;
      char * firstFile;
      char * secondFile = NULL;
      for(x = 2; x < 50; x++){
        if(command[x] == ' '){
          firstBreak = x;
          int y;
          firstFile = malloc(sizeof(char)*(x-1));
          for(y = 2; y < firstBreak; y++){
            firstFile[y-2] = command[y];
          }
          firstFile[firstBreak+1] = '\0';
        }
        if(command[x] == '\0'){
          secondFile = malloc(sizeof(char)*(x-firstBreak+1));
          int y;
          for(y = firstBreak+1; y <= x; y++){
            secondFile[y-(firstBreak+1)] = command[y];
          }
          break;
        }
      }

     firstFile[strcspn(firstFile, "\n")] = 0;
     secondFile[strcspn(secondFile, "\n")] = 0;

     FILE * fp1;
     FILE * fp2;
     fp1 = fopen(firstFile, "rb");
     if(errno != 0){
       printf("Error: %d\n", errno);
     }
     fp2 = fopen(secondFile, "rb");
     fseek(fp1, 0, SEEK_END);
     long f1size = ftell(fp1);
     fseek(fp1, 0, SEEK_SET);
     
     fseek(fp2, 0, SEEK_END);
     long f2size = ftell(fp2);
     fseek(fp2, 0, SEEK_SET);

     if(f1size != f2size){
       printf("ptor: H: file sizes differ");
     }
     else{
       char* string1 = malloc(f1size + 1);
       char* string2 = malloc(f2size + 1);
       fread(string1, f1size, 1, fp1);
       fread(string2, f2size, 1, fp2);
       fclose(fp1);
       fclose(fp2);
        
       int strlen;
       int hammingDist = 0;
       for(strlen = 0; strlen < f1size; strlen++){
         if(string1[strlen] != string2[strlen])
           hammingDist++;
       }
       printf("ptor: H: Hamming Distance: %d", hammingDist);
     }
    }

    else if(command[0] == 'O' && command[1] == ' '){
      validCount++;
      int y;
      int size = strlen(command)-2;
      char* number = malloc(sizeof(char)*size);
      for(y = 2; command[y] != '\0'; y++){
        number[y-2]=command[y];
      }
      number[strlen(number)] = '\0';

      int newNum = atoi(number);

      int bits = countSetBits(newNum);

      int x = newNum+1;
      while(countSetBits(x) != bits){
        x++;
      }
      printf("ptor: O: %d \n", x);
    }
    else if(command[0] == 'R' && command[1] == ' '){
      validCount++;
      int y;
      int size = strlen(command)-2;
      char* fname = malloc(sizeof(char)*size);
      for(y = 2; command[y] != '\0'; y++){
        fname[y-2]=command[y];
      }
      fname[strlen(fname)] = '\0';

      int largestLoc = 0;
      int largestSize = 1;
      char largestChar = '\0';
      char ch;
      char curChar = '\0';
      int curLoc = 0;
      int curRun = 0;
      FILE * fp;
      fp = fopen(fname, "r");
      while((ch = getc(fp)) != EOF){
        //printf("Scanning %d\n", ch);
        if(curChar == '\0')
          curChar = ch;
        if(ch == curChar)
          curRun++;
        else{
          //printf("Run ended\n");
          if(curRun > largestSize){
            largestLoc = curLoc-curRun;
            largestSize = curRun;
            largestChar = curChar;
          }
          curChar = ch;
          curRun = 1;
        }
        curLoc++;

      }
      fclose(fp);
      printf("ptor: R: %d %d %d\n", largestLoc, largestChar, largestSize);
    }
    else if(command[0] == 'X' && command[1] == ' '){
      validCount++;
      int y;
      int size = strlen(command)-2;
      char* fname = malloc(sizeof(char)*size);
      for(y = 2; command[y] != '\0'; y++){
        fname[y-2]=command[y];
      }
      fname[strlen(fname)] = '\0';

      FILE * fp;
      fp = fopen(fname, "r");

      int total = 0;
      char ch;

      while((ch = getc(fp)) != EOF){
        total += ch;
      }

      total = ~((unsigned)total)+1; 

      printf("ptor: X: 0x%x\n", total);

    }
    else if(command[0] == '+' && command[1] == ' '){
      validCount++;
      int x = 0;
      int firstBreak = 0;
      char * firstFile;
      char * secondFile = NULL;
      for(x = 2; x < 50; x++){
        if(command[x] == ' '){
          firstBreak = x;
          int y;
          firstFile = malloc(sizeof(char)*(x-1));
          for(y = 2; y < firstBreak; y++){
            firstFile[y-2] = command[y];
          }
          firstFile[firstBreak+1] = '\0';
        }
        if(command[x] == '\0'){
          secondFile = malloc(sizeof(char)*(x-firstBreak+1));
          int y;
          for(y = firstBreak+1; y <= x; y++){
            secondFile[y-(firstBreak+1)] = command[y];
          }
          break;
        }
      }

      //printf("you entered %s and %s\n", firstFile, secondFile);

      int lengthdif = strlen(secondFile)-strlen(firstFile);
      if(lengthdif > 0 ){
        char* tempString = malloc(sizeof(char)*strlen(secondFile));
        strcpy(tempString, secondFile);
        free(secondFile);
        secondFile = malloc(sizeof(char)*strlen(firstFile));
        strcpy(secondFile, firstFile);
        free(firstFile);
        firstFile = malloc(sizeof(char)*strlen(tempString));
        strcpy(firstFile, tempString);
        //swap strings here
      }
      //printf("you entered %s and %s\n", firstFile, secondFile);


      char* answer = malloc(sizeof(char)*(strlen(firstFile)+1));
      answer[strlen(answer)] = '\0';
      x = strlen(secondFile)-1;
      int y = strlen(firstFile)-1;
      int remainder = 0;
      while(x >= 0){
        printf("Solving\n");
        int newRemainder = 0;
        if(firstFile[y] == '0' && secondFile[x] == '0')
          answer[y+1] = '0';
        if(firstFile[y] == '1' && secondFile[x] == '0')
          answer[y+1] = '1';
        if(firstFile[y] == '0' && secondFile[x] == '1')
          answer[y+1] = '1';
        if(firstFile[y] == '1' && secondFile[x] == '1'){
          answer[y+1] = '0';
          newRemainder++;
        }
        if(remainder == 1){
          if(answer[y+1] == '1'){
            answer[y+1] = '0';
            newRemainder++;
          }
          else{
            answer[y+1] = '1';
          }
        }
        //printf("Current digit: %c\n", answer[y+1]);
        remainder = newRemainder;
        y--;
        x--;
      }
      while(y >= 0){
        if(remainder != 0){
          if(firstFile[y] == '0'){
            remainder = 0;
            answer[y+1] = '1';
          }
          else
            answer[y+1] = '0';
        }
        else{
          answer[y+1] = firstFile[y];
        }
        y--;
      }
      if(remainder != 0)
        answer[0] = '1';
      else
        answer[0] = '0';

      //printf("Current digit: %c\n", answer[0]);
      printf("ptor: +: %s\n", answer);
    }
    
    else if(command[0] == '!'){
      validCount++;
      printf("ptor: !: %d valid %d invalid\n", validCount, invalidCount);
    }
    else{
      invalidCount++;
    }

    //say you're done
    kill(getppid(), SIGUSR2);
  }
}

void ParentProcess(pid_t pid){
  //establish contact
  int done = 0;
  signal(SIGUSR1, testContact);
  pause();

  //command processing
  while(!done){
    char* command = malloc(sizeof(50));

    printf("cmd: ");
    fgets(command, 50, stdin);
    strtok(command, "\n");

    //exit command
    if(strcmp(command, "exit") == 0){
      kill(pid, SIGUSR2);
      waitpid(pid, &invalidCount, 0);
      invalidCount = WEXITSTATUS(invalidCount);
      printf("Total invalid commands: %d \n", invalidCount);
      break;
    }

    //write command to file
    FILE * fp;
    fp = fopen("ptor_parent_file", "w");
    fprintf(fp, command);
    fclose(fp);
    
    //send file ready command
    kill(pid, SIGUSR1);
    
    //printf("parent waiting for child completion\n");
    //wait for child file
    signal(SIGUSR2, childFileReady);
    pause();
    //printf("parent knows child is done\n");

    //Display results here
    
  }
}

void testContact(int sig){
  signal(SIGUSR1, testContact);
}

void parFileReady(int sig){
  signal(SIGUSR1, parFileReady);
}

void childFileReady(int sig){
  signal(SIGUSR2, childFileReady);
}

void childTerminate(int sig){
  signal(SIGUSR2, childTerminate);
  exit(invalidCount);
}

int countSetBits(int number){
  int setBits;
  for(setBits = 0; number; number >>= 1){
    setBits += number & 1;
  }
  return setBits;
}
