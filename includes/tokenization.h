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
	t_token			*next;
	t_token			*prev;
}	t_token;


void tokenization(char *cmd_line, t_token **tokens);
int skip_whitespaces(char *line, int i);
t_token *create_new_token(char *value);
int is_quote(char *cmd_line, int i);
char	*str_type(int token_type);
t_token_type set_token_type(char *value, int i);
void	tokens_types(t_token *tokens);
void chakertni(t_token **tokens);

#endif