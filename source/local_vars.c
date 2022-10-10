#include "stdio.h"
#include "string.h"
static unsigned int eqn_count = 0;
static unsigned int duplicate_count = 0;
static unsigned int variable_count = 0;
static unsigned int values_count = 0;


int check_variable (char *line)
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

int search (char **a, char *key)
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

void save_variable (char *line, char **variables, char **values)
{

  char *token = strtok (line, " = ");
  while (token != NULL)
    {
      if (eqn_count % 2 == 0)
	{
	  int searched_index = search (variables, token);
	  if (searched_index >= 0)
	    {
	      token = strtok (NULL, " = ");
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


      token = strtok (NULL, " = ");

      eqn_count++;
    }

}

void print_variables (char **variables, char **values)
{

  for (int i = 0; i < (eqn_count / 2) - duplicate_count; i++)
    {
      printf ("Local Variable[%d] : %s=%s \n", i, variables[i], values[i]);
    }


}

