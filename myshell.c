#include "cd.h"
#include "echo.h"
#include "parse.h"
#include "local_vars.h"
#include "prompt.h"
#include "export.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char history[10][BUFFER_SIZE];
char * variables[64];
char * values[64];

void redirect_output(char *file_name){
      	 int out=open(file_name,O_WRONLY|O_TRUNC|O_CREAT,0600);
   	dup2(out,1);
   	close(out);
}
void redirect_input(char *file_name){
    int in = open(file_name, O_RDONLY);
    dup2(in, 0);
    close(in);
}
int
main() {

  char * host_name = (char * ) malloc(sizeof(char) * (1024 + 1));
  char * input, shell_prompt[200],* newargv[64],cwd[PATH_MAX],*args2[64];
  int command = 0;
  int args_count = 0;
  int args_count2 = 0;
  int redirection_type=0;
  pid_t ret_pid;
  gethostname(host_name, (1024 + 1));
  init_prompt();
   char *cc=(char * ) malloc(sizeof(char) * (50 + 1));
   char *file=(char * ) malloc(sizeof(char) * (50 + 1));
  
  for (;;) {
   // redirect_output("dev/tty");
    // Create prompt string from user name and current working directory.
    snprintf(shell_prompt, sizeof(shell_prompt), "%s%s@%s:~%s%s$ %s", GREEN_BOLD,
      getenv("USER"), host_name, KCYN, getcwd(NULL, 1024), RESET);

    // Display prompt and read input (NB: input must be freed after use)...
    input = readline(shell_prompt);
    trim_spaces(input);
    // Check for EOF.
    if (!input)
      break;
    if (strcmp(input, "") == 0)
      continue;
   strcpy(history[command++], input);
      
   redirection_type=check_redirection(input);
   if(redirection_type>-1){
   args_count2=parse_redirection(input,args2);
    strcpy(cc,args2[0]);
    strcpy(file,args2[1]);   
   args_count = parse(cc, newargv);
   }else{
     args_count = parse(input, newargv);
   }



    if (strcmp(newargv[0], "export") == 0) {
      export (args_count, newargv);
      continue;
    } else if (strcmp(newargv[0], "set") == 0) {
      print_variables(variables, values);
      continue;
    } else if (strcmp(newargv[0], "echo") == 0) {
      handle_echo(args_count, newargv);
      continue;
    } else if (strcmp(newargv[0], "exit") == 0) {
      exit(0);
      continue;
    } else if (strcmp(newargv[0], "cd") == 0) {
      handle_cd(args_count, newargv);
      continue;
    } else if (check_variable(input)) {
      save_variable(input, variables, values);
      continue;
    } else {
      ret_pid = fork();
      if (ret_pid < 0)
        printf("Fork Failed\n");
      else if (ret_pid > 0) {
        int status;
        wait( & status);
      } else {
      if(redirection_type==1){
            redirect_output(file);
      }else if(redirection_type==0){
            redirect_input(file);
      } 
        execvp(newargv[0], newargv);
        printf("%s: command not found\n", input);
        return -1;
      }
    }

    if (command == 9)
      command = 0;

  }
  return 0;
}
