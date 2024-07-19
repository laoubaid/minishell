/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:07:43 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/19 03:22:07 by laoubaid         ###   ########.fr       */
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
            dup2(outputs[output_counter], STDOUT_FILENO);
            close(outputs[output_counter++]);
        }
        else if (tmp->redir_type == R_STD_IN)
        {
            inputs[input_counter] = open(tmp->filename, O_RDONLY);
            if (inputs[input_counter] == -1)
            {
                perror("file");
                exit(1);
            }
            dup2(inputs[input_counter], STDIN_FILENO);
            close(inputs[input_counter++]);
        }
        tmp = tmp->next;
    }
}

int	execute(t_ast *ast, char **env)
{
	char **cmd;
	int pid;
    int exit_status;

	cmd = ast->cmd->simple_cmd;
	path(&cmd, env[getpath(env)]);
	pid = fork();
	if (!pid)
	{
		redirecte(ast);
        /////////////////////////////////////////fix the exit code and error messsage for things like premission denied , not a dir, etc
		execve(cmd[0], cmd, env);
		write(2, "command not found: ", 19);
		if (cmd[0])
			write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		exit(1);
	}
	wait(&exit_status);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    return (-1);
}


int    handle_operations(t_ast *ast, char **env)
{
    int exit_status;

    exit_status = 0;
    if (ast->type == OR)
    {
        if (test(ast->left, env) != 0)
            exit_status = test(ast->right, env);
        else
            exit_status = 0;
    }
    else
    {
        if (test(ast->left, env) == 0)
            exit_status = test(ast->right, env);
    }
    return (exit_status);
}

void    handle_pipe(t_ast *ast)
{
    exit(2);
}

int subshell(t_ast *ast, char **env)
{
    int pid;
    int exit_status;

    pid = fork();
    if (!pid)
    {
        if (ast->cmd != NULL)
            redirecte(ast);
        exit(test(ast->left, env));
    }
    wait(&exit_status);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    return (-1);
}

int    test(t_ast *ast, char **env)
{
    int exit_status;
    
    if (ast->type == OR || ast->type == AND)
        exit_status = handle_operations(ast, env);
    else if (ast->type == PIPE)
        handle_pipe(ast);
    else if (ast->type == LPAREN)
        exit_status = subshell(ast, env);
    else
        exit_status = execute(ast, env);
    return (exit_status);
}