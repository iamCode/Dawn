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

int CNPC::LoadMobInfo() {
    FILE *fp;
    char buf[255];
    sprintf(buf,"data/NPC/%d.NPC",NPC_id);

    // open the NPC_id.npc-file, if not give us an error in stdout.txt.
    if ((fp=fopen(buf, "r")) == NULL) {
        std::cout << "ERROR opening file " << buf << std::endl << std::endl;
        return -1;
    }

    while(!feof(fp)) {
        fgets(buf, 255, fp);
        if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' && buf[0] != '\n' && strlen(buf) != 0) {
            /**
            here we should scan through the entire X.NPC file and look for
            name, level, stats, textures, abilities etc... not sure how to do this.
            should probably abandon scanf and go for some ifstream.

            The X.NPC file i thought should look like this:
            Name: A wolf pup
            Level: 1
            Min_gold: 0
            Max_gold: 0
            Loot table: 25,78,92 (points to item-ids).
            Adjusted str: -2
            Adjusted dex: -2
            Adjusted vit: -1
            Adjusted int: -5
            Adjusted wis: -5
            Adjusted health: -10
            Adjusted mana: 0
            Adjusted energy: 0

            And so on.. It will be easy to create an NPC this way I think, we only need a simple function to load all of the data.
            /Arnestig
            **/
        }
    }
    fclose(fp);
    return 0;
};

int CNPC::CheckForCollision(int x_pos, int y_pos) {
    for (unsigned int t=0;t<zone->CollisionMap.size();t++) {
        if ((zone->CollisionMap[t].CR.x+zone->CollisionMap[t].CR.w >= x_pos) && (zone->CollisionMap[t].CR.x <= x_pos)) {
            if ((zone->CollisionMap[t].CR.y+zone->CollisionMap[t].CR.h >= y_pos) && (zone->CollisionMap[t].CR.y <= y_pos)) {
                return 1;
            }
        }
    }
    return 0;
}

int CNPC::CollisionCheck(Direction direction) {
    switch (direction) {
        case N:
        // check upper left corner
        if (CheckForCollision(x_pos+1,y_pos+40) == 1) {
            return 1;
        }
        // check upper right corner
        if (CheckForCollision(x_pos+39,y_pos+40) == 1) {
            return 1;
        }
        break;

        case E:
        // check upper right corner
        if (CheckForCollision(x_pos+40,y_pos+39) == 1) {
            return 1;
        }
        // check lower right corner
        if (CheckForCollision(x_pos+40,y_pos+1) == 1) {
            return 1;
        }
        break;

        case S:
        // check lower left corner
        if (CheckForCollision(x_pos+1,y_pos+1) == 1) {
            return 1;
        }
        // check lower right corner
        if (CheckForCollision(x_pos+39,y_pos) == 1) {
            return 1;
        }
        break;

        case W:
        // check upper left corner
        if (CheckForCollision(x_pos,y_pos+39) == 1) {
            return 1;
        }
        // check lower left corner
        if (CheckForCollision(x_pos,y_pos) == 1) {
            return 1;
        }
        break;
    }
    return 0;
};

void CNPC::MoveUp() {
    if (CollisionCheck(N) == 0) {
        y_pos++;
        //current_texture = 1;
    }
};

void CNPC::MoveDown() {
    if (CollisionCheck(S) == 0) {
        y_pos--;
        //current_texture = 5;
    }
};

void CNPC::MoveLeft() {
    if (CollisionCheck(W) == 0) {
        x_pos--;
        //current_texture = 7;
    }
};

void CNPC::MoveRight() {
    if (CollisionCheck(E) == 0) {
        x_pos++;
        //current_texture = 3;
    }
};

void CNPC::Move(int direction)
{
    int movePerStep = 10; // moves one step per movePerStep ms

    //while ( remainingMovePoints > movePerStep )
    //{
        remainingMovePoints -= movePerStep;

        switch( direction )
        {
            case NW:
                MoveLeft();
                MoveUp();
            break;
            case N:
                MoveUp();
            break;
            case NE:
                MoveRight();
                MoveUp();
            break;
            case W:
                MoveLeft();
            break;
            case E:
                MoveRight();
            break;
            case SW:
                MoveLeft();
                MoveDown();
            break;
            case S:
                MoveDown();
            break;
            case SE:
                MoveRight();
                MoveDown();
            break;
            default:
            break;
        }
   // }
}

void CNPC::giveMovePoints( uint32_t movePoints )
{
    remainingMovePoints += movePoints;
}


void CNPC::Wander() {
    if (wandering) {
        if (wander_points_left > 0) {
            Move(wander_direction);
            wander_points_left--;
        } else {
            wander_lastframe = SDL_GetTicks();
            wandering = false;
        }
    } else {
        wander_thisframe = SDL_GetTicks();
        if ((wander_thisframe-wander_lastframe) > (wander_every_seconds*1000)) {
            wandering = true;
            wander_points_left = rand() % 50 + 10;
            wander_direction = rand() % 9;
            Move(wander_direction);
        }
    }
};

void CNPC::Die() {
    alive = false;
    respawn_lastframe = SDL_GetTicks();
};

void CNPC::Respawn() {
    if (alive == false && do_respawn == true) {
        respawn_thisframe = SDL_GetTicks();
        if ((respawn_thisframe-respawn_lastframe) > (seconds_to_respawn * 1000)) {
                alive = true;
                x_pos = x_spawn_pos;
                y_pos = y_spawn_pos;
                respawn_thisframe = 0.0f;
                respawn_lastframe = 0.0f;
        }
    }
};

void CNPC::Draw() {
    if (alive == true) {
        texture.DrawTexture(x_pos,y_pos,current_frame);
    }
};
