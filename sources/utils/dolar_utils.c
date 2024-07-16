#include "tokenization.h"
#include "utils.h"

extern int	g_exit_status;

void karch(char *value, int *i, int *j, bool *flag_a)
{
	if (value[*i + 1] && value[*i + 1] == '?')
	{
		free(value);
		value = ft_itoa(g_exit_status);
		*flag_a = true;
	}		
	*j = *i;
	while (value[*j] && (ft_isspace(value[*j]) != 1 &&
	value[*j] != 34 && value[*j] != 39))
	{
		*j = *j + 1;
		if (value[*j] == '$' || value[*j] == '/' || value[*j] == '=')
			*flag_a = true;
	}
}

void free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char **karch2(char *value, int start, int mid, int end)
{
	char **arr;
	arr = NULL;

	arr = malloc(sizeof(char *) * 4);
	arr[0] = ft_substr(value, 0, start, true);
	arr[1] = ft_substr(value, start + 1, mid, true);
	arr[2] = ft_substr(value, mid, end - mid, false);
	arr[3] = NULL;
	return (arr);
}

void karch3(char *p1, char **p, bool *flag)
{
	free(p1);
	free(p);
	*flag = false;
}