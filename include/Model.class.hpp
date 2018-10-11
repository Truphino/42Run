/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:48:30 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/11 11:28:43 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_CLASS_H
# define MODEL_CLASS_H

#include <iostream>
#include "Mesh.class.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class Model {

public :

	enum transformation_type {
		TRANSLATION,
		ROTATION,
		SCALING
		};

	Model(char *path);
	~Model(void);

	void		draw(const Shader &shader);
	void		setTransformations(glm::vec3 const &translation,
									glm::vec3 const &scale,
									glm::vec3 const &rotation);
	void		buildModelMatrix(void);
	glm::mat4	const &getModelMatrix(void) const;
	std::ostream	&printVertices(std::ostream &o) const;
	void			addTransformation(glm::vec3 const &transformation, transformation_type t);

private :
	Model(void);
	Model(Model const &rhs);
	Model	&operator=(Model const &rhs);

	void					loadModel(std::string path);
	void					loadVertex(std::vector<Vertex> &vertex,
								aiMesh *mesh, unsigned int i);
	void					loadIndices(std::vector<unsigned int> &indices,
								aiMesh *mesh, unsigned int i);
	void					loadMaterial(std::vector<Texture> &textures,
								aiMesh *mesh, const aiScene *scene);
	void					processNode(aiNode *node, const aiScene *scene);
	Mesh					processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture>	loadMaterialTextures(aiMaterial *mat,
								aiTextureType type, std::string typeName);
	unsigned int			textureFromFile(const char *path, const std::string &directory);

	std::vector<Mesh>		_meshes;
	std::string				_directory;
	std::vector<Texture>	_textures_loaded;
	glm::vec3				_translate;
	glm::vec3				_scale;
	glm::vec3				_rotation;
	glm::mat4				_model_matrix;
};

#endif
