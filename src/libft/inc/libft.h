/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 16:11:44 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/09 23:50:43 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include "ft_std.h"

/*
** Defining CALLOC_ZERO_RETURN_NULL guarantees calloc returns NULL instead of
** calling malloc(0) when it is called with a zero 'count' or 'size'
** # define CALLOC_ZERO_RETURN_NULL
*/

/*
** libft definitions
*/

typedef enum		e_case
{
	__lowcase,
	__upcase
}					t_case;

/*
** 'vector'-like struct (see dynmem.c)
*/
typedef struct		s_dynmen
{
	size_t			element_cap;
	size_t			element_count;
	unsigned char	**mem;
}					t_dynmem;

/*
**  libft functions
*/
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_issymbol(int c);

void				ft_swap(char *a, char *b);

int					ft_atoi(const char *str);
long				ft_strtol(const char *str, char **endptr, int base);
unsigned long long	ft_strtoull(const char *str, char **endptr, int base);
char				*ft_itoa(int n);
char				*ft_ultoa_base(unsigned long nb, int base, int uppercase);
char				*ft_ulltoa_base(unsigned long long nb, int base,
						int uppercase);
char				*ft_ltoa_base(long int nb, int base, int uppercase);
char				*ft_lltoa_base(long long int nb, int base, int uppercase);
char				*ft_ldtoa(long double nb, int precision);
char				*ft_dtoa_sc(double nb, int precision, int *exp_ptr,
						t_bool uppercase);

char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dst,
						const char *src, size_t dstsize);
size_t				ft_strlcpy(char *restrict dst,
						const char *restrict src, size_t dstsize);
size_t				ft_strlen(const char *s);
size_t				ft_wcslen(wchar_t *ws);
int					ft_wclen(wchar_t wc);
size_t				ft_strnlen(const char *s, size_t maxlen);
char				*ft_strrev(char *str);
size_t				ft_strclen(const char *s, char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t len);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_strsplit(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t				ft_strcount(const char *s1, char c);
char				*ft_strfdup(const char *s1, char c);

int					ft_tolower(int c);
int					ft_toupper(int c);

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);

void				ft_putchar_fd(char c, int fd);
void				ft_putwchar_fd(wchar_t wc, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putwstr_fd(wchar_t *ws, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr_base_fd(unsigned long nb, int base, int fd);
void				*ft_arrayclear(void **ptr_array, size_t len);

void				dynmem_destroy(t_dynmem *dym);
t_dynmem			*dynmem_init(size_t element_cap);
t_bool				dynmem_pushback(t_dynmem **dym, unsigned char *element);
#endif
