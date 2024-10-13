#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	*input;
	char	*prompt;

	(void)ac;
	prompt = calloc(strlen(av[0] + 6), sizeof(char *));
	if (!prompt)
		return (1);
	strcpy(prompt, (av[0] + 2));
	strcat(prompt, "$ > ");
	input = readline(prompt);
	if (input){
		printf("Input was: %s\n", input);
		free(input);
	}
	free(prompt);
}
