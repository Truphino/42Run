/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:46:33 by trecomps          #+#    #+#             */
/*   Updated: 2018/09/20 16:32:53 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_CPP
# define STRUCTS_CPP

# include "externals_headers.hpp"
# include <glm/vec3.hpp>
# include <glm/vec2.hpp>

struct		Vertex
{
	glm::vec3	Position;
	glm::vec3	Normal;
	glm::vec2	TexCoords;
};

struct		Texture
{
	unsigned int	id;
	std::string		type;
	std::string		path;
};

#endif
