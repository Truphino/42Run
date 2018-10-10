/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 10:29:27 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/04 11:53:59 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shader.class.hpp"

Shader::Shader(const GLchar *vertex_path, const GLchar *fragment_path) : _inUse(0)
{
	unsigned int	vertexId;
	unsigned int	fragmentId;

	this->_vShaderCode = readShaderFile(vertex_path);
	this->_fShaderCode = readShaderFile(fragment_path);
	vertexId = compileShader(GL_VERTEX_SHADER, this->_vShaderCode.c_str());
	fragmentId = compileShader(GL_FRAGMENT_SHADER, this->_fShaderCode.c_str());

	shaderProgram(vertexId, fragmentId);
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	return ;
}

Shader::~Shader(void)
{
	//std::cout << "Destructor called" << std::endl;
	
	return ;
}

std::string				Shader::readShaderFile(const GLchar *shaderPath) const
{
	std::string			shaderCode;
	std::ifstream		shaderFile;
	std::stringstream	shaderStream;

	shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return (shaderCode);
}

unsigned int			Shader::compileShader(GLenum shaderType, const char *shaderCode) const
{
	unsigned int		shaderId;
	int					success;
	char				infoLog[512];

	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	return (shaderId);
}

void					Shader::shaderProgram(unsigned int vertexId, unsigned int fragmentId)
{
	int					success;
	char				infoLog[512];

	_id = glCreateProgram();
	glAttachShader(_id, vertexId);
	glAttachShader(_id, fragmentId);
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void					Shader::use()
{
	if (this->_inUse == 0)
	{
		this->_inUse = 1;
		glUseProgram(_id);
	}
	else
		std::cout << "Program already in use" << std::endl;
}

void					Shader::setUniform(const std::string &name, bool value) const
{
	if (this->_inUse == 1)
	{
		glUniform1i(glGetUniformLocation(this->_id, name.c_str()), static_cast<int>(value));
	}
	else
		std::cout << "Program not in use" << std::endl;
}

void					Shader::setUniform(const std::string &name, int value) const
{
	if (this->_inUse == 1)
	{
		glUniform1i(glGetUniformLocation(this->_id, name.c_str()), value);
	}
	else
		std::cout << "Program not in use" << std::endl;
}

void					Shader::setUniform(const std::string &name, unsigned int value) const
{
	if (this->_inUse == 1)
	{
		glUniform1ui(glGetUniformLocation(this->_id, name.c_str()), value);
	}
	else
		std::cout << "Program not in use" << std::endl;
}

void					Shader::setUniform(const std::string &name, float value) const
{
	if (this->_inUse == 1)
	{
		glUniform1f(glGetUniformLocation(this->_id, name.c_str()), value);
	}
	else
		std::cout << "Program not in use" << std::endl;
}

void					Shader::setUniform(const std::string &name, glm::mat4 value) const
{
	if (this->_inUse == 1)
	{
		glUniformMatrix4fv(glGetUniformLocation(this->_id, name.c_str()), 1,
				GL_FALSE, glm::value_ptr(value));
	}
	else
		std::cout << "Program not in use" << std::endl;
}

unsigned int			Shader::get_id(void) const
{
	return (this->_id);
}

std::string				Shader::getVShaderCode() const
{
	return (this->_vShaderCode);
}

std::string				Shader::getFShaderCode() const
{
	return (this->_fShaderCode);
}

std::ostream	&operator<<(std::ostream &o, Shader const &i)
{
	o << "Shader id: " << i.get_id() << std::endl <<
		"Vertex shader :" << std::endl << i.getVShaderCode() <<
		std::endl << std::endl <<
		"Fragment shader :" << std::endl << i.getFShaderCode() << std::endl;

	return (o);
}
