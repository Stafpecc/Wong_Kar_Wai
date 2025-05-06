/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:04:17 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/25 20:33:36 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_dprintf.h"
#include "libft.h"

static int	convert_args(t_dprintf *data, char type, va_list args)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += convert_char(data, va_arg(args, int));
	else if (type == 's')
		len += convert_str(data, va_arg(args, char *));
	else if (type == 'd' || type == 'i')
		len += convert_int(data, va_arg(args, int));
	return (len);
}

static int	handle_conversion(t_dprintf *data, const char *format, \
	va_list args, int *total_len)
{
	int	converted_len;

	data->index++;
	if (ft_strchr("cspdiuxX", format[data->index]))
	{
		converted_len = convert_args(data, format[data->index], args);
		if (converted_len == -1)
			return (-1);
		*total_len += converted_len;
	}
	else if (format[data->index] == '%')
	{
		if (!add_to_buffer(&data->buffer, format[data->index]))
			return (-1);
		(*total_len)++;
	}
	return (0);
}

static int	regular_char(t_dprintf *data, const char *format, int *total_len)
{
	if (add_to_buffer(&data->buffer, format[data->index]) == -1)
		return (-1);
	(*total_len)++;
	return (0);
}

static int	parse(int fd, const char *format, va_list args)
{
	t_dprintf	data;
	int			total_len;

	ft_memset(&data, 0, sizeof(t_dprintf));
	total_len = 0;
	while (format && format[data.index])
	{
		if (format[data.index] == '%' && format[data.index + 1])
		{
			if (handle_conversion(&data, format, args, &total_len) == -1)
				return (-1);
		}
		else if (format[data.index] == '%' && !format[data.index + 1])
			return (-1);
		else if (regular_char(&data, format, &total_len) == -1)
			return (-1);
		data.index++;
	}
	write(fd, data.buffer, total_len);
	free(data.buffer);
	return (total_len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	va_start(args, format);
	len = parse(fd, format, args);
	va_end(args);
	return (len);
}
