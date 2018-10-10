/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:25:18 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/10 14:03:33 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forty_two_run.hpp"
#include "assimp/Importer.hpp"
#include "Model.class.hpp"
#include <unistd.h>

glm::mat4		transform(glm::vec2 const &Orientation,
		glm::vec3 const &Translate,
		glm::vec3 const &Up)
{
	glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1000.f / 600.f, 0.1f, 1000.f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
	glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
	glm::mat4 Model = glm::mat4(1.0f);
	return Proj * View * Model;
}

SDL_Window		*init_sdl()
{
	SDL_Window	*win;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Coundn't init sdl" << std::endl;
	SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0)
		std::cout <<SDL_GetError() << std::endl;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	win = SDL_CreateWindow("RUN !!!!!!!!!!!!!!!",
			100, 200, 1000, 600, SDL_WINDOW_OPENGL);
	if (SDL_GL_CreateContext(win) == NULL)
		std::cout << "Cannot init gl context" << std::endl;
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew error" << std::endl;
		exit(1);
	}
	glClearColor(0.6, 0.6, 0.8, 1);
	return (win);
}

int		main(int argc, char **argv)
{
	SDL_Window	*win;
	int			quit;
	SDL_Event	event;

	quit = 0;
	if (argc >= 2)
	{
		win = init_sdl();
		Shader shader("./vertex_shader.vert", "./fragment_shader.frag");
		shader.use();
		shader.setUniform("projection_matrix",
				glm::perspective(glm::radians(60.f), 1000.f / 600.f, 0.1f, 100.f));
		shader.setUniform("view_matrix",
				glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)));
		Model model(argv[1]);
		model.setTransformations(glm::vec3(0, -5, -20), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));
		model.buildModelMatrix();
		shader.setUniform("model_matrix",
				model.getModelMatrix());
		while (!quit)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				model.draw(shader);
				SDL_GL_SwapWindow(win);
			}
		}
	}
	else
		exit(1);
}
