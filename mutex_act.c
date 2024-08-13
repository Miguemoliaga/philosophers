/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:50:49 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/13 18:17:50 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_mutex(t_data *curr, int n)
{
	pthread_mutex_t	*w_mutex;
	pthread_mutex_t	*m_mutex;
	pthread_mutex_t	*s_mutex;

	s_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(s_mutex, NULL);
	m_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(m_mutex, NULL);
	w_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(w_mutex, NULL);
	while (curr->philo_number < n)
	{
		curr->write_mutex = w_mutex;
		curr->status_mutex = s_mutex;
		curr->time_mutex = m_mutex;
		curr = curr->next;
	}
	curr->write_mutex = w_mutex;
	curr->status_mutex = s_mutex;
	curr->time_mutex = m_mutex;
}

void	smart_sleep(long long time)
{
	long long	i;

	i = ft_get_time();
	while (1)
	{
		if (ft_get_time() - i >= time)
			break ;
	}
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	printf_mutex(t_data *data, char *str)
{
	pthread_mutex_lock((data->write_mutex));
	printf("%lli ms: ", (ft_get_time() - data->initial_time));
	printf("philo number %i ", data->philo_number);
	printf("%s.\n", str);
	pthread_mutex_unlock((data->write_mutex));
	return ;
}

int	check_status(t_data	*philo, int set)
{
	int	ret;

	pthread_mutex_lock(philo->status_mutex);
	if (set)
		*philo->status = 0;
	ret = *philo->status;
	pthread_mutex_unlock(philo->status_mutex);
	return (ret);
}
