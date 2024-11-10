#include "../inc/minishell.h"

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	while (cmd)
	{
		tmp = cmd->next;	
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		//free(cmd->path);
		//free_doubles((void **)cmd->env);
		free(cmd);
		cmd = tmp;
	}
	if (i)
	{
		if (terminal()->env)
			free_doubles((void**)terminal()->env);
		exit(0);
	}
}

/*limpo
==138757== 
==138757== HEAP SUMMARY:
==138757==     in use at exit: 208,385 bytes in 235 blocks
==138757==   total heap usage: 551 allocs, 316 frees, 233,815 bytes allocated
==138757== 
==138757== 16 bytes in 1 blocks are definitely lost in loss record 10 of 69
==138757==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==138757==    by 0x4014F0: ft_calloc (alloc.c:63)
==138757==    by 0x401A64: ft_strdup (dup_split.c:52)
==138757==    by 0x4012EE: main (main.c:55)
==138757== 
==138757== LEAK SUMMARY:
==138757==    definitely lost: 16 bytes in 1 blocks
==138757==    indirectly lost: 0 bytes in 0 blocks
==138757==      possibly lost: 0 bytes in 0 blocks
==138757==    still reachable: 0 bytes in 0 blocks
==138757==         suppressed: 208,369 bytes in 234 blocks
==138757== 
==138757== For lists of detected and suppressed errors, rerun with: -s
==138757== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
*/