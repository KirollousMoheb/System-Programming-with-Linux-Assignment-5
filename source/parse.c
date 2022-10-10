#include "../includes/parse.h"
int parse (char *line, char **argv)
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
