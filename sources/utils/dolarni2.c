#include "tokenization.h"
#include "utils.h"

void kp(char *begin, char *word, char *end, t_token **current)
{
	char *final;

	final = join(begin, word, 0, 0);
	// printf("begin -> %s, word-> %s,end -> %s\n", begin, word, end);
	free((*current)->value);
	(*current)->value = join(final, end, 0, 0);
	// printf("value -> %s\n", (*current)->value);
	free(final);
	free(word);
	if (begin != NULL)
	{
	free(begin);
	begin = NULL;
	}
	if (end != NULL)
	{
		free(end);
		end = NULL;
	}
}

char *open_dollar(char *dollar, char **env, bool flag, int *k)
{
	char *word;
	char *envp;
	int i;
	int j;

	word = NULL;
	i = 0;
	if (flag == true)
		return (ft_strdup("$"));
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		envp = ft_substr(env[i], 0, j, false);
		if (ft_strcmp(dollar, envp) == 0)
		{
			word = ft_substr(env[i], j + 1, ft_strlen(env[i]), true);
			*k += 0;
			free(envp);
			return (word);
		}
		free(envp);
		i++;
	}
	return(word);
}

void veragrum(char **begin, char **word, char **end, char **dollar)
{
	*begin = NULL;
	*word = NULL;
	*end = NULL;
	*dollar = NULL;
}

void qt_check_for_dollar(bool *d_qt, bool *qt, char *value, int i)
{
	if (value[i] == 34 && *qt == false)
		*d_qt = !*d_qt;
	if (value[i] == 39 && *d_qt == false)
		*qt = !*qt;
}

void dolarni2(t_token **token_list, char **env, bool flag, bool flag_a)
{
	t_token *current;
	int i;
	int j;
	char *word;
	char **parts;
	bool qt = false;
	bool double_qt = false;

	current = *token_list;
	while(current)
	{
		if ((current->type == WORD || (current->type >= 12 && current->type <= 16)) && current->type != LIMITER)
		{
			i = 0;
			while(current->value && current->value[i])
			{
				qt_check_for_dollar(&double_qt, &qt, current->value, i);
				if (current->value[i] == '$' && qt == false)
				{
					if (current->value[i + 1] && current->value[i + 1] == '?')
					{
						free(current->value);
						current->value = ft_itoa(g_exit_status);
						break ;
					}		
					j = i;
					while (current->value[j] && (ft_isspace(current->value[j]) != 1 &&
					current->value[j] != 34 && current->value[j] != 39))
					{
						j = j + 1;
						if (current->value[j] == '$' || current->value[j] == '/' || current->value[j] == '=')
							break ;
					}
					if (j == i + 1)
						flag = true;
					parts = karch2(current->value, i, j, strlen(current->value));
					word = open_dollar(parts[1], env, flag, &i);
					kp(parts[0], word, parts[2], &current);
					karch3(parts[1], parts, &flag);
				}
				if (current->value[0] != '\0')
					i++;
			}
		}
		current = current->next;
		flag_a = false;
	}
	free_env(env);
}

char	*foo(void)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * 2);
	ptr[0] = 48;
	ptr[1] = '\0';
	return (ptr);
}

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	long	long_n;

	if (n == 0)
		return (foo());
	len = ft_len(n);
	arr = malloc(sizeof(char) *(len + 1));
	if (!arr)
		return (NULL);
	long_n = (long)n;
	arr[len] = '\0';
	len--;
	if (n < 0)
	{
		arr[0] = '-';
		long_n = -long_n;
	}
	while (long_n != 0)
	{
		arr[len--] = ((long_n % 10) + 48);
		long_n /= 10;
	}
	return (arr);
}