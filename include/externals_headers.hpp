/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_headers.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:35:07 by trecomps          #+#    #+#             */
/*   Updated: 2018/09/20 18:24:44 by trecomps         ###   ########.fr       */
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

#endif
