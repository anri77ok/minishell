#include "tokenization.h"
#include "utils.h"

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

int	ft_is_operator(char *s, int i)
{
	int	op_len;

	if (s[i] == '|' || s[i] == '&' || s[i] == '>' || s[i] == '<')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			op_len = 2;
		else
			op_len = 1;
	}
	else
		op_len = 0;
	return (op_len);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	while (token_list)
	{
		printf("\033[0;035m token -> \033[0;034m%s \033[0;031m | \033[0;032m       value -> \033[0;033m(%s)\033[0m\n",
			str_type(token_list->type), token_list->value);
		token_list = token_list->next;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len, bool is_op)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (s == NULL)
		return ("");
	if (is_op == true)
		len = len - start;
	if (len <= ft_strlen(s))
		str = (char *) malloc(sizeof(char) * (len + 1));
	else
		str = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*str_type(int token_type)
{
	if (token_type == 0)
		return ("WORD          ");
	else if (token_type == 1)
		return ("S_PIPE        ");
	else if (token_type == 2)
		return ("D_PIPE        ");
	else if (token_type == 3)
		return ("S_AND         ");
	else if (token_type == 4)
		return ("D_AND         ");
	else if (token_type == 5)
		return ("D_QUOTE       ");
	else if (token_type == 6)
		return ("S_QUOTE       ");
	else if (token_type == 7)
		return ("IN_REDIR      ");
	else if (token_type == 8)
		return ("OUT_REDIR     ");
	else if (token_type == 9)
		return ("HERE_DOC      ");
	else if (token_type == 10)
		return ("APPEND_REDIR  ");
	else if (token_type == 11)
		return ("ERROR         ");
	else if (token_type == 12)
		return ("NONE          ");
	else if (token_type == 13)
		return ("FILEIN        ");
	else if (token_type == 14)
		return ("LIMITER       ");
	else if (token_type == 15)
		return ("FILEOUT       ");
	else if (token_type == 16)
		return ("APPEND_FILEOUT");
	else if (token_type == 17)
		return ("OPEN_PAR      ");
	else if (token_type == 18)
		return ("CLOSE_PAR     ");
	else
		return ("\033[0;031mTOKEN_TYPE_NOT_FOUND");
}

void	ft_token_list_clear(t_token **lst)
{
	t_token	*tmp;
	t_token	*last;

	if (!lst)
		return ;
	last = *lst;
	while (last)
	{
		tmp = last->next;
		free(last->value);
		free(last);
		last = tmp;
	}
	*lst = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2, char sep)
{
	char	*r_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!r_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	r_s[j++] = sep;
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
}

char	*join(char *s1, char *s2)
{
	char	*r_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	if (!src)
		return (NULL);
	while (src[size])
		++size;
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (*to_find == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == 0)
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}