/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:27:10 by jpceia            #+#    #+#             */
/*   Updated: 2021/09/10 08:48:01 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/resource.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

typedef enum e_bool
{
	false,
	true
}	t_bool;

/*
 * Memory related functions
 */
void	*ft_memset(void *str, int c, size_t n);
void	*ft_bzero(void *str, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_calloc(size_t n, size_t size);

/*
 * String related functions
 */
size_t	ft_strlen(const char *str);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strndup(char const *str, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strlower(char const *s);
char	*ft_strupper(char const *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char c);
int		ft_strwc(char const *s, char c);
int		ft_contains(char c, char const *charset);
int		ft_startswith(const char *s, const char *pref);
int		ft_endswith(const char *s, const char *suff);
char	*ft_strreverse(char *s);
char	*ft_straddc(char *s, char c);
char	*ft_empty_string(void);
void	ft_str_array_clear(char **str_arr, int len);

/*
 * Number <=> String conversion functions
 */
int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, char *base);
char	*ft_itoa(int n);
long	ft_atol(const char *str);
char	*ft_lltoa(long long nb);
char	*ft_lltoa_base(long long nb, const char *base);
char	*ft_ulltoa(unsigned long long nb);
char	*ft_ulltoa_base(unsigned long long nb, const char *base);
float	ft_atof(const char *str);

/*
 * Arithmetic functions
 */
int		ft_iabs(int x);
int		ft_isign(int x);
int		ft_imax(int x, int y);
int		ft_imin(int x, int y);
int		ft_mod(int x, int y);

/*
 * Char related functions
 */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/*
 * Print/Write related functions
 */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
void	ft_putchar_error(char c);
void	ft_putstr_error(char *s);
void	ft_putendl_error(char *s);
void	ft_putnbr_error(int n);

/*
 * Get Next Line
 */
int		ft_get_next_line(int fd, char **line);

/*
 * Linked-List related functions
 */
t_list	*ft_lstnew(void *content);

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *node);
void	ft_lstadd_front(t_list **lst, t_list *node);
t_list	*ft_lstpush_back(t_list **lst, void *content);
t_list	*ft_lstpush_front(t_list **lst, void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
