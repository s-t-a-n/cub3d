/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoa.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/21 19:24:54 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/30 00:32:24 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LDTOA_H
# define FT_LDTOA_H

# define DTOA_WSIZE 2024
# define DTOA_MAX_PRECISION 100

/*
** ft_ldtoa2.c (put in a separate header because of norminette
** (these would be private/static functions irl)
*/
void	ft_perform_bankers_rounding(long double nb, char *worker,
			size_t worker_len);
void	ft_perform_retrospective_rounding(char *worker,
			size_t worker_len, char *master);
void	ft_handle_integer_rounding(unsigned long long nb_asint,
			char *master);
void	ft_handle_rounding(long double nb, char *worker, char *master);

#endif
