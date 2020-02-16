/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_swap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 13:33:56 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/21 19:38:52 by sverschu      ########   odam.nl         */
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
	*b = *a;
}
