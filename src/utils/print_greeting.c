/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_greeting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:07:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/07 16:44:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_geeting1(void)
{
	ft_printf_fd(2, "\e[38;2;255;3;3m#####################################");
	ft_printf_fd(2, "####################################################");
	ft_printf_fd(2, "################################\n##################");
	ft_printf_fd(2, "####################################################");
	ft_printf_fd(2, "###################################################\n");
	ft_printf_fd(2, "\e[38;2;255;120;0m##                                 ");
	ft_printf_fd(2, "                                                     ");
	ft_printf_fd(2, "                               ##\n##    ,dPYb,      ");
	ft_printf_fd(2, "          +          *                           *   ");
	ft_printf_fd(2, "                +                      ,dPYb,   ##\n");
	ft_printf_fd(2, "\e[38;2;255;237;0m##    IP'`Yb      +                 ");
	ft_printf_fd(2, "                                                *     ");
	ft_printf_fd(2, "                +   IP'`Yb   ##\n##    I8  8I         ");
	ft_printf_fd(2, "           *                              +          ");
	ft_printf_fd(2, "        +                           I8  8I   ##\n");
	ft_printf_fd(2, "\e[38;2;0;220;38m##    I8  8'                         ");
	ft_printf_fd(2, "                                                      ");
	ft_printf_fd(2, "                   I8  8'   ##\n##    I8 dPgg,    ,ggg");
	ft_printf_fd(2, ",   gg     gg        ,gggg,gg  gg      gg  gg      gg ");
	ft_printf_fd(2, "  ,gggggg,   ,gggggg,   ,gggggg,  I8 dP    ##\n");

}

static void	print_geeting2(void)
{
	ft_printf_fd(2, "\e[38;2;26;24;242m##    I8dP\" \"8I  i8\" \"8i  I8     ");
	ft_printf_fd(2, "8I       dP\"  \"Y8I  I8      8I  I8      8I   dP\"\"\"");
	ft_printf_fd(2, "\"8I   dP\"\"\"\"8I   dP\"\"\"\"8I  I8dP     ##\n##    ");
	ft_printf_fd(2, "I8P    I8  I8, ,8I  I8,   ,8I      i8'    ,8I  I8,    ,");
	ft_printf_fd(2, "8I  I8,    ,8I  ,8'    8I  ,8'    8I  ,8'    8I  I8P   ");
	ft_printf_fd(2, "   ##\n\e[38;2;180;61;210m##   ,d8     I8, `YbadP' ,d8b");
	ft_printf_fd(2, ", ,d8I     ,d8,   ,d8I ,d8b,  ,d8b,,d8b,  ,d8b,,dP     ");
	ft_printf_fd(2, "Y8,,dP     Y8,,dP     Y8,,d8b,_    ##\n##   88P     `Y8");
	ft_printf_fd(2, "888P\"Y888P\"\"Y88P\"888    P\"Y8888P\"8888P'\"Y88P\"`Y");
	ft_printf_fd(2, "88P'\"Y88P\"`Y88P      `Y88P      `Y88P      `Y88P'\"Y8");
	ft_printf_fd(2, "8   ##\n");
	ft_printf_fd(2, "\x1b[m##                             ,d8I'           ,d");
	ft_printf_fd(2, "8I'                                                    ");
	ft_printf_fd(2, "               ##\n##         +                 ,dP'8I ");
	ft_printf_fd(2, "         ,dP'8I        *                      *        ");
	ft_printf_fd(2, "                      +     ##\n##                     ");
	ft_printf_fd(2, "*    ,8\"  8I         ,8\"  8I  +                      ");
	ft_printf_fd(2, "                                           ##\n");
}

void	print_greeting(void)
{
	print_geeting1();
	print_geeting2();
	ft_printf_fd(2, "\e[38;2;255;169;184m##      ");
	ft_printf_fd(2, "                    I8   8I         I8   8I            ");
	ft_printf_fd(2, "                                                       ");
	ft_printf_fd(2, " ##\n##                          `8, ,8I");
	ft_printf_fd(2, "         `8, ,8I                       +               ");
	ft_printf_fd(2, "                             ##\n##           *        ");
	ft_printf_fd(2, "       `Y8P\"           `Y8P\"                     *   ");
	ft_printf_fd(2, "                  +                         ##\n");
	ft_printf_fd(2, "\e[38;2;91;206;250m##                                  ");
	ft_printf_fd(2, "                                                       ");
	ft_printf_fd(2, "                            ##\n");
	ft_printf_fd(2, "####################################");
	ft_printf_fd(2, "#######################################################");
	ft_printf_fd(2, "##############################\n#######################");
	ft_printf_fd(2, "#######################################################");
	ft_printf_fd(2, "###########################################\n");
}
