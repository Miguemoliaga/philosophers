/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:52:45 by mmartine          #+#    #+#             */
/*   Updated: 2024/08/13 18:14:44 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	struct s_data	*next;
	pthread_t		philo_id;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	*status_mutex;
	int				number_of_dishes;
	int				philo_number;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				number_to_eat;
	int				*status;
	long long		initial_time;
	long long		last_meal;
}			t_data;

void		error(int error_n);
int			validnum(char *args);
int			ft_atoi(const char *str);
void		printlist(t_data **data, int n);
long long	ft_get_time(void);
void		printf_mutex(t_data *data, char *str);
int			free_memory(t_data **data, int n);
void		smart_sleep(long long time);
void		*routine(void *arg);
int			eatingact(t_data *philo, long long last_meal);
void		monitor(int	*status, t_data **data, int n);
void		fill_mutex(t_data *list, int n);
int			check_status(t_data	*philo, int set);
void		one_philo_scenario(t_data *philo);
#endif