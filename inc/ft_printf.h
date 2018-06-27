/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:11:37 by galy              #+#    #+#             */
/*   Updated: 2017/03/27 17:32:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <wchar.h>

/*
**	Machine
*/

# define EX_FAIL	-1
# define BASE_BIN	2
# define BASE_OCT	8
# define BASE_DEC	10
# define BASE_HEX	16

typedef struct	s_flags
{
	char		*start;
	int			end;
	char		conv_type;
	int			len;
	int			sharp;
	int			zero;
	int			plus;
	int			minus;
	int			space;
	int			width;
	int			precision;
	int			precision_on;
	char		*sizemod;
	int			decal;
	int			fl_l;
	int			fl_h;
	int			fl_j;
	int			fl_z;
	int			maj;
	int			error;
}				t_flags;

/*
**	ft_printf.c
*/
int				ft_printf(const char *format, ...);
int				sar(va_list ap, const char *format);
int				printer(t_flags *flag);
int				optimus(va_list ap, t_flags *flag);
void			reset_flag(t_flags *flag);

/*
**	flag filler
*/

void			flag_sharp_filler(t_flags *flag);
void			flag_zero_filler(t_flags *flag);
void			flag_minus_filler(t_flags *flag);
void			flag_space_filler(t_flags *flag);
void			flag_plus_filler(t_flags *flag);
void			flag_width_filler(t_flags *flag);
void			flag_precision_filler(t_flags *flag);

void			flag_j_filler(t_flags *flag);
void			flag_h_filler(t_flags *flag);
void			flag_l_filler(t_flags *flag);
void			flag_z_filler(t_flags *flag);

void			flag_dmin_filler(t_flags *flag);
void			flag_dmaj_filler(t_flags *flag);
void			flag_imin_filler(t_flags *flag);
int				flag_d(va_list ap, t_flags *flag);
char			*flag_width_d_exec(char *str, t_flags *flag);
char			*flag_precision_d_exec(char *str, t_flags *flag);
char			*flag_space_d_exec(char *str, t_flags *flag);
char			*flag_plus_exec(char *str, t_flags *flag);

void			flag_umaj_filler(t_flags *flag);
void			flag_umin_filler(t_flags *flag);
int				flag_u(va_list ap, t_flags *flag);
char			*flag_precision_u_exec(char *str, t_flags *flag);

void			flag_percent_filler(t_flags *flag);
int				flag_percent(t_flags *flag);

void			flag_omaj_filler(t_flags *flag);
void			flag_omin_filler(t_flags *flag);
int				flag_o(va_list ap, t_flags *flag);
char			*flag_sharp_oexec(char *str);

void			flag_xmin_filler(t_flags *flag);
void			flag_xmaj_filler(t_flags *flag);
char			*flag_sharp_x_exec(char *str);
int				flag_x(va_list ap, t_flags *flag);
char			*flag_precision_x_exec(char *str, t_flags *flag);
char			*flag_width_x_exec(char *str, t_flags *flag);

void			flag_cmaj_filler(t_flags *flag);
void			flag_cmin_filler(t_flags *flag);
int				flag_c(va_list ap, t_flags *flag);

void			flag_smaj_filler(t_flags *flag);
void			flag_smin_filler(t_flags *flag);
int				flag_s(va_list ap, t_flags *flag);
int				check_flag_zero_smod(void *str, t_flags *flag);
char			*flag_width_s_exec(char *str, t_flags *flag);
char			*flag_precision_s_exec(char *str, t_flags *flag);
wchar_t			*flag_precision_ls_exec(wchar_t *wstr, t_flags *flag);
wchar_t			*flag_width_ls_exec(wchar_t *wstr, t_flags *flag);

void			flag_pmin_filler(t_flags *flag);
int				flag_p(va_list ap, t_flags *flag);
char			*flag_width_p_exec(char *str, t_flags *flag);
char			*flag_precision_p_exec(char *str, t_flags *flag);
char			*flag_sharp_p_exec(char *str);

int				flag_b(va_list ap);
void			flag_b_filler(t_flags *flag);

char			*flag_plus_exec(char *str, t_flags *flag);

char			*ft_lltoa(long long n);
long long int	ft_atoll(const char *nptr);
char			*ft_ulltoa(unsigned long long n);
char			*ft_ubase_converter(uintmax_t nbr, int base, int nbr_bit);
int				ft_wstrlen(wchar_t *wstr);
int				ft_wcharlen(wchar_t wc);
int				ft_putwchar(wchar_t lettre);
int				ft_putwstr(wchar_t *str);
unsigned long	ft_power(int nbr, int power);
wchar_t			*ft_wstrdup(wchar_t *s1);
void			ft_putbuffer(char *str);

char			*ft_imaxtoabase(intmax_t nbr, int base, int nbr_bit);
char			*putnegativesign(char *str, int base);
char			*str_imaxbase_hexa(char *str);

/*
** pour les tests
*/

void			print_flags(t_flags *flag);
int				list_flag_exec(va_list ap, t_flags *flag);
void			list_flag_filler(t_flags *flag);

#endif
