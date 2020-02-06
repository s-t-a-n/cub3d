/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dtoa_sc.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:36:31 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:36:33 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DTOA_SC_H
# define FT_DTOA_SC_H

# define DTOA_WSIZE 2024
# define DTOA_MAX_PRECISION 100

/*
** ft_dtoa_sc (put in a separate header because of norminette
** (these would be private/static functions irl)
*/
void		ft_perform_bankers_rounding_sc(double nb, char *worker,
				size_t worker_len);
void		ft_perform_retrospective_rounding_sc(char *worker,
				size_t worker_len, char *master);
void		ft_handle_integer_rounding_sc(unsigned long long nb_asint,
				char *master);
void		ft_handle_rounding_sc(double nb, char *worker, char *master);
void		ft_handle_precision_sc(double *nb, int precision,
					char *worker);

#endif
