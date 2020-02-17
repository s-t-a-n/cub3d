/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_swap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 13:33:56 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/17 19:41:14 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(char *a, char *b)
{
	if (*a != *b)
	{
		*a = (int)*a + (int)*b;
		*b = (int)*a - (int)*b;
		*a = (int)*a - (int)*b;
	}
}

void	ft_pswap(void **a, void **b)
{
	void *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
