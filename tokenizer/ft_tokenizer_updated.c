#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	size_t	j;
	size_t	index;
	size_t	i;
	size_t	count;
	size_t	k;
	int		error_token;
	char	c;
	char	*input;
	char	**tokens;
}			t_Tok;

void	ft_free(t_Tok *token, int error)
{
	int	i;

	if (token)
	{
		if (token->tokens)
		{
			i = 0;
			while (token->tokens[i])
			{
				free(token->tokens[i]);
				i++;
			}
		}
		free(token->tokens);
		free (token);
	}
	if (error == 0)
	{
		printf("The Malloc Not Located\n");
		exit (0);
	}
}

void    *ft_calloc(size_t count, size_t size)
{
    unsigned char   *p;
    void    		*pa;
    size_t			i;

    i = 0;
    pa = malloc(count * size);
    if (!pa)
        return (NULL);
    p = pa;
    while (i < (count * size))
    {
        p[i] = 0;
        i++;
    }
    return (pa);
}

void	initialize(t_Tok *token)
{
	token->i = 0;
	token->index = 0;
	token->j = 0;
	token->count = 0;
	token->k = 0;
	token->error_token = 1;
	token->c = '\0';
	token->input = NULL;
	token->tokens = NULL;
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	comper(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '$')
		return (1);
	return (0);
}

void	string(t_Tok *token)
{
	while (!(comper(token->input[token->i])))
		{
			if ((token->input[token->i] == '"' || token->input[token->i] == '\'') && token->input[token->i - 1] != '\\')
			{
				token->c = token->input[token->i];
				token->i++;
				while ((token->input[token->i] != token->c || (token->input[token->i] == token->c && token->input[token->i - 1] == '\\')) && token->input[token->i] != '\0')
					token->i++;
			}
			if (token->input[token->i] == '\0')
			{
				token->i--;
				token->error_token = 2;
			}
			if (comper(token->input[token->i + 1]))
				token->index++;
			token->i++;
		}
}

void	pipe(t_Tok *token)
{
	if (token->input[token->i] == '|')
		{
			token->i++;
			token->index++;
		}
}

void	dollar(t_Tok *token)
{
	if (token->input[token->i] == '$')
		{
			token->i++;
			token->index++;
		}
}

void	fill_token(t_Tok *token)
{
	if (token->index > token->k)
		{
			token->tokens[token->k] = ft_calloc((token->i - token->count + 1), sizeof(char));
			if (!token->tokens[token->k])
				ft_free(token, 0);
			token->j = 0;
			while (token->count < token->i)
			{
				token->tokens[token->k][token->j] = token->input[token->count];
				token->count++;
				token->j++;
			}
			token->tokens[token->k][token->j] = '\0';
		}
}

size_t	count(t_Tok *token)
{
	while (token->input[token->i] != '\0')
	{
		while (token->input[token->i] == ' ' || token->input[token->i] == '\t')
		{
			token->i++;
		}
		string(token);
		pipe(token);
		greater(token);
		dollar(token);
	}
	return (token->index++);
}

void	fill_tokens(t_Tok *token)
{
	while (token->input[token->i] != '\0')
	{
		while (token->input[token->i] == ' ' || token->input[token->i] == '\t')
			token->i++;
		token->k = token->index;
		token->count = token->i;
		string(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		pipe(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		greater(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		dollar(token);
		fill_token(token);
	}
}

char	**ft_tokenizer(char *input, t_Tok *token)
{
	//t_Tok	*token;
	size_t	i;

	//token = (t_Tok *)malloc(sizeof(t_Tok));
    //if (!token)
		//exit (0);
	initialize(token);
	token->input = input;
	i = count(token);
	printf("%ld\n", i);
	printf("%i\n", token->error_token);
	initialize(token);
	token->tokens = ft_calloc(i + 1, sizeof(char*));
	if (!(token->tokens))
		ft_free(token, 0);
	token->input = input;
	fill_tokens(token);
	token->tokens[i] = NULL;
	return (token->tokens);       
}
int	main(void)
{
	t_Tok	*token;

	token = (t_Tok *)malloc(sizeof(t_Tok));
    if (!token)
		exit (0);
	token->tokens = ft_tokenizer("123$123 | $HOME$WO$1RLD$$$", token);
	int i = 0;
	while (token->tokens[i])
	{
		printf("%d) %s\n", i, token->tokens[i]);
	       i++;
	}
	ft_free(token, 1);
	return (0);
}
/*int	main(int argc, char **argv)
{
	argc = argc + 1 - 1;
	char	**array;
	char 	*line;
	(void) argv;
	while (1)
	{
		line = readline("ali: ");
		array = ft_tokenizer(line);
		int i = 0;
		while (array[i])
		{
			printf("%d) %s\n", i, array[i]);
			i++;
		}
		free(array);
	}
	return (0);
}*/
