#include "minishell.h"



void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_lexer	*lexer;
	t_token	*token;
	t_token *token_list = NULL;
	t_tree	*node = NULL;
    t_env *envlist = init_env(env);


	(void)argc;
	(void)env;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handler);
    rl_catch_signals = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
        {
            write(1, "exit\n", 5);
            exit(0);
        }
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
		add_history(input);
		lexer = initialize_lexer(input);
		token_list = NULL;
		while (lexer->position < lexer->lenght)
		{
			token = get_next_token(lexer);
			if (!token)
				continue;
			token->type = token_type(token);
			append_token(&token_list, token);
		}
		node = parse_op(token_list);
		execute_tree(node, env, envlist);
        free(input);
	}
	return (0);
}