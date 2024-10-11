# Minishell

**42 Introduction:**
>The existence of shells is linked to the very existence of IT.
At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating.
It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.
Thanks to Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.



##### Index
###### [Functions](#functions)



## Mandatory



  **Your shell should:**

• Display a prompt when waiting for a new command.

• Have a working history.

• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path)

• Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.

>**Be careful. This global variable cannot provide any other
information or data access than the number of a received signal.
Therefore, using "norm" type structures in the global scope is
forbidden.
• Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).**


• Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.

• Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).

• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.

• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.

• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.


• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options


## Functions
[Back to top](#index)
| Library   | Functions |
|-----------|-----------|
| **unistd.h**  | [access](#access), [fork](#fork), read, write, open, close, wait, waitpid, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot |
| **wait.h** |wait3, wait4|
| **stdio.h**| printf, readline |
| **stdlib.h** | malloc, free, exit, getenv |
| **dirent.h** | opendir, readdir, closedir |
| **string.h** | strerror, perror |
| **termios.h** | tcsetattr, tcgetattr |
| **term.h**| tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| **signal.h**  | signal, sigaction, sigemptyset, sigaddset, kill |
| **sys/stat.h**| stat, lstat, fstat |
|**stropts.h**| ioctl|


### unistd.h


#### access
[Back to top](#index)

**determine accessibility of a file descriptor**

***access definition in unistd.h***
```c
/* Values for the second argument to access.
   These may be OR'd together.  */
#define	R_OK	4		/* Test for read permission.  */
#define	W_OK	2		/* Test for write permission.  */
#define	X_OK	1		/* Test for execute permission.  */
#define	F_OK	0		/* Test for existence.  */

/* Test for access to NAME using the real UID and real GID.  */
extern int access (const char *__name, int __type) __THROW __nonnull ((1));

```
```c
int		main(void)
{
	int		res[3];
	int		i;

	res[0] = access("/bin/ls", 0);	//Returns 0, as right execution
	res[1] = access("ls", 0);	//Without the absolute path returns an error
	res[2] = access("/bin/cd", 0);	//Since the "cd" command doesn't exist in the /bin, returns an error
	for(i = 0; i < 3; i++)
		printf("Access return: %i\n", res[i]);
}
```

![access](./functions/prints/access.png)
___

#### fork
[Back to top](#index)

**create a new process**

***fork definition in the unistd.h***
```c
/* Clone the calling process, creating an exact copy.
   Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
extern __pid_t fork (void) __THROWNL;
```

```c
int	main()
{
	pid_t	pid;

	printf("Fork no wait call\n\n");
	pid = fork();
	if (pid == 0) // If it's the child proccess
		printf("I'm the child!\n");
	else
		printf("I'm the parent!\n");
}
```
![out](./functions/prints/fork1.png)
___

```c
int	main()
{
	pid_t	pid;

	printf("Fork wait for child call\n\n");
	pid = fork();
	if (pid != 0) // If it's not the child
	{
		wait(NULL);
		printf("I've been waiting my child!\n");
	}
	else
		printf("Parent process will wait for me!\n");
}
```
![fork2](./functions/prints/fork2.png)



### wait.h
[Back to top](#index)

wait3, wait4



### signal.h
[Back to top](#index)
	signal, sigaction, sigemptyset, sigaddset, kill



### stdlib.h
[Back to top](#index)
	exit, getenv




### stat.h
[Back to top](#index)
		stat, lstat, fstat



### dirent.h
[Back to top](#index)
		opendir, readdir, closedir



### string.h
[Back to top](#index)
		strerror



### stdio.h
[Back to top](#index)
		readline, perror, printf



### stropts.h
[Back to top](#index)
		ioctl



### termios.h
[Back to top](#index)
		tcgetattr, tcsetattr,



### curses.h / term.h
[Back to top](#index)
		tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs





