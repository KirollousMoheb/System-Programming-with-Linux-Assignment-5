#include "cd.h"

#include "echo.h"

#include "parse.h"

#include "local_vars.h"

#include "prompt.h"

#include "export.h"

char history[10][BUFFER_SIZE];
char * variables[64];
char * values[64];

int
main() {

  char * host_name = (char * ) malloc(sizeof(char) * (1024 + 1));
  char * input, shell_prompt[100],* newargv[64],cwd[PATH_MAX];
  int command = 0;
  int args_count = 0;
  pid_t ret_pid;
  gethostname(host_name, (1024 + 1));
  init_prompt();


  for (;;) {

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
    args_count = parse(input, newargv);

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
        execvp(newargv[0], newargv);
        printf("%s: command not found\n", input);
        return -1;
      }
    }

    if (command == 9)
      command = 0;
    free(input);
  }
  return 0;
}
