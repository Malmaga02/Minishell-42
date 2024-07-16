#include "minishell.h"

t_all	assign_token_as_words_token(t_all all_info, int token)
{
	t_input	*tmp;

	tmp = all_info.cmd_line;
	while (tmp)
	{
		if (find_token_type(tmp->token) == token)
		{
			if (!tmp->prev)
				tmp->token = get_word_token(0);
			if (tmp->prev)
				tmp->token = get_word_token(tmp->prev->token);
		}
		tmp = tmp->next;
	}
	return (all_info);
}
