/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:42:06 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/10 10:37:20 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_CLASS_H
# define MESH_CLASS_H

#include <iostream>
#include <vector>
#include "structs.hpp"
#include "Shader.class.hpp"

class Mesh {

public :

	Mesh(const std::vector<Vertex> &vertices,
			const std::vector<unsigned int> &indices,
			const std::vector<Texture> &textures);
	~Mesh(void);
	Mesh(Mesh const &rhs);
	Mesh	&operator=(Mesh const &rhs);

	unsigned int				getVao(void) const;
	unsigned int				getVbo(void) const;
	unsigned int				getEbo(void) const;
	std::vector<Vertex>			getVertices(void) const;
	std::vector<unsigned int>	getIndices(void) const;
	std::vector<Texture>		getTextures(void) const;
	std::ostream				&printVertices(std::ostream &o) const;

	void		draw(const Shader &shader);

private :
	Mesh(void);

	void	setupMesh(void);

	unsigned int				_vao;
	unsigned int				_vbo;
	unsigned int				_ebo;
	std::vector<Vertex>			_vertices;
	std::vector<unsigned int>	_indices;
	std::vector<Texture>		_textures;
	GLuint						_positionsAttrib;
	GLuint						_normalsAttrib;
	GLuint						_texturesAttrib;
};

#endif
