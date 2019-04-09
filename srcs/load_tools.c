/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:18:00 by llejeune          #+#    #+#             */
/*   Updated: 2019/04/09 11:18:02 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			load_texture_wall(t_context *ct)
{
	ct->wall.motif_red = init_texture("./images/blocgris.bmp", ct);
	ct->wall.motif_yellow = init_texture("./images/murgris.bmp", ct);
	ct->wall.motif_green = init_texture("./images/bloc.bmp", ct);
	ct->wall.motif_blue = init_texture("./images/murroux.bmp", ct);
}

void			load_texture_backgr(t_context *ct)
{
	ct->tex.ground = init_texture("./images/Floor.bmp", ct);
	ct->tex.sky = init_texture("./images/Sky.bmp", ct);
	ct->tex.fireworks[0] = init_texture_png("./images/Fireworks3.png", ct);
	ct->tex.fireworks[1] = init_texture_png("./images/Fireworks4.png", ct);
	ct->tex.fireworks[2] = init_texture_png("./images/Fireworks5.png", ct);
	ct->tex.fireworks[3] = init_texture_png("./images/Fireworks6.png", ct);
	ct->tex.fireworks[4] = init_texture_png("./images/Fireworks7.png", ct);
	ct->tex.fireworks[5] = init_texture_png("./images/Fireworks8.png", ct);
	ct->tex.fireworks[6] = init_texture_png("./images/Fireworks9.png", ct);
	ct->tex.fireworks[7] = init_texture_png("./images/Fireworks10.png", ct);
	ct->tex.fireworks[8] = init_texture_png("./images/Fireworks11.png", ct);
	ct->tex.fireworks[9] = init_texture_png("./images/Fireworks12.png", ct);
}

void			load_texture_obj(t_context *ct)
{
	ct->tex.key = init_texture_png("./images/Key.png", ct);
	ct->tex.mushroom = init_texture_png("./images/Mushroom.png", ct);
	ct->tex.tuyau = init_texture_png("./images/tuyau.png", ct);
}

void			load_font(t_context *ct)
{
	ct->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 35);
	if (ct->font == NULL)
		quit("TTF_OpenFont()failed", ct);
}

void			load_music(t_context *ct)
{
	ct->music = Mix_LoadMUS("./images/mario.wav");
	ct->chunk = Mix_LoadWAV("./images/sonchampi.wav");
	ct->chunky = Mix_LoadWAV("./images/levelcomplete.wav");
	ct->chunk_menu = Mix_LoadWAV("./images/son_menu.wav");
}
