#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

extern int	g_exit_status;

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char*)b;
	while (len-- > 0)
		*(ptr++) = (unsigned char)c;
	return (b);
}

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)//tcgetattr считывает текущие параметры терминала, связанного с файловым дескриптором STDIN_FILENO (стандартный ввод), и сохраняет их в структуру term.
		return ;
	term.c_lflag &= ~(ECHOCTL);//&= ~(ECHOCTL) գործողությունը մաքրում է ECHOCTL դրոշը, դրանով իսկ անջատելով այս կառավարման նիշերի ցուցադրումը:
	tcsetattr(STDIN_FILENO, TCSANOW, &term);//Функция tcsetattr устанавливает новые параметры терминала, которые находятся в структуре term.
											// STDIN_FILENO указывает, что настройки применяются к стандартному вводу (обычно клавиатуре).
											// TCSANOW указывает, что изменения должны быть применены немедленно.
}

void	ctrl_d(int sig)
{
	(void)sig;
	rl_on_new_line();//nor readline-i toxa tali//сообщает библиотеке Readline, что текущая строка ввода завершена и нужно начать новую строку//MINIVIBERSEIJ:-i masina xosqy
	rl_replace_line("", 0);// используется для замены текущей строки ввода на указанную строку, arajiny Указатель на строку, которая заменит текущую строку ввода.ete datarki texy grenq Anri apa ctrl c enluc kberi taza tox senc-MINIVIBERSEIJ: Anri,dnum enq datark vor Anrin chlni
	rl_redisplay();//используется для перерисовки строки ввода esi vor chlni ctrl c aneluc en mer MINIVIBERSEIJ:-@ chi grvi minchev hraman chgrenq
	rl_cleanup_after_signal();// используется для очистки внутреннего состояния библиотеки Readline после обработки сигнала. Это помогает предотвратить некорректное поведение и утечки памяти, которые могут возникнуть, если сигнал прерывает ввод пользователя.
}

void	ctrl_bckslash(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

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

void	set_singals(void)
{
	choose_signal(ctrl_c, 0);
	choose_signal(ctrl_d, 1);
}
