/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:49:16 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/13 20:38:56 by mmartine         ###   ########.fr       */
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

void	mutex_init(t_data **data, int n)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*first_fork;
	int				i;
	t_data			*curr;

	i = 0;
	curr = *data;
	first_fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(first_fork, NULL);
	curr->left_fork = first_fork;
	while (++i <= n && curr)
	{
		if (curr->philo_number != n)
		{
			fork = malloc(sizeof(pthread_mutex_t));
			pthread_mutex_init(fork, NULL);
			curr->right_fork = fork;
			curr->next->left_fork = fork;
		}
		else
			curr->right_fork = first_fork;
		curr = curr->next;
	}
}

void	philo_mutex_init(t_data **data, int n, long long i_time, int *status)
{
	t_data	*curr;

	mutex_init(data, n);
	curr = *data;
	*status = 1;
	if (n == 1)
	{
		one_philo_scenario(curr);
		return ;
	}
	while (curr->philo_number < n)
	{
		curr->status = status;
		curr->initial_time = i_time;
		curr->last_meal = curr->initial_time;
		pthread_create(&(curr->philo_id), NULL, &routine, curr);
		curr = curr->next;
	}
	monitor(status, data, n);
	curr = *data;
	while (curr->philo_number < n)
	{
		pthread_join(curr->philo_id, NULL);
		curr = curr->next;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_data			**data;
	int				*status;

	if (!(argc == 6 || argc == 5))
		return (error(2), 0);
	i = 1;
	while (argv[i])
	{
		if (!validnum(argv[i]))
			return (error(1), 0);
		i++;
	}
	data = malloc(sizeof(t_data *));
	if (!data)
		return (error(3), 0);
	data = create_list(argc, argv, data, ft_atoi(argv[1]));
	status = malloc(sizeof(int));
	philo_mutex_init(data, ft_atoi(argv[1]), ft_get_time(), status);
	if (ft_atoi(argv[1]) == 1)
		free(status);
	return (free_memory(data, ft_atoi(argv[1])));
}
