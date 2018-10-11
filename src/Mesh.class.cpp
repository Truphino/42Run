/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:42:37 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/11 13:07:06 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.class.hpp"

Mesh::Mesh(const std::vector<Vertex> &v,
			const std::vector<unsigned int> &i,
			const std::vector<Texture> &t):
	_vertices(v),
	_indices(i),
	_textures(t)
{
	setupMesh();

	return ;
}

Mesh::Mesh(Mesh const &rhs)
{
	*this = rhs;
}

Mesh::~Mesh(void)
{
	return ;
}

void			Mesh::setupMesh(void)
{
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(1, &this->_vbo);
	glGenBuffers(1, &this->_ebo);

	glBindVertexArray(this->_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(Vertex), &this->_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
		&this->_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void			Mesh::draw(const Shader &shader)
{
	unsigned int	i;
	unsigned int	diffuseNr;
	unsigned int	specularNr;
	std::string		name;
	std::string		number;

	i = 0;
	diffuseNr = 1;
	specularNr = 1;
	while (i < this->_textures.size())
	{
		glActiveTexture(GL_TEXTURE0 + i);
		name = this->_textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		if (name == "texture_specular")
			number = std::to_string(specularNr++);
		shader.setUniform(("material_" + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, this->_textures[i].id);
		i++;
	}
	glBindVertexArray(this->_vao);
	glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

unsigned int				Mesh::getVao(void) const
{
	return (this->_vao);
}

unsigned int				Mesh::getVbo(void) const
{
	return (this->_vbo);
}

unsigned int				Mesh::getEbo(void) const
{
	return (this->_ebo);
}

std::vector<Vertex>			Mesh::getVertices(void) const
{
	return (this->_vertices);
}

std::vector<unsigned int>	Mesh::getIndices(void) const
{
	return (this->_indices);
}

std::vector<Texture>		Mesh::getTextures(void) const
{
	return (this->_textures);
}

Mesh			&Mesh::operator=(Mesh const &rhs)
{
	if (this != &rhs)
	{
		this->_vao = rhs.getVao();
		this->_vbo = rhs.getVbo();
		this->_ebo = rhs.getEbo();
		this->_vertices = rhs.getVertices();
		this->_indices = rhs.getIndices();
		this->_textures = rhs.getTextures();
	}
	return (*this);
}

std::ostream	&Mesh::printVertices(std::ostream &o) const
{
	unsigned int			i;

	i = 0;
	while (i < this->_vertices.size())
	{
		o << this->_vertices[i].Position[0] << "\t"
			<< this->_vertices[i].Position[1] << "\t"
			<< this->_vertices[i].Position[2] << "\t"
			<< std::endl;
		i++;
	}

	return (o);
}
