/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:26:31 by llejeune          #+#    #+#             */
/*   Updated: 2019/04/09 11:26:35 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			action_loop_game(t_context *ct, Uint8 *state,
	unsigned int delta_time)
{
	SDL_Event		event;

	while (SDL_PollEvent(&event))
	{
		((state[SDL_SCANCODE_C]) && (event.type == SDL_KEYDOWN)) ?
		ct->choose_inter = (ct->choose_inter + 1) % INTERFACE_NB : 0;
		(event.type == SDL_QUIT) ? quit("Thank you for playing", ct) : 0;
		common_actions(ct, state, event);
	}
	ct->cam.angle = angle_limit(ct->cam.angle);
	SDL_SetRenderDrawColor(ct->rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ct->rend);
	choose_interface(ct);
	if (ct->show_fps == TRUE)
		show_fps(ct);
	SDL_RenderPresent(ct->rend);
	update_settings(ct);
	key_events(ct, state, delta_time);
}

int				one_second_passed(t_context *ct,
	int one_second_count, int fps_count)
{
	if (one_second_count > 1000)
	{
		ct->fps = fps_count;
		return (TRUE);
	}
	else
		return (FALSE);
}

void			manage_music(t_context *ct)
{
	if (ct->choose_inter != FIREWORKS)
		Mix_PlayMusic(ct->music, -1);
	else
		Mix_PlayChannel(MIX_DEFAULT_CHANNELS, ct->chunky, -1);
}

void			common_actions(t_context *ct, Uint8 *state, SDL_Event event)
{
	((state[SDL_SCANCODE_1]) && (event.type == SDL_KEYDOWN)) ?
	ct->full_screen = -ct->full_screen : 0;
	(state[SDL_SCANCODE_M] && event.type == SDL_KEYDOWN) ?
	ct->mute = -ct->mute : 0;
	(state[SDL_SCANCODE_9] && event.type == SDL_KEYDOWN) ? ct->volume-- : 0;
	(state[SDL_SCANCODE_0] && event.type == SDL_KEYDOWN) ? ct->volume++ : 0;
	(state[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN) ?
	quit("Thank you for playing", ct) : 0;
	((state[SDL_SCANCODE_F]) && (event.type == SDL_KEYDOWN)) ?
	ct->show_fps = (ct->show_fps + 1) % 2 : 0;
}

void			update_settings(t_context *ct)
{
	while (ct->volume < 0)
		ct->volume++;
	Mix_VolumeMusic(ct->volume);
	Mix_VolumeChunk(ct->chunk, ct->volume);
	(ct->mute < 0) ? Mix_PauseMusic() : Mix_ResumeMusic();
	if (ct->full_screen < 0)
	{
		SDL_SetWindowFullscreen(ct->window, SDL_WINDOW_FULLSCREEN);
		SDL_GetWindowSize(ct->window, &ct->xwin, &ct->ywin);
	}
	if (ct->full_screen > 0)
	{
		ct->xwin = XWIN;
		ct->ywin = YWIN;
		SDL_SetWindowSize(ct->window, ct->xwin, ct->ywin);
		SDL_SetWindowFullscreen(ct->window, 0);
		SDL_RestoreWindow(ct->window);
	}
}
