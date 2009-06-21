/**                    Dawn - 2D roleplaying game
    Copyright (C) 2009  Tobias Eliasson (arnestig@users.sourceforge.net)

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

#include "CZone.h"

void CZone::DrawZone() {
    DrawTiles(); // draw the tiles (ground) first.
    DrawEnvironment(); // then the environment.. cliffs, trees, stones, water ... you name it.
    DrawShadows(); // then draw the shadows (not shadows from environment objects but, cloudy areas, darker places etc).
    // depending on what transparency, color setting and such we have been using, we reset the color+transparency here.
    glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void CZone::LoadZone(char *file) {
    char texturemap[32], textureenvironment[32], collisionmap[32], tilemap[32], environmentmap[32], textureshadow[32], shadowmap[32];

    sprintf(texturemap,"%s.textures",file);
    sprintf(tilemap,"%s.tilemap",file);
    sprintf(textureenvironment,"%s.textureenvironment",file);
    sprintf(environmentmap,"%s.environmentmap",file);
    sprintf(shadowmap,"%s.shadowmap",file);
    sprintf(textureshadow,"%s.textureshadow",file);
    sprintf(collisionmap,"%s.collisionmap",file);

    ZoneTiles.LoadTextureMap(texturemap);
    ZoneEnvironment.LoadTextureMap(textureenvironment,true);
    ZoneShadow.LoadTextureMap(textureshadow);

    LoadMap(tilemap);
    LoadEnvironment(environmentmap);
    LoadShadow(shadowmap);
    LoadCollisions(collisionmap);
}

int CZone::LoadCollisions(char *file) {
    FILE *fp;
    char buf[255];
    int CR_x = 0, CR_y = 0, CR_h = 0, CR_w = 0;

    // open the texturemap-file, if not give us an error in stdout.txt.
    if ((fp=fopen(file, "r")) == NULL) {
        printf("ERROR opening file %s\n\n", file);
        return -1;
    }

    while(!feof(fp)) {
        fgets(buf, 255, fp);
        if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' && buf[0] != '\n' && strlen(buf) != 0) {
            sscanf(buf, "%d %d %d %d", &CR_x, &CR_y, &CR_h, &CR_w);
            CollisionMap.push_back(sCollisionMap(CR_x,CR_y,CR_h,CR_w));
        }
    }
    fclose(fp);
    return 0;
}

int CZone::LoadEnvironment(char *file) {
    FILE *fp;
    char buf[255];
    int texture_id = 0, x_pos = 0, y_pos = 0;
    float transparency, red, green, blue;

    // open the texturemap-file, if not give us an error in stdout.txt.
    if ((fp=fopen(file, "r")) == NULL) {
        printf("ERROR opening file %s\n\n", file);
        return -1;
    }

    int count = 0;
    while(!feof(fp)) {
        fgets(buf, 255, fp);
        if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' && buf[0] != '\n' && strlen(buf) != 0) {
            sscanf(buf,"%d %d %d %f %f %f %f", &x_pos, &y_pos, &texture_id, &transparency, &red, &green, &blue);
            EnvironmentMap.push_back(sEnvironmentMap(x_pos,y_pos,texture_id,transparency, red, green, blue));
            count++;
        }
    }
    fclose(fp);
    return 0;
}

int CZone::LoadShadow(char *file) {
    FILE *fp;
    char buf[255];
    int texture_id = 0, x_pos = 0, y_pos = 0;
    float transparency, red, green, blue;

    // open the shadowmap-file, if not give us an error in stdout.txt.
    if ((fp=fopen(file, "r")) == NULL) {
        printf("ERROR opening file %s\n\n", file);
        return -1;
    }

    int count = 0;
    while(!feof(fp)) {
        fgets(buf, 255, fp);
        if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' && buf[0] != '\n' && strlen(buf) != 0) {
            sscanf(buf, "%d %d %d %f %f %f %f", &x_pos, &y_pos, &texture_id, &transparency, &red, &green, &blue);
            // the old shadowmap here, keeping it a while. ShadowMap.push_back(sShadowMap(x_pos,y_pos,texture_id, transparency, red, green, blue));
            ShadowMap.push_back(sEnvironmentMap(x_pos,y_pos,texture_id, transparency, red, green, blue));
            count++;
        }
    }
    fclose(fp);
    return 0;
}

int CZone::LoadMap(char *file) {
    FILE *fp;
    char buf[255];
    int texture_id = 0, x_pos = 0, y_pos = 0;

    // open the texturemap-file, if not give us an error in stdout.txt.
    if ((fp=fopen(file, "r")) == NULL) {
        printf("ERROR opening file %s\n\n", file);
        return -1;
    }

    int count = 0;
    while(!feof(fp)) {
        fgets(buf, 255, fp);
        if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' && buf[0] != '\n' && strlen(buf) != 0) {
            sscanf(buf, "%d %d %d", &x_pos, &y_pos, &texture_id);
            TileMap.push_back(sTileMap(x_pos,y_pos,texture_id));
            count++;
        }
    }

    fclose(fp);
    return 0;
}


void CZone::DrawTiles() {
    for (unsigned int x=0;x<TileMap.size();x++) {
        ZoneTiles.DrawTexture(TileMap[x].x_pos,TileMap[x].y_pos,TileMap[x].id);
    }
}

void CZone::DrawEnvironment() {
    for (unsigned int x=0;x<EnvironmentMap.size();x++) {
        ZoneEnvironment.DrawTexture(EnvironmentMap[x].x_pos,EnvironmentMap[x].y_pos,EnvironmentMap[x].id, EnvironmentMap[x].transparency, EnvironmentMap[x].red, EnvironmentMap[x].green, EnvironmentMap[x].blue);
    }
}

void CZone::DrawShadows() {
    for (unsigned int x=0;x<ShadowMap.size();x++) {
        ZoneShadow.DrawTexture(ShadowMap[x].x_pos,ShadowMap[x].y_pos,ShadowMap[x].id, ShadowMap[x].transparency, ShadowMap[x].red, ShadowMap[x].green, ShadowMap[x].blue);
    }
}

int CZone::LocateTile(int x, int y) {
    for (unsigned int t=0;t<TileMap.size();t++) {
        if ((TileMap[t].x_pos+ZoneTiles.texture[TileMap[t].id].width > x) && (TileMap[t].x_pos < x)) {
            if ((TileMap[t].y_pos+ZoneTiles.texture[TileMap[t].id].height > y) && (TileMap[t].y_pos < y)) {
                return t;
            }
        }
    }
    return -1;
}

int CZone::LocateTexture(int x, int y) {
    for (unsigned int t=0;t<TileMap.size();t++) {
        if ((TileMap[t].x_pos == x) && (TileMap[t].y_pos == y)) {
            return TileMap[t].id;
        }
    }
    return -1;
}

void CZone::ChangeTile(int iId, int texture) {
    if (iId >= 0) {
        TileMap[iId].id = texture;
    }
}

void CZone::DeleteTile(int iId) {
    if (iId >= 0) {
        TileMap[iId].id = 0;
    }
}

void CZone::AddEnvironment(int x_pos, int y_pos, int texture) {
    // add environment to our environmentvector.
    // x and y cords and devide and substract the height and width of the image so we place the texture
    // in the middle of the cursor.
    // IF the environmenttexture has an collision_box we also push that info into the collisionvector.
    EnvironmentMap.push_back(sEnvironmentMap(x_pos-(ZoneEnvironment.texture[texture].width/2),y_pos-(ZoneEnvironment.texture[texture].height/2),texture, 1.0f, 1.0f, 1.0f, 1.0f));
    if (ZoneEnvironment.texture[texture].contains_collision_box == true) {
        CollisionMap.push_back(sCollisionMap(x_pos-(ZoneEnvironment.texture[texture].width/2)+ZoneEnvironment.texture[texture].collision_box.x,y_pos-(ZoneEnvironment.texture[texture].height/2)+ZoneEnvironment.texture[texture].collision_box.y,ZoneEnvironment.texture[texture].collision_box.h,ZoneEnvironment.texture[texture].collision_box.w));
    }
}

void CZone::AddShadow(int x_pos, int y_pos, int texture) {
    // the old shadowmap here, keeping it a while... ShadowMap.push_back(sShadowMap(x_pos-(ZoneShadow.texture[texture].width/2),y_pos-(ZoneShadow.texture[texture].height/2),texture, 1.0f, 1.0f, 1.0f, 1.0f));
    ShadowMap.push_back(sEnvironmentMap(x_pos-(ZoneShadow.texture[texture].width/2),y_pos-(ZoneShadow.texture[texture].height/2),texture, 1.0f, 1.0f, 1.0f, 1.0f));
}


int CZone::DeleteEnvironment(int x, int y) {
    for (unsigned int t=0;t<EnvironmentMap.size();t++) {
        if ((EnvironmentMap[t].x_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].width > x) && (EnvironmentMap[t].x_pos < x)) {
            if ((EnvironmentMap[t].y_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].height > y) && (EnvironmentMap[t].y_pos < y)) {
                EnvironmentMap.erase(EnvironmentMap.begin()+t);
                return 0;
            }
        }
    }
    return 1;
}

int CZone::LocateEnvironment(int x, int y) {
    for (unsigned int t=0;t<EnvironmentMap.size();t++) {
        if ((EnvironmentMap[t].x_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].width > x) && (EnvironmentMap[t].x_pos < x)) {
            if ((EnvironmentMap[t].y_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].height > y) && (EnvironmentMap[t].y_pos < y)) {
                return t;
            }
        }
    }
    return -1;
}

int CZone::LocateShadow(int x, int y) {
    for (unsigned int t=0;t<ShadowMap.size();t++) {
        if ((ShadowMap[t].x_pos+ZoneShadow.texture[ShadowMap[t].id].width > x) && (ShadowMap[t].x_pos < x)) {
            if ((ShadowMap[t].y_pos+ZoneShadow.texture[ShadowMap[t].id].height > y) && (ShadowMap[t].y_pos < y)) {
                return t;
            }
        }
    }
    return -1;
}

int CZone::DeleteShadow(int x, int y) {
    for (unsigned int t=0;t<ShadowMap.size();t++) {
        if ((ShadowMap[t].x_pos+ZoneShadow.texture[ShadowMap[t].id].width > x) && (ShadowMap[t].x_pos < x)) {
            if ((ShadowMap[t].y_pos+ZoneShadow.texture[ShadowMap[t].id].height > y) && (ShadowMap[t].y_pos < y)) {
                ShadowMap.erase(ShadowMap.begin()+t);
                return 0;
            }
        }
    }
    return 1;
}