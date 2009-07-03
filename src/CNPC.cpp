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

#include "CNPC.h"

int CNPC::LoadSpawnPoints(char *file) {
    FILE *fp;
    char buf[255];
    int NPC_id = 0, x_pos = 0, y_pos = 0, respawn_rate = 0, do_respawn = 0;

    // open the zoneX.spawnpoints-file, if not give us an error in stdout.txt.
    if ((fp=fopen(file, "r")) == NULL) {
        std::cout << "ERROR opening file " << file << std::endl << std::endl;
        return -1;
    }

    while(!feof(fp)) {
        fgets(buf, 255, fp);
        if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' && buf[0] != '\n' && strlen(buf) != 0) {
            sscanf(buf, "%d %d %d %d %d", &x_pos, &y_pos, &NPC_id, &respawn_rate, &do_respawn);
            // the old shadowmap here, keeping it a while. ShadowMap.push_back(sShadowMap(x_pos,y_pos,texture_id, transparency, red, green, blue));
            NPC.push_back(sNPCs(x_pos,y_pos,NPC_id,respawn_rate, do_respawn));
        }
    }

    fclose(fp);
    return 0;
};

void CNPC::RespawnNPCs() {
    for (unsigned int x=0; x<NPC.size(); x++) {
        if (NPC[x].alive == false && NPC[x].do_respawn == true) {
            NPC[x].thisframe_respawn = SDL_GetTicks();
            if ((NPC[x].thisframe_respawn-NPC[x].lastframe_respawn) > 1000) {
                NPC[x].time_to_respawn--;
                NPC[x].lastframe_respawn = NPC[x].thisframe_respawn;
                if (NPC[x].time_to_respawn == 0) {
                    NPC[x].alive = true;
                    NPC[x].time_to_respawn = NPC[x].respawn_rate;
                }
            }
        }
    }
};

void CNPC::DrawNPCs() {
    for (unsigned int x=0;x<NPC.size();x++) {
        if (NPC[x].alive == true) {
            NPC[x].texture.DrawTexture(NPC[x].x_pos,NPC[x].y_pos,NPC[x].current_frame);
        }
    }
};

void CNPC::Init() {
        NPC[0].texture.texture.reserve(10);
        NPC[0].texture.LoadIMG("data/character/pacman/pacman_s.tga",1);
};
