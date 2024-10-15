/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:57:05 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/15 01:33:50 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_isprint(int ch)
{
	if (ch <= 31 || ch > 126)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

// int	ft_isprint(int argument)
// {
// 	return (argument >= 32 && argument <= 126);
// }

// int	main(void)
// {
// 	printf("%d\n", ft_isprint(EOF));
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:54:16 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/15 01:33:08 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	count_n(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		num = -num;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

void	digit_to_string(char *array_of_digits, int n, int digit_count)
{
	int	i;

	i = 0;
	while (i < digit_count)
	{
		array_of_digits[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	array_of_digits[i] = '\0';
}

void	handle_min_max(int n, int fd)
{
	if (n < -2147483647)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n == 2147483647)
	{
		write(fd, "2147483647", 10);
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	array_of_digits[11];
	int		negative;
	int		i;

	negative = 0;
	i = count_n(n);
	if (n < -2147483647 || n == 2147483647)
	{
		handle_min_max(n, fd);
		return ;
	}
	else
	{
		if (n < 0)
		{
			negative = 1;
			n = -n;
		}
		digit_to_string(array_of_digits, n, i);
		if (negative == 1)
			write(fd, "-", 1);
	}
	while (i--)
		write(fd, &array_of_digits[i], 1);
}


void	print_integer(va_list args)
{
	int	i;

	i = va_arg(args, int);
	ft_putnbr_fd(i, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	str_len;

	str_len = ft_strlen(s);
	i = 0;
	while (i < str_len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	intToHex(long num)
{
	int			i;
	const char	*hexDigits = "0123456789ABCDEF";
	char		hexStr[20];
	long		temp;

	ft_putstr_fd("0x", 1);
	i = 0;
	while (num > 0)
	{
		
		temp = num % 16;
		num = num / 16;
		hexStr[i] = hexDigits[temp];
		i++;
	}
	printf("%s", hexStr);
}

void	print_pointer(void *ptr)
{
	unsigned long	ptr_unsigned;

	ptr_unsigned = (unsigned long)ptr;
	intToHex(ptr_unsigned);
	// printf("THIS IS POINTER: %lu", ptr_unsigned);
	// ft_putstr_fd(ptr, 1);
}

void	select_input_type(const char *format, va_list args, int i)
{
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] == 'c')
			return (ft_putchar_fd(va_arg(args, int), 1));
		else if (format[i] == '%' && format[i + 1] == 's')
			return (ft_putstr_fd(va_arg(args, char *), 1));
		else if (format[i] == '%' && format[i + 1] == 'p')
			return (print_pointer(va_arg(args, void *)));
		else if (format[i] == '%' && format[i + 1] == 'd')
			return (print_integer(args));
		else if (format[i] == '%' && format[i + 1] == 'i')
			return (print_integer(args));
		else if (format[i] == '%' && format[i + 1] == 'u')
			printf("Prints an unsigned decimal (base 10) number.\n");
		else if (format[i] == '%' && format[i + 1] == 'x')
			printf("Prints a number in hexadecimal (base 16) lowercase format.\n");
		else if (format[i] == '%' && format[i + 1] == 'X')
			printf("Prints a number in hexadecimal (base 16) uppercase format.\n");
		else if (format[i] == '%' && format[i + 1] == '%')
			return (ft_putchar_fd('%', 1));
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			select_input_type(format, args, i);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
		}
		i++;
	}
	va_end(args);
	printf("\n");
	return (0);
}

// first we separa format and variadic function
// we have to get the input string from format and %X<-the type of format
//+ we have to do va_ manipulations

// go over the format, locate % sign and if its single separate