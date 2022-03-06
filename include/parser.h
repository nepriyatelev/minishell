/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:39:34 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 20:18:25 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
/*    /parser/parsing.c    */
int	parsing(char *cmd, t_list **list_env, t_cmd **ex_cmd);

int	separation_by_pipes(char *cmd, t_list **cmd_list);
/*    parser/parser_utilities.c    */
int	new_lst_back(char *cmd, t_list **cmd_list);
#endif