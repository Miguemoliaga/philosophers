/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:49:16 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/18 17:40:29 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	init_support(t_data **data, int n, int *status)
{
	int		i;
	t_data	*curr;

	curr = *data;
	i = 0;
	monitor(status, data, n);
	curr = *data;
	i = 0;
	while (i++ < n)
	{
		pthread_join(curr->philo_id, NULL);
		curr = curr->next;
	}
}

void	philo_mutex_init(t_data **data, int n, long long i_time, int *status)
{
	t_data	*curr;
	int		i;

	mutex_init(data, n);
	curr = *data;
	*status = 1;
	i = 0;
	if (n == 1)
	{
		one_philo_scenario(curr, status);
		return ;
	}
	while (i++ < n)
	{
		curr->status = status;
		curr->initial_time = i_time;
		curr->last_meal = curr->initial_time;
		pthread_create(&(curr->philo_id), NULL, &routine, curr);
		curr = curr->next;
	}
	init_support(data, n, status);
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
