/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 10:28:46 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/11 15:48:17 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_CLASS_H
# define SHADER_CLASS_H

#include "externals_headers.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {

public :

	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	~Shader(void);

	unsigned int		get_id() const;
	void				use();
	void				setUniform(const std::string &name, bool value) const;
	void				setUniform(const std::string &name, int value) const;
	void				setUniform(const std::string &name, unsigned int value) const;
	void				setUniform(const std::string &name, float value) const;
	void				setUniform(const std::string &name, glm::vec3 value) const;
	void				setUniform(const std::string &name, glm::mat4 value) const;
	void				setUniform(const std::string &name, glm::mat3 value) const;
	std::string			getVShaderCode() const;
	std::string			getFShaderCode() const;

private :
	Shader(void);
	Shader(Shader const &rhs);
	Shader	&operator=(Shader const &rhs);

	std::string		readShaderFile(const GLchar *shaderPath) const;
	unsigned int	compileShader(GLenum shaderType, const char *shaderCode) const;
	void			shaderProgram(unsigned int vertexId, unsigned int fragmentId);

	unsigned int		_id;
	std::string			_vShaderCode;
	std::string			_fShaderCode;
	int					_inUse;
};

std::ostream		&operator<<(std::ostream &o, Shader const &i);

#endif
