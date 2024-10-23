#include "minishell.h"

void	terminal_configs(t_tty *term)
{
	if (term->fd < 0)
		return ;
	if (tcgetattr(term->fd, &(term->termios)))
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term->termios.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(term->fd, TCSANOW, &(term->termios)))
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	term_emulator(t_tty *term)
{
	char	*start;

	term->type = getenv("TERM");
	if (!term->type)
	{
		write(2, "No TERM in the env\n", 19);
		exit(EXIT_FAILURE);
	}
	if (tgetent(term->buff, term->type) < 1)
	{
		write(2, "Termcap database not accessible\n", 32);
		exit(EXIT_FAILURE);
	}
	start = tgetstr("cl", NULL); // to check capabilities
	if (start)
	{
		tputs(start, 1, putchar);
		printf("HEY\n\n");
	}
}

int	open_tty(t_tty *term)
{

	term->fd = open("/dev/tty", O_RDWR, 0666);
	if (term->fd < 0)
	{
		printf("Failed to open terminal\n");
		exit(EXIT_FAILURE);
	}
	if (isatty(term->fd)){
		terminal_configs(term);
		term_emulator(term);
		printf("minishell is a tty!\n");
		printf("Terminal configured\n");
	}
	else
		printf("minishell is not a tty!\n");
	printf("Fildes minishell: %i\n\n", term->fd);
	return (term->fd);
}

int	main()
{
	t_tty	term;

	term.fd = open_tty(&term);
	printf("%i\n", term.fd);
	close(term.fd);
}
