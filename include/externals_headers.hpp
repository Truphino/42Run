/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_headers.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:35:07 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/11 11:55:18 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNALS_HEADERS_HPP
# define EXTERNALS_HEADERS_HPP

# include "glew/glew.h"
# include <iostream>
# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
# else
#  include <GL/gl.h>
#  include <GL/glut.h>
# endif
# include <SDL2/SDL.h>
# include "glm/mat4x4.hpp"
# include "glm/ext.hpp"
# define GLM_ENABLE_EXPERIMENTAL
# include <glm/gtc/quaternion.hpp>
# include <glm/gtx/quaternion.hpp>

#endif
