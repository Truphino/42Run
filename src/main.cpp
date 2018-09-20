/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:25:18 by trecomps          #+#    #+#             */
/*   Updated: 2018/09/20 19:24:03 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forty_two_run.hpp"
#include "assimp/Importer.hpp"
#include "Model.class.hpp"
#include <unistd.h>

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
		Model model(win, argv[1]);
		while (!quit)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
			model.draw(shader);
			}
		}
	}
	else
		exit(1);
}
