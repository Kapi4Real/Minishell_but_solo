#include <minishell.h>
#include <stdlib.h>
#include <string.h>

static void	create_token(t_tokenizer *tk)
{
	if (tk->pos_buffer > 0)
	{
		tk->buffer[tk->pos_buffer] = '\0';
		tk->tab[tk->pos_tab] = strdup(tk->buffer);
		tk->pos_tab++;
		tk->pos_buffer = 0;
	}
}

static int	init_tokenizer(t_tokenizer *tk, char *input)
{
	tk->input = input;
	tk->state = OUTSIDE;
	tk->buffer = malloc(sizeof(char) * 100);
	if (!tk->buffer)
		return (0);
	tk->tab = malloc(sizeof(char *) * 100);
	if (!tk->tab)
	{
		free(tk->buffer);
		return (0);
	}
	tk->pos_input = 0;
	tk->pos_buffer = 0;
	tk->pos_tab = 0;
	return (1);
}

static void	handle_outside(t_tokenizer *tk)
{
	if (tk->state == OUTSIDE)
	{
		if (tk->input[tk->pos_input] == '"')
		{
			tk->state = IN_DOUBLE_QUOTES;
			tk->pos_input++;
		}
		else if (tk->input[tk->pos_input] == '\'')
		{
			tk->state = IN_SINGLE_QUOTES;
			tk->pos_input++;
		}
		else if (tk->input[tk->pos_input] == ' ' ||
			tk->input[tk->pos_input] == '\t')
		{
			create_token(tk);
			tk->pos_input++;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

static void	handle_double_quotes(t_tokenizer *tk)
{
	if (tk->state == IN_DOUBLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '"')
		{
			tk->state = OUTSIDE;
			tk->pos_input++;
			tk->buffer[tk->pos_buffer] = '\0';
			tk->pos_buffer = 0;
			tk->tab[tk->pos_tab] = strdup(tk->buffer);
			tk->pos_tab++;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

static void	handle_single_quotes(t_tokenizer *tk)
{
	if (tk->state == IN_SINGLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '\'')
		{
			tk->state = OUTSIDE;
			tk->pos_input++;
			tk->buffer[tk->pos_buffer] = '\0';
			tk->pos_buffer = 0;
			tk->tab[tk->pos_tab] = strdup(tk->buffer);
			tk->pos_tab++;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

char	**tokenizer(char *input)
{
	t_tokenizer	tk;

	if (!input || !init_tokenizer(&tk, input))
		return (NULL);
	init_tokenizer(&tk, input);
	while (input[tk.pos_input] && tk.pos_tab < 99)
	{
		handle_outside(&tk);
		handle_double_quotes(&tk);
		handle_single_quotes(&tk);
	}
	if (tk.pos_buffer > 0)
	{
		tk.buffer[tk.pos_buffer] = '\0';
		tk.tab[tk.pos_tab] = strdup(tk.buffer);
		tk.pos_tab++;
		tk.pos_buffer = 0;
	}
	tk.tab[tk.pos_tab] = NULL;
	free(tk.buffer);
	return (tk.tab);
}
