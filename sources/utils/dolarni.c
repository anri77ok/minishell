#include "tokenization.h"
#include "utils.h"

void dolarni(t_token **tokens, char **env)
{
	t_token *current;
	int i;
	int j;
	char *dollar = NULL;
	char *envp;
	char *begin = NULL;
	char *word = NULL;
	//char *end = NULL;

	i = 0;
	current = *tokens;
	while(current)
	{
		if (current->type == WORD)
		{
			while(current->value[i])
			{
				if (current->value[i] == '$')
				{
					j = i;
					while (current->value[j] && ft_isspace(current->value[j]) != 1)
						j++;
					dollar = ft_substr(current->value, i + 1, j, true);
					if (i > 0)
						begin = ft_substr(current->value, 0, i, true);
					j = skip_whitespaces(current->value, j);
				}
				i++;
			}
			i = 0;
			if (dollar != NULL)
			{
				while (env[i])
				{
					j = 0;
					while (env[i][j] && env[i][j] != '=')
						j++;
					envp = ft_substr(env[i], 0, j, false);
					if (ft_strcmp(dollar, envp) == 0)
					{
						free(current->value);
						word = ft_substr(env[i], j + 1, ft_strlen(env[i]), true);
						if (begin != NULL)
						{
							current->value = join(begin, word);
							free(word);
						}
						else
							current->value = word;
						break ;
					}
					free(envp);
				i++;
				}
				free(dollar);
				dollar = NULL;
			}
		}
		current = current->next;
	}
}
