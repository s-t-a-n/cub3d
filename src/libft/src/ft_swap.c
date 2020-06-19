/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_swap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:01:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:01:43 by sverschu      ########   odam.nl         */
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
