/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:22:25 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/18 17:40:11 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_memory(t_data **data, int n)
{
	int		i;
	t_data	*curr;
	t_data	*next;

	i = 0;
	curr = *data;
	pthread_mutex_destroy(curr->write_mutex);
	free(curr->write_mutex);
	pthread_mutex_destroy(curr->time_mutex);
	free(curr->time_mutex);
	pthread_mutex_destroy(curr->status_mutex);
	free(curr->status_mutex);
	if (n > 1)
		free(curr->status);
	while (i++ < n)
	{
		pthread_mutex_destroy(curr->time_mutex);
		pthread_mutex_destroy(curr->right_fork);
		free(curr->right_fork);
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(data);
	return (0);
}

void	error(int error_n)
{
	if (error_n == 1)
		printf("Alguno de los argumentos no es un número valido\n");
	if (error_n == 2)
		printf("Número de argumentos inválido\n");
	if (error_n == 3)
		printf("Error a la hora de alojar memoria\n");
}

void	one_philo_scenario(t_data *philo, int *status)
{
	philo->status = status;
	philo->initial_time = ft_get_time();
	printf_mutex(philo, "has taken (rigth) fork");
	smart_sleep(philo->time_to_die);
	printf_mutex(philo, "died");
}

int	ft_atoi(const char *str)
{
	int	mult;
	int	resul;
	int	i;

	i = 0;
	mult = 1;
	resul = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] && (str[i] == 43 || str[i] == 45))
	{
		if (str[i] == 45)
			mult = -1;
		i++;
	}
	while (str[i] && (str[i] > 47 && str[i] < 58))
	{
		resul = (resul * 10 + (str[i] - '0'));
		i++;
	}
	return (resul * mult);
}

int	validnum(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || str[i] == 43 || str[i] == 45)
		return (0);
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			i++;
		else
			return (0);
	}
	return (1);
}
