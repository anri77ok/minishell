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
void dolarni2(t_token **tokens, char **env);
char	*ft_strjoin(char const *s1, char const *s2, char sep);
char	*join(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*ft_strstr(char *str, char *to_find);


//spliti hamar
char	**ft_split(char const *s, char c);

//lst_func
t_env_elem	*ft_lstnew_dlya_env(char *key, char *value);
t_env_elem	*ft_lstlast(t_env_elem *lst);
void	ft_lstadd_back_env(t_env_elem **lst, t_env_elem *new);

int print_env(t_env_elem *env, int *is_builtin);
#endif