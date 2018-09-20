/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:49:25 by trecomps          #+#    #+#             */
/*   Updated: 2018/09/20 19:23:34 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Model.class.hpp"
#include "stb.hpp"

Model::Model(SDL_Window *win, char *path)
{
	loadModel(path);
	this->_win = win;

	return ;
}

void		Model::draw(const Shader &shader)
{
	unsigned int	i;

	i = 0;
	while (i < this->_meshes.size())
	{
		this->_meshes[i].draw(shader);
		i++;
	}
	SDL_GL_SwapWindow(this->_win);
}

void		Model::loadModel(std::string path)
{
	Assimp::Importer	importer;
	const aiScene *scene = importer.ReadFile(path,
								aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	this->_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void		Model::processNode(aiNode *node, const aiScene *scene)
{
	unsigned int	i;
	aiMesh			*mesh;

	i = 0;
	while (i < node->mNumMeshes)
	{
		mesh = scene->mMeshes[node->mMeshes[i]];
		this->_meshes.push_back(processMesh(mesh, scene));
		i++;
	}
	i = 0;
	while (i < node->mNumChildren)
	{
		processNode(node->mChildren[i], scene);
		i++;
	}
}

void		Model::loadVertex(std::vector<Vertex> &vertex, aiMesh *mesh, unsigned int i)
{
	Vertex					tmp_vertex;

	tmp_vertex.Position.x = mesh->mVertices[i].x;
	tmp_vertex.Position.y = mesh->mVertices[i].y;
	tmp_vertex.Position.z = mesh->mVertices[i].z;
	tmp_vertex.Normal.x = mesh->mNormals[i].x;
	tmp_vertex.Normal.y = mesh->mNormals[i].y;
	tmp_vertex.Normal.z = mesh->mNormals[i].z;
	if (mesh->mTextureCoords[0])
	{
		tmp_vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
		tmp_vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
	}
	else
		tmp_vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	vertex.push_back(tmp_vertex);
}

void		Model::loadIndices(std::vector<unsigned int> &indices, aiMesh *mesh, unsigned int i)
{
	aiFace			face;
	unsigned int	j;

	j = 0;
	face = mesh->mFaces[i];
	while (j < face.mNumIndices)
	{
		indices.push_back(face.mIndices[j]);
		j++;
	}
}

void		Model::loadMaterial(std::vector<Texture> &textures, aiMesh *mesh, const aiScene *scene)
{
	aiMaterial	*material;

	material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
										aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<Texture> specularMaps = loadMaterialTextures(material,
										aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
}

std::vector<Texture>	Model::loadMaterialTextures(aiMaterial *mat,
							aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for(unsigned int j = 0; j < this->_textures_loaded.size(); j++)
		{
			if(std::strcmp(this->_textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(this->_textures_loaded[j]);
				skip = true; 
				break;
			}
		}
		if(!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = textureFromFile(str.C_Str(), this->_directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->_textures_loaded.push_back(texture); // add to loaded textures
		}
	}
	return textures;
}

unsigned int Model::textureFromFile(const char *path, const std::string &directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

Mesh		Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture>		textures;
	unsigned int				i;

	i = 0;
	while (i < mesh->mNumVertices)
	{
		loadVertex(vertices, mesh, i);
		i++;
	}
	i = 0;
	while (i < mesh->mNumFaces)
	{
		loadIndices(indices, mesh, i);
		i++;
	}
	if (mesh->mMaterialIndex > 0)
	{
		loadMaterial(textures, mesh, scene);
	}
	return Mesh(vertices, indices, textures);
}

Model::~Model(void)
{
	//std::cout << "Destructor called" << std::endl;
	
	return ;
}
