#include <stdio.h>
#include <string.h>

// state structure
typedef struct
{
  struct IS
  {
    int pTrans[2];
  } is[20];

} State;

// function prototype
int setMode(char *, char[]);
int isStringAccepted(char *, State *, int, int *, int);
int toInteger(char);

int main()
{

  // initialization
  State states[20];
  int state_count = 0, symbol_tracker = 0, start_state;
  int final_states[20], no_of_final_states = 0, in;
  char mode[20] = "NULL_STATE";
  char input_string[30];
  char c[30];

  // inputs
  FILE *input_file = fopen("input.txt", "r");

  printf("Enter the string: ");
  scanf("%s", input_string);

  // setting default transitions
  for (int i = 0; i < 20; i++)
  {
    for (int i = 0; i < 2; i++)
    {
      states[i].is[i].pTrans[0] = toInteger('-');
      states[i].is[i].pTrans[1] = toInteger('-');
    }
  }

  while (fscanf(input_file, "%s", c) == 1) // fetch each word to c
  {

    if (setMode(mode, c))
    {
      continue;
    }

    if (strcmp(mode, "STATE_FETCH_MODE") == 0)
    {
      if (strlen(c) > 2 && c[1] == ',')
      {
        states[state_count / 2].is[symbol_tracker % 2].pTrans[0] = toInteger(c[0]);
        states[state_count / 2].is[symbol_tracker % 2].pTrans[1] = toInteger(c[2]);
      }
      else
      {
        states[state_count / 2].is[symbol_tracker % 2].pTrans[0] = toInteger(c[0]);
        states[state_count / 2].is[symbol_tracker % 2].pTrans[1] = toInteger('-');
      }

      state_count++;
      symbol_tracker++;
    }
    else if (strcmp(mode, "START_STATE_MODE") == 0)
    {
      start_state = toInteger(c[0]);
    }
    else if (strcmp(mode, "FINAL_STATES_MODE") == 0)
    {
      final_states[no_of_final_states++] = toInteger(c[0]);
    }
  }

  // check if the string accepted
  if (isStringAccepted(input_string, states, start_state, final_states, no_of_final_states))
  {
    printf("%s is accepted.\n", input_string);
  }
  else
  {
    printf("%s is not accepted.\n", input_string);
  }

  return 0;
}

int isStringAccepted(char *input_string, State *states, int current_state, int *final_states, int no_of_final_states)
{

  if (*input_string != '0' && *input_string != '1')
  {
    return 0;
  }

  for (int i = 0; i < 2; i++)
  {
    current_state = states[current_state].is[toInteger(*input_string)].pTrans[i];
    if (current_state == toInteger('-'))
    {
      continue;
    }

    if (isStringAccepted(input_string + 1, states, current_state, final_states, no_of_final_states))
    {
      return 1;
    }

    for (int i = 0; i < no_of_final_states; i++)
    {
      if (current_state == final_states[i])
      {
        return 1;
      }
    }
  }

  return 0;
}

// convert number in ascii to int type
int toInteger(char c)
{
  return c - 48;
}

// Set mode function
int setMode(char *mode, char c1[])
{
  if (strcmp(c1, "STATES:") == 0)
  {
    strncpy(mode, "STATE_FETCH_MODE", 20);
  }
  else if (strcmp(c1, "END") == 0)
  {
    strncpy(mode, "NULL_STATE", 20);
  }
  else if (strcmp(c1, "START_STATE:") == 0)
  {
    strncpy(mode, "START_STATE_MODE", 20);
  }
  else if (strcmp(c1, "FINAL_STATES:") == 0)
  {
    strncpy(mode, "FINAL_STATES_MODE", 20);
  }
  else
  {
    return 0;
  }

  return 1;
}
