
#include "ftp_server.h"

void	test_cmd_pwd(t_vault *vault)
{
	char *name = "name_test";
	char *pass = "pass_test";
	vault->csc = 1;
	vault->name = name;
	vault->passw = pass;
	cmd_pwd(vault);
}

int		main(void)
{
	t_vault *vault;


	test_cmd_pwd(vault);
	return (0);
}