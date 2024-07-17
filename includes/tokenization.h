#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <unistd.h>

typedef struct s_token	t_token;

/*
WORD
S_PIPE - |
D_PIPE - ||
S_AND - &
D_AND - &&
D_QUOTE - "
S_QUOTE - '
IN_REDIR - <
OUT_REDIR - >
HERE_DOC - <<
APPEND_REDIR - >>
ERROR
NONE
*/
typedef enum e_token_type
{
	WORD,
	S_PIPE,
	D_PIPE,
	S_AND,
	D_AND,
	D_QUOTE,
	S_QUOTE,
	IN_REDIR,
	OUT_REDIR,
	HERE_DOC,
	APPEND_REDIR,
	ERROR,
	NONE,
	FILEIN,
	LIMITER,
	FILEOUT,
	APPEND_FILEOUT,
}	t_token_type;

typedef struct s_token_params
{
	short	cmd_found;
	short	redir;
}	t_token_params;

typedef struct s_fds
{
	int	infd;
	int	outfd;
	int	second_case;
}	t_fds;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				flag;
	t_token			*next;
	t_token			*prev;
}	t_token;


int tokenization(char *cmd_line, t_token **tokens);
int skip_whitespaces(char *line, int i);
t_token *create_new_token(char *value);
int is_quote(char *cmd_line, int i);
char	*str_type(int token_type);
t_token_type set_token_type(char *value, int i);
void	tokens_types(t_token *tokens);
void chakertni(t_token **tokens);
//itoa
char	*foo(void);
int	ft_len(int n);
char	*ft_itoa(int n);


//datark nodery jnjelu hamar
void	get_bez_empty_nodes(t_token **token_list);
void	delete_this_node(t_token	**token_list, int pos);
void	middle_node(t_token **token_list, int pos);
int	count_nodes_func(t_token	*token_list);
int	check_value_is_empty(char	*value);


//echo
// void    echo(char **cmd_args, int fd);
int    echo(char **cmd_args, int fd, int *is_builtin);
void    fd_put_string(char *str, int fd);
void	echo_run_helper(char **cmd_args, int i, int fd, int ind);
void	write_helper(char **cmd_args, int ind, int fd, int flag);

//pwd
int    pwd(int fd, int *is_builtin);


int	check_is_ambiguous(t_token *cmd);
#endif