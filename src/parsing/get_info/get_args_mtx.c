#include "minishell.h"

int count_args(t_input *cmdline, int token, int if_cmd_before_red)
{
    int len;

    len = 1;
    if (token == CMD)
    {
        cmdline = cmdline->next;
        while (cmdline && cmdline->token == ARG)
            len++;
    }
    else if (check_which_operator(token) == REDIRECTS)
    {
        if (if_cmd_before_red)
        {
            while (cmdline && (cmdline->token == FILE_W || cmdline->token == ARG))
                len++;
            return (len);
        }
        while (cmdline && (cmdline->token != CMD))
            len++;
        len++;
    }
    return (len);
}

char    **get_args_cmds(t_input *cmdline)
{
    int     len;
    char    **args;

    len = count_args(cmdline, cmdline->token, 0);
}

char    **get_args_redirects(t_input *cmdline, t_input *head)
{
    int     len;
    char    **args;

        len = count_args(cmdline, cmdline->token, 0);

}

t_input *create_args_mtx(t_input *cmdline, t_input *head)
{
    cmdline->args = NULL;
    if (cmdline->token == CMD)
        cmdline->args = get_args_cmds(cmdline);
    else if (check_which_operator(cmdline->token) == REDIRECTS)
        cmdline->args = get_args_redirects(cmdline, head);
    return (cmdline);    
}

t_input	*get_args_mtx(t_input *cmd_line)
{
    t_input *cmdline;
    t_input *current;

    current = NULL;
    cmdline = cmd_line;
    while (cmdline)
    {
        cmdline = create_args_mtx(cmdline, cmd_line);
        if (!cmdline)
            return (dll_input_clear(&cmd_line), NULL);
        cmdline = cmdline->next;
    }
    return (cmd_line);
}
