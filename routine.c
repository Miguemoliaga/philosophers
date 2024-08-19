/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:56:29 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/19 17:56:13 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eatingodds(t_data *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf_mutex(philo, "has taken (rigth) fork");
	pthread_mutex_lock(philo->left_fork);
	printf_mutex(philo, "has taken (left) fork");
	pthread_mutex_lock(philo->time_mutex);
	if (ft_get_time() - philo->last_meal >= philo->time_to_die)
	{
		pthread_mutex_unlock(philo->time_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf_mutex(philo, "is eating");
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->time_mutex);
	smart_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eatingeven(t_data *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf_mutex(philo, "has taken (left) fork");
	pthread_mutex_lock(philo->right_fork);
	printf_mutex(philo, "has taken (rigth) fork");
	pthread_mutex_lock(philo->time_mutex);
	if (ft_get_time() - philo->last_meal >= philo->time_to_die)
	{
		pthread_mutex_unlock(philo->time_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf_mutex(philo, "is eating");
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->time_mutex);
	smart_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_data		*philo;

	philo = (t_data *)arg;
	if (philo->philo_number % 2 == 0)
		usleep(1500);
	while (check_status(philo, 0))
	{
		if (philo->philo_number % 2 == 0)
			eatingeven(philo);
		else
			eatingodds(philo);
		pthread_mutex_lock(philo->status_mutex);
		philo->number_of_dishes++;
		pthread_mutex_unlock(philo->status_mutex);
		printf_mutex(philo, "is sleeping");
		smart_sleep(philo->time_to_sleep);
		printf_mutex(philo, "is thinking");
		smart_sleep((philo->time_to_die - philo->time_to_eat
				- philo->time_to_sleep) / 2);
	}
	return (NULL);
}

void	check_death(t_data **data, int n, int *status)
{
	t_data	*curr;

	curr = *data;
	while (curr->philo_number < n && *status)
	{
		pthread_mutex_lock(curr->time_mutex);
		if (ft_get_time() - curr->last_meal >= curr->time_to_die)
		{
			pthread_mutex_unlock(curr->time_mutex);
			printf_mutex(curr, "died");
			check_status(*data, 1);
			break ;
		}
		else
			pthread_mutex_unlock(curr->time_mutex);
		curr = curr->next;
	}
}

void	monitor(int *status, t_data **data, int n)
{
	t_data	*curr;
	int		i;

	i = 0;
	curr = *data;
	while (*status)
	{
		check_death(data, n, status);
		if (!*status)
			break ;
		curr = *data;
		i = 0;
		pthread_mutex_lock((*data)->status_mutex);
		while (curr->philo_number < n && curr->number_to_eat > 0
			&& curr->number_of_dishes >= curr->number_to_eat)
		{
			pthread_mutex_unlock((*data)->status_mutex);
			i++;
			curr = curr->next;
			pthread_mutex_lock((*data)->status_mutex);
		}
		pthread_mutex_unlock((*data)->status_mutex);
		if (i == n - 1)
			check_status(*data, 1);
	}
}
