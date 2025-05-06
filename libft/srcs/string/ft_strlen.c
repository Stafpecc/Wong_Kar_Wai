/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:57:04 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/12 22:48:18 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	ssize_t	i;

	i = -1;
	while (s[++i])
		;
	return ((size_t) i);
}
