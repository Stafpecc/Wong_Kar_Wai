/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:04:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/02/21 09:06:35 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"

int	convert_char(t_dprintf *data, int c)
{
	if (add_to_buffer(&data->buffer, (char)c) == -1)
		return (-1);
	return (1);
}

int	convert_str(t_dprintf *data, char *str)
{
	const char	*null = "(null)";
	size_t		i;
	size_t		len;

	i = 0;
	if (!str)
	{
		while (null[i])
		{
			if (add_to_buffer(&data->buffer, null[i]) == -1)
				return (-1);
			i++;
		}
		return ((int)i);
	}
	len = ft_strlen(str);
	while (str[i])
	{
		if (add_to_buffer(&data->buffer, str[i]) == -1)
			return (-1);
		i++;
	}
	return ((int)len);
}

int	convert_int(t_dprintf *data, int n)
{
	char	*number;
	size_t	i;
	size_t	len;

	number = ft_itoa(n);
	if (!number)
		return (-1);
	len = ft_strlen(number);
	i = 0;
	while (number[i])
	{
		if (add_to_buffer(&data->buffer, number[i]) == -1)
		{
			free(number);
			return (-1);
		}
		i++;
	}
	free(number);
	return (len);
}

int	add_to_buffer(char **buffer, char c)
{
	char	*new_buffer;
	size_t	len;

	if (!*buffer)
	{
		*buffer = malloc(sizeof(char) * 2);
		if (!*buffer)
			return (-1);
		(*buffer)[0] = c;
		(*buffer)[1] = '\0';
		return (1);
	}
	len = ft_strlen(*buffer);
	new_buffer = malloc(sizeof(char) * (len + 2));
	if (!new_buffer)
		return (-1);
	ft_strcpy(new_buffer, *buffer);
	new_buffer[len] = c;
	new_buffer[len + 1] = '\0';
	free(*buffer);
	*buffer = new_buffer;
	return (1);
}
