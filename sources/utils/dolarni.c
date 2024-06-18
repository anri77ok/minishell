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
	char *end = NULL;
	char *final = NULL;
	bool qt = false;
	bool double_qt = false;
	bool is_valid = false;
	bool more_dollars;

	current = *tokens;
	while(current)
	{
		if (current->type == WORD || (current->type >= 12 && current->type <= 16))
		{
			i = 0;
			while(current->value[i])
			{
				if (current->value[i] == 34 && qt == false)
					double_qt = !double_qt;
				if (current->value[i] == 39 && double_qt == false)
					qt = !qt;
				if (current->value[i] == '$' && qt == false)
				{
					j = i;
					while (current->value[j] && (ft_isspace(current->value[j]) != 1 &&
					 current->value[j] != 34 && current->value[j] != 39))
					{
						j++;
						if (current->value[j] == '$')
						{
							if (i > 0)
								begin = ft_substr(current->value, 0, i, true);
							dollar = ft_substr(current->value, i + 1, j, true);
							end = ft_substr(current->value, j, ft_strlen(current->value) - j, false);
							more_dollars = true;
						}
					}
					if (more_dollars == false)
					{
						dollar = ft_substr(current->value, i + 1, j, true);
						end = ft_substr(current->value, j, ft_strlen(current->value) - j, false);
						if (i > 0)
							begin = ft_substr(current->value, 0, i, true);
					}
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
						final = join(begin, word);
						current->value = join(final, end);
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
						is_valid = true;
						break ;
					}
					free(envp);
				i++;
				}
				if (is_valid == false)
				{
					free(current->value);
					if (ft_strcmp(dollar, "") == 0)
					{
						word = ft_strdup("$");
						final = join(begin, word);
						current->value = join(final, end);
					}
					else
						current->value = join(begin, end);
					if (final != NULL)
					{
						free(final);
						free(word);
					}
					free(begin);
					free(end);
				}
				free(dollar);
				dollar = NULL;
			}
		}
		printf("%s\n", current->value);
		if (more_dollars == true)
			more_dollars = false;
		else
			current = current->next;
	}
}
