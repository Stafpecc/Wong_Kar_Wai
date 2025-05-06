/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:33:31 by gueberso          #+#    #+#             */
/*   Updated: 2025/02/20 21:37:32 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_dprintf
{
	char	*buffer;
	int		index;
}	t_dprintf;

int		add_to_buffer(char **buffer, char c);

int		convert_char(t_dprintf *data, int c);
int		convert_int(t_dprintf *data, int n);
int		convert_str(t_dprintf *data, char *str);

int		ft_dprintf(int fd, const char *format, ...)
		__attribute__((format(printf, 2, 3)));

#endif
