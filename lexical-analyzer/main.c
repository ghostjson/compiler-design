#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int isOperator(char c)
{
  char operators[] = {'*', '/', '-', '+', '=', '%', '>', '<', '(', ')'};

  for (int i = 0; i < strlen(operators); i++)
  {
    if (c == operators[i])
    {
      return 1;
    }
  }

  return 0;
}

int isKeyword(char *str)
{
  char *keywords[] = {"if", "else", "while", "void", "int", "float", "static", "function", "struct", "return", "print"};

  for (int i = 0; i < 11; i++)
  {
    if (strcmp(str, keywords[i]) == 0)
    {
      return 1;
    }
  }

  return 0;
}

int isNumber(char *str)
{
  for (int i = 0; i < strlen(str); i++)
  {
    if (!isdigit(str[i]))
    {
      return 0;
    }
  }

  return 1;
}

int isString(char *str)
{
  return str[0] == '"' && str[strlen(str) - 1] == '"';
}

int isDeliminator(char c)
{

  char delims[] = {';', ',', ']', '[', '{', '}', ' ', '+', '-', '*', '/', '=', '(', ')', '<', '>', '\n', '\r'};

  for (int i = 0; i < strlen(delims); i++)
  {
    if (c == delims[i])
    {
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{

  if (argc == 1)
  {
    printf("Path of the file is not given!\n");
    return 1;
  }

  char inputFile[1024];
  char buffer[1024];
  char c;

  int buffCursor = 0;
  FILE *file = fopen(argv[1], "r");

  while (fgets(inputFile, 1024, file))
  {

    for (int i = 0; i < strlen(inputFile); i++)
    {
      c = inputFile[i];

      if (isDeliminator(c))
      {
        if (isKeyword(buffer))
        {
          printf("%s is a keyword\n", buffer);
        }
        else if (buffCursor != 0)
        {

          if (isNumber(buffer))
          {
            printf("%s is a number\n", buffer);
          }
          else if (isString(buffer))
          {
            printf("%s is a string\n", buffer);
          }
          else
          {
            printf("%s is a identifier\n", buffer);
          }
        }

        buffCursor = 0;
        buffer[buffCursor] = '\0';
      }
      else
      {
        buffer[buffCursor++] = c;
        buffer[buffCursor] = '\0';
      }

      if (isOperator(c))
      {
        printf("%c is an operator\n", c);
      }
    }
  }

  fclose(file);

  return 0;
}