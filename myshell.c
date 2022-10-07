#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define RESET "\x1B[0m"
#define BUFFER_SIZE 50
char history[10][BUFFER_SIZE];
char *variables[64];
char *values[64];
int eqn_count = 0;
int duplicate_count = 0;
unsigned variable_count = 0;
unsigned values_count = 0;

int
parse (char *line, char **argv)
{
  int argc = 0;
  while (*line != '\0')
    {				/* if not the end of line ....... */
      while (*line == ' ' || *line == '\t' || *line == '\n')
	*line++ = '\0';		/* replace white spaces with 0    */
      *argv++ = line;		/* save the argument position     */
      argc++;
      while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
	line++;			/* skip the argument until ...    */
    }
  *argv = '\0';			/* mark the end of argument list  */

  return argc;
}

int
check_variable (char *line)
{

  for (int i = 0; line[i] != '\0'; i++)
    {
      if (line[i] == '=')
	{
	  return 1;
	}

    }
  return 0;

}

int
search (char **a, char *key)
{

  for (int i = 0; i < (eqn_count / 2) - duplicate_count; i++)
    {
      if (!strcmp (a[i], key))
	{
	  return i;
	}

    }

  return -1;

}

void
save_variable (char *line, char **variables, char **values)
{

  char *token = strtok (line, "= ");
  while (token != NULL)
    {
      if (eqn_count % 2 == 0)
	{
	  int searched_index = search (variables, token);
	  if (searched_index >= 0)
	    {
	      token = strtok (NULL, "= ");
	      eqn_count++;
	      duplicate_count++;
	      values[searched_index] = token;
	    }
	  else
	    {

	      variables[variable_count++] = token;
	    }
	}
      else
	{

	  values[values_count++] = token;
	}


      token = strtok (NULL, "= ");

      eqn_count++;
    }

}

void
print_variables (char **variables, char **values)
{

  for (int i = 0; i < (eqn_count / 2) - duplicate_count; i++)
    {
      printf ("Local Variable[%d] : %s=%s \n", i, variables[i], values[i]);
    }


}

void
printHistory ()
{
  int i;
  for (i = 0; i < 10; i++)
    {
      if (!strcmp (history[i], ""))
	continue;
      printf ("\n%d)", i + 1);
      printf ("%s", history[i]);
    }
  printf ("\n");
  printf ("%s%s:~%s%s$ %s", KMAG, getenv ("USER"), KCYN, getcwd (NULL, 1024),
	  RESET);
}




int
main ()
{


  char *input, shell_prompt[100];
  char *newargv[64];
  pid_t ret_pid;
  // Configure readline to auto-complete paths when the tab key is hit.
  rl_bind_key ('\t', rl_complete);
  rl_bind_keyseq ("\\e[A", (int (*)(int, int)) printHistory);


  int command = 0;
  int args_count = 0;
  for (;;)
    {

      // Create prompt string from user name and current working directory.
      snprintf (shell_prompt, sizeof (shell_prompt), "%s%s:~%s%s$ %s", KMAG,
		getenv ("USER"), KCYN, getcwd (NULL, 1024), RESET);

      // Display prompt and read input (NB: input must be freed after use)...
      input = readline (shell_prompt);
      args_count = parse (input, newargv);
      // Check for EOF.
      if (!input)
	break;
      if (!strcmp (input, ""))
	continue;



      if (!strcmp (newargv[0], "export"))
	{

	  for (int i = 1; i <= args_count-1; i++)
	    {
	      int searched_index = search (variables, newargv[i]);
	      if (searched_index >= 0)
		{
		  setenv (variables[searched_index], values[searched_index], 1);
		}
	      else
		{
		  printf
		    ("Couldn't Export variable%s.The Variable doesn't exist.\n",
		     newargv[i]);
		  break;
		}

	    }
	  continue;
	}
      else if (!strcmp (newargv[0], "set"))
	{
	  print_variables (variables, values);
	  strcpy (history[command++], input);
	  continue;
	}
      else if (check_variable (input))
	{
	  save_variable (input, variables, values);

	  continue;
	}

      strcpy (history[command++], input);
      if (command == 9)
	command = 0;
      ret_pid = fork ();
      if (ret_pid < 0)
	printf ("Fork Failed\n");
      else if (ret_pid > 0)
	{
	  int status;
	  wait (&status);
	}
      else
	{
	  execvp (newargv[0], newargv);
	  printf ("Exec Failed\n");
	  return -1;
	}
      free (input);
    }
  return 0;
}
