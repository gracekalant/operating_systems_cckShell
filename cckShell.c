#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 512
#define tokBUFSIZE 512
#define tokDELIMITER " &; "

char *command;
char *line;
char **args;
char **argv;
int argc = 0;
int status;
char input[BUFSIZE];
void Interactive(void);
int BatchFile(char *batF);
char *cckReadCMD(void);
static char* skipSpace(char* s);
char **cckSplitCMD(char *command);
int cckExecute(char **args);


//interactive mode
void Interactive()
{
  do {
    printf("kalantzi_8446> ");
    //printf("type quit to exit\n");

    line = cckReadCMD();
    args = cckSplitCMD(line);
    if (strcmp(args[0],"quit")==0) exit(EXIT_SUCCESS);
    status = cckExecute(args);

  } while (1);
}


//Batchfile mode
int BatchFile(char *batF)
{
	char inputB[BUFSIZE];
	//int quit = 0;

	//Opens file
	FILE* file = fopen(batF, "r");
	if (!file){
		printf("Couldn't open file.\n");
		exit(EXIT_FAILURE);
	}

	//Else reads file
	while (fgets(inputB, sizeof(inputB), file)) {
		strcpy(inputB, skipSpace(inputB));
		if (strcmp(inputB, "\n") == 0 || inputB == 0){
			continue;
		}
    //line = cckReadCMD();
    args = cckSplitCMD(inputB);
    if (strcmp(args[0],"quit")==0) exit(EXIT_SUCCESS);
    status = cckExecute(args);
	}

	fclose(file); //close the file
	return(0);
}


// Read a line of input from stdin.
//return The line from stdin.
char *cckReadCMD()
{
  int bufsize = BUFSIZE;
  int count = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int ch;

  if (!buffer) {
    fprintf(stderr, "Allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    ch = getchar();

    // If EOF, replace it with a null character and return
    if (ch == EOF || ch == '\n') {
      buffer[count] = '\0';
      return buffer;
    } else {
      buffer[count] = ch;
    }
    count ++;

    // If buffer exceeded, reallocate
    if (count >= bufsize) {
      bufsize += BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}


//Skip the spaces in a line
char *skipSpace(char *string)
{
  char *endLine;

  //Skip spaces on the frond
  while (isspace( (unsigned char) *string )){
    string++;
  }
  if(*string == 0) return string; //only spaces on the line
  //Skip spaces on the end
  endLine = string + strlen(string) - 1;
  while (endLine > string && isspace( (unsigned char) *endLine )){
    endLine--;
  }
  //Writes new null terminator
  *(endLine+1) = 0;

  return string;
}


//Split a line into tokens
char **cckSplitCMD(char *command)
{
  int bufsize = tokBUFSIZE, count = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "Allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(command, tokDELIMITER);
  
  while (token != NULL) {
    tokens[count] = token;
    count ++;

    if (count >= bufsize) {
      bufsize += tokBUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, tokDELIMITER);
    
  }
  tokens[count] = NULL;
  return tokens;
}


//main execution of the commands
int cckExecute(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("Failed to create child process");
    }
    exit(EXIT_FAILURE);
    } else if (pid < 0) {
    // Error forking
    perror("Can't fork");
    } else {
  	// Parent process
  		while (wait(&status) != pid)
  			;
  		return status;
  	}
}


int main(int argc, char *argv[]){

  //printf("kalantzi_8446> ");
  printf("type quit to exit\n");
  
  switch (argc) {
    case 1:
      Interactive();
    case 2:
      BatchFile(argv[1]);
    default:
      printf("Sorry! No such mode supported! \n");
  }
  exit(EXIT_SUCCESS);
}
