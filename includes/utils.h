#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "tokenization.h"
# include <stdbool.h>

char	*ft_substr(char const *s, unsigned int start, size_t len, bool is_op);
int	ft_isspace(char c);
int	ft_is_operator(char *s, int i);
int	ft_isalpha(int c);
size_t	ft_strlen(const char *s);
void	print_token_list(t_token *token_list);
void	ft_token_list_clear(t_token **lst);
int	ft_strcmp(char *s1, char *s2);
void dolarni(t_token **tokens, char **env);
char	*ft_strjoin(char const *s1, char const *s2, char sep);
char	*join(char const *s1, char const *s2);

#endif