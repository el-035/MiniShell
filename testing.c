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
		printf("  in: %s\n", data->cmds[i].in);
		printf("  out: %s\n", data->cmds[i].out);
	}
}

