/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:23:28 by pvital-m          #+#    #+#             */
/*   Updated: 2023/06/10 13:33:40 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_colors.h"
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

// MAIN FUNCTION
int	ft_printf(const char *format, ...);
int	ft_print_str(char *str);
int	ft_print_char(char c);
int	ft_print_nbr(long int nbr);
int	ft_print_hex(unsigned int num, const char format);
int	ft_print_ptr(unsigned long long ptr_addr);
int	ft_print_unsigned(unsigned int nbr);

#endif