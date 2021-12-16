#include <stdio.h>

int main()
{

  int no_of_states, no_of_final_states, no_of_input_symbols, tracker, current_state = 0;
  int input_symbols[30], final_states[30], in;
  int transitions[30][30];
  char string[30];

  printf("Enter total number of states: ");
  scanf("%d", &no_of_states);

  printf("Enter total number of final states: ");
  scanf("%d", &no_of_final_states);

  if (no_of_states < no_of_final_states)
  {
    printf("Error: Number of states should be greater than number of final states.");
    return 1;
  }

  printf("Enter number of input symbols: ");
  scanf("%d", &no_of_input_symbols);

  for (int i = 0; i < no_of_input_symbols; i++)
  {
    printf("Enter input symbol no %d: ", i + 1);
    scanf("%d", &input_symbols[i]);
  }

  for (int i = 0; i < no_of_final_states; i++)
  {
    printf("Enter final state %d: ", i + 1);
    scanf("%d", &final_states[i]);
  }

  printf("\nEnter transitions: \n");
  for (int i = 0; i < no_of_states; i++)
  {
    for (int j = 0; j < no_of_input_symbols; j++)
    {
      printf("δ(q%d,%d) --> ", i + 1, input_symbols[j]);
      scanf("%d", &(transitions[i][input_symbols[j]]));
    }
  }

  printf("\nEnter a string: ");
  scanf("%s", string);

  tracker = 0;
  in = string[tracker];

  while (in != '\0')
  {

    int previous_state = current_state;
    current_state = transitions[current_state][in - 48];

    tracker++;
    in = string[tracker];
  }

  for (int i = 0; i < no_of_final_states; i++)
  {
    if (final_states[i] == current_state)
    {
      printf("String %s is accepted\n", string);
      return 0;
    }
  }

  printf("String %s is not accepted\n", string);

  return 0;
}