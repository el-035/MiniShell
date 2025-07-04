#include "minishell.h"

/* void print_cmd_list(t_cmd *cmds)
{
    int i = 0;
    while (cmds)
    {
        printf("Command %d: %s\n", i++, cmds->args[0]);
        cmds = cmds->next;
    }
} */

void print_cmds(t_data *data)
{
	for (int i = 0; i < data->cmd_count; i++)
	{
		printf("CMD %d:\n", i);
		for (int j = 0; data->cmds[i].args && data->cmds[i].args[j]; j++)
			printf("  arg[%d]: %s\n", j, data->cmds[i].args[j]);
		for (int j = 0; data->cmds[i].in && data->cmds[i].in[j]; j++)
			printf("  in[%d]: %s\n", j, data->cmds[i].in[j]);
		for (int j = 0; data->cmds[i].out && data->cmds[i].out[j]; j++)
			printf("  out[%d]: %s\n", j, data->cmds[i].out[j]);
		int total = data->cmds[i].in_redirs + data->cmds[i].out_redirs;
		for (int j = 0; j < total; j++)
			printf("  redir type[%d]: %d\n", j, data->cmds[i].redir_order[j]);
	}
}

