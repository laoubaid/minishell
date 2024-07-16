/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:07:43 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/17 00:22:40 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

void count_redir(t_redir *tmp, int *in, int *out)
{
    while (tmp)
    {
        if (tmp->redir_type == R_STD_OUT)
            (*out)++;
        else if (tmp->redir_type == R_STD_IN)
            (*in)++;
        tmp = tmp->next;
    }
}

void	redirecte(t_ast *ast)
{
	int 	input_counter = 0;
    int 	output_counter = 0;
    int 	*inputs;
	int		*outputs;
    t_redir *tmp;

    count_redir(ast->cmd->redirs, &input_counter, &output_counter);
    inputs = malloc(sizeof(int) * input_counter);
    outputs = malloc(sizeof(int) * output_counter);
    input_counter = 0;
    output_counter = 0;
    tmp = ast->cmd->redirs;
    while (tmp)
    {
        if (tmp->redir_type == R_STD_OUT)
        {
            outputs[output_counter] = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
            dup2(outputs[output_counter++], STDOUT_FILENO);
        }
        else if (tmp->redir_type == R_STD_IN)
        {
            inputs[input_counter] = open(tmp->filename, O_RDONLY);
            if (inputs[input_counter] == -1)
            {
                perror("file");
                exit(1);
            }
            dup2(inputs[input_counter++], STDIN_FILENO);
        }
        tmp = tmp->next;
    }
}

void	execute(t_ast *ast, char **env)
{
	char **cmd;
	int pid;

	cmd = ast->cmd->simple_cmd;
	// printf("\nfilename: %s\n", ast->cmd->redirs->filename);
	path(&cmd, env[getpath(env)]);
	pid = fork();
	if (!pid)
	{
		redirecte(ast);
		execve(cmd[0], cmd, NULL);
		write(2, "command not found: ", 19);
		if (cmd[0])
			write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		exit(1);
	}
	wait(NULL);
}