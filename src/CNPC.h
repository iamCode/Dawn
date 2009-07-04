/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#ifndef __C_NPC__
#define __C_NPC__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "CTexture.h"

class CNPC {
    private:

    public:

    CNPC ( int _x_spawn_pos, int _y_spawn_pos, int _NPC_id, int _respawn_rate, int _do_respawn) {
        x_pos = _x_spawn_pos; y_pos = _y_spawn_pos;
        x_spawn_pos = _x_spawn_pos; y_spawn_pos = _y_spawn_pos;
        NPC_id = _NPC_id, respawn_rate = _respawn_rate; do_respawn = _do_respawn;
        time_to_respawn = _respawn_rate;
        alive = true;
        current_frame = 1; // this will be altered later on to draw what animation frame we want to draw.
        lastframe_respawn = 0.0f; thisframe_respawn = 0.0f; // helps us count when to respawn the NPC.
    };

    int x_pos, y_pos, x_spawn_pos, y_spawn_pos, NPC_id, respawn_rate, time_to_respawn;
    int current_frame;
    bool do_respawn, alive;
    CTexture texture;
    float lastframe_respawn, thisframe_respawn;

};

#endif
