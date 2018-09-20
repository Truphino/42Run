/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:48:30 by trecomps          #+#    #+#             */
/*   Updated: 2018/09/20 19:20:21 by trecomps         ###   ########.fr       */
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

	Model(SDL_Window *win, char *path);
	~Model(void);

	void		draw(const Shader &shader);

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
	SDL_Window				*_win;
};

#endif
