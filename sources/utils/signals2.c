#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	choose_signal(void (*f), int flag)
{
	struct sigaction	sa;

	if (flag == 0)
		ctrl_bckslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = f;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (flag == 0)
		sigaction(SIGINT, &sa, NULL);
	else if (flag == 1)
		sigaction(SIGQUIT, &sa, NULL);
	disable_echoctl();
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char*)b;
	while (len-- > 0)
		*(ptr++) = (unsigned char)c;
	return (b);
}