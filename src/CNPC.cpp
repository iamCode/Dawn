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
