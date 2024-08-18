/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:34:42 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/18 17:39:02 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_data(t_data *node, int number, char **args, int argc)
{
	node->philo_number = number;
	node->time_to_die = ft_atoi(args[2]);
	node->time_to_eat = ft_atoi(args[3]);
	node->time_to_sleep = ft_atoi(args[4]);
	node->number_of_dishes = 0;
	if (argc == 6)
		node->number_to_eat = ft_atoi(args[5]);
	else
		node->number_to_eat = -1;
}

t_data	**create_list(int argc, char **args, t_data **data, int n)
{
	int				i;
	t_data			*curr;
	t_data			*add;

	curr = malloc(sizeof(t_data));
	*data = curr;
	i = 0;
	while (++i <= n)
	{
		fill_data(curr, i, args, argc);
		if (i < n)
		{
			add = malloc(sizeof(t_data));
			curr->next = add;
			curr = add;
		}
	}
	fill_mutex(*data, n);
	return (curr->next = *data, data);
}
