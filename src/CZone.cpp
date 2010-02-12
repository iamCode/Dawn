/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

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

#include "CLuaFunctions.h"

void CZone::DrawZone()
{
	DrawTiles(); // draw the tiles (ground) first.
	DrawEnvironment(); // then the environment.. cliffs, trees, stones, water ... you name it.
	DrawShadows(); // then draw the shadows (not shadows from environment objects but, cloudy areas, darker places etc).
}

void CZone::LoadZone(std::string file)
{
	ZoneTiles.LoadTextureMap( std::string( file ).append ( ".textures" ) );
	ZoneEnvironment.LoadTextureMap( std::string( file ).append ( ".textureenvironment" ) ,true);
	ZoneShadow.LoadTextureMap( std::string( file ).append ( ".textureshadow" ) );

	LoadMap( std::string( file ).append ( ".tilemap" ) );
	LoadEnvironment( std::string( file ).append ( ".environmentmap" ) );
	LoadShadow( std::string( file ).append ( ".shadowmap" ) );
	LoadCollisions( std::string( file ).append ( ".collisionmap" ) );
	LuaFunctions::executeLuaFile( std::string( file ).append( ".spawnpoints" ) );
}

int CZone::LoadCollisions(std::string file)
{
	char buf[255];
	int CR_x = 0, CR_y = 0, CR_h = 0, CR_w = 0;

	std::ifstream input_file(file.c_str());

	// open the texturemap-file, if not give us an error in stdout.txt.
	if (!input_file) {
		std::cout << "ERROR opening file " << file << std::endl << std::endl;
		return -1;
	}

	while (input_file.getline (buf, 255)) {
		if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' &&
		        buf[0] != '\n' && strlen(buf) != 0) {
			sscanf(buf, "%d %d %d %d", &CR_x, &CR_y, &CR_h, &CR_w);
			CollisionMap.push_back(sCollisionMap(CR_x,CR_y,CR_h,CR_w));
		}
	}
	input_file.close();

	return 0;
}

int CZone::LoadEnvironment(std::string file)
{
	std::ifstream input_file(file.c_str());
	char buf[255];
	int texture_id = 0, x_pos = 0, y_pos = 0;
	float transparency, red, green, blue, x_scale, y_scale;
	int count = 0;

	// open the texturemap-file, if not give us an error in stdout.txt.
	if (!input_file) {
		std::cout << "ERROR opening file " << file << std::endl << std::endl;
		return -1;
	}

	for (count = 0 ; input_file.getline (buf, 255) ; ++count) {
		if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' &&
		        buf[0] != '\n' && strlen(buf) != 0) {
			sscanf(buf,"%d %d %d %f %f %f %f %f %f", &x_pos, &y_pos, &texture_id, &transparency, &red, &green, &blue, &x_scale, &y_scale);
			EnvironmentMap.push_back(sEnvironmentMap(x_pos,y_pos,texture_id,transparency, red, green, blue, x_scale, y_scale));
		}
	}

	input_file.close();

    std::sort(EnvironmentMap.begin(), EnvironmentMap.end());

	return 0;
}

int CZone::LoadShadow(std::string file)
{
	std::ifstream input_file(file.c_str());
	char buf[255];
	int texture_id = 0, x_pos = 0, y_pos = 0;
	float transparency, red, green, blue, x_scale, y_scale;
	int count = 0;

	// open the shadowmap-file, if not give us an error in stdout.txt.
	if (!input_file) {
		std::cout << "ERROR opening file " << file << std::endl << std::endl;
		return -1;
	}

	for (count = 0 ; input_file.getline (buf, 255) ; ++count) {
		if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' &&
		        buf[0] != '\n' && strlen(buf) != 0) {
			sscanf(buf, "%d %d %d %f %f %f %f %f %f", &x_pos, &y_pos, &texture_id, &transparency, &red, &green, &blue, &x_scale, &y_scale);
			// the old shadowmap here, keeping it a while. ShadowMap.push_back(sShadowMap(x_pos,y_pos,texture_id, transparency, red, green, blue));
			ShadowMap.push_back(sEnvironmentMap(x_pos,y_pos,texture_id,transparency, red, green, blue, x_scale, y_scale));
			count++;
		}
	}

	input_file.close();

	return 0;
}

int CZone::LoadMap(std::string file)
{
	std::ifstream input_file(file.c_str());
	char buf[255];
	int texture_id = 0, x_pos = 0, y_pos = 0;
	int count = 0;

	// open the texturemap-file, if not give us an error in stdout.txt.
	if (!input_file) {
		std::cout << "ERROR opening file " << file << std::endl << std::endl;
		return -1;
	}

	for (count = 0 ; input_file.getline (buf, 255) ; ++count) {
		if (buf[0] != '#' && buf[0] != '\r' && buf[0] != '\0' &&
		        buf[0] != '\n' && strlen(buf) != 0) {
			sscanf(buf, "%d %d %d", &x_pos, &y_pos, &texture_id);
			TileMap.push_back(sTileMap(x_pos,y_pos,texture_id));
			count++;
		}
	}
	std::sort(TileMap.begin(), TileMap.end()); // sort our vector based on texture, less calls to glBindTexture() = more performance.

	input_file.close();
	return 0;
}


void CZone::DrawTiles()
{
	for (unsigned int x=0 ; x < TileMap.size() ; x++) {
		ZoneTiles.DrawTexture(TileMap[x].x_pos,TileMap[x].y_pos,TileMap[x].id);
	}
}

void CZone::DrawEnvironment()
{
	for (unsigned int x=0 ; x < EnvironmentMap.size() ; x++) {
		ZoneEnvironment.DrawTexture(EnvironmentMap[x].x_pos,
		                            EnvironmentMap[x].y_pos,EnvironmentMap[x].id,
		                            EnvironmentMap[x].transparency, EnvironmentMap[x].red,
		                            EnvironmentMap[x].green, EnvironmentMap[x].blue,
		                            EnvironmentMap[x].x_scale, EnvironmentMap[x].y_scale);
	}
}

void CZone::DrawShadows()
{
	for (unsigned int x=0 ; x < ShadowMap.size() ; x++) {
		ZoneShadow.DrawTexture(ShadowMap[x].x_pos,ShadowMap[x].y_pos,ShadowMap[x].id,
		                       ShadowMap[x].transparency, ShadowMap[x].red,
		                       ShadowMap[x].green, ShadowMap[x].blue, ShadowMap[x].x_scale,
		                       ShadowMap[x].y_scale);
	}
}

int CZone::LocateTile(int x, int y)
{
	for (unsigned int t=0;t<TileMap.size();t++) {
		if ((TileMap[t].x_pos+ZoneTiles.texture[TileMap[t].id].width > x) &&
		        (TileMap[t].x_pos < x)) {
			if ((TileMap[t].y_pos+ZoneTiles.texture[TileMap[t].id].height > y) &&
			        (TileMap[t].y_pos < y)) {
				return t;
			}
		}
	}
	return -1;
}

void CZone::ChangeTile(int iId, int texture)
{
	if (iId >= 0) {
		TileMap[iId].id = texture;
	}
}

void CZone::DeleteTile(int iId)
{
	if (iId >= 0) {
		TileMap[iId].id = 0;
	}
}

void CZone::AddEnvironment(int x_pos, int y_pos, int texture)
{
	// add environment to our environmentvector.
	// x and y cords and devide and substract the height and width of the image so we place the texture
	// in the middle of the cursor.
	// IF the environmenttexture has an collision_box we also push that info into the collisionvector.
	EnvironmentMap.push_back(sEnvironmentMap(x_pos-(ZoneEnvironment.texture[texture].width/2),
	                         y_pos-(ZoneEnvironment.texture[texture].height/2),texture,
	                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	if (ZoneEnvironment.texture[texture].contains_collision_box == true) {
		CollisionMap.push_back(sCollisionMap(x_pos-(
		                                         ZoneEnvironment.texture[texture].width/2)+
		                                     ZoneEnvironment.texture[texture].collision_box.x,
		                                     y_pos-(ZoneEnvironment.texture[texture].height/2)+
		                                     ZoneEnvironment.texture[texture].collision_box.y,
		                                     ZoneEnvironment.texture[texture].collision_box.h,
		                                     ZoneEnvironment.texture[texture].collision_box.w));
	}
}

void CZone::AddShadow(int x_pos, int y_pos, int texture)
{
	// the old shadowmap here, keeping it a while... ShadowMap.push_back(sShadowMap(x_pos-(ZoneShadow.texture[texture].width/2),y_pos-(ZoneShadow.texture[texture].height/2),texture, 1.0f, 1.0f, 1.0f, 1.0f));
	ShadowMap.push_back(sEnvironmentMap(x_pos-(ZoneShadow.texture[texture].width/2),
	                                    y_pos-(ZoneShadow.texture[texture].height/2),texture, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
}

void CZone::AddCollisionbox(int x_pos, int y_pos)
{
	CollisionMap.push_back(sCollisionMap(x_pos,y_pos,100,100));
}

int CZone::DeleteEnvironment(int x, int y)
{
	for (unsigned int t=0;t<EnvironmentMap.size();t++) {
		if ((EnvironmentMap[t].x_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].width > x) &&
		        (EnvironmentMap[t].x_pos < x)) {
			if ((EnvironmentMap[t].y_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].height > y) &&
			        (EnvironmentMap[t].y_pos < y)) {
				EnvironmentMap.erase(EnvironmentMap.begin()+t);
				return 0;
			}
		}
	}
	return 1;
}

int CZone::LocateEnvironment(int x, int y)
{
	for (unsigned int t=0;t<EnvironmentMap.size();t++) {
		if ((EnvironmentMap[t].x_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].width > x) &&
		        (EnvironmentMap[t].x_pos < x)) {
			if ((EnvironmentMap[t].y_pos+ZoneEnvironment.texture[EnvironmentMap[t].id].height > y) &&
			        (EnvironmentMap[t].y_pos < y)) {
				return t;
			}
		}
	}
	return -1;
}

int CZone::LocateShadow(int x, int y)
{
	for (unsigned int t=0;t<ShadowMap.size();t++) {
		if ((ShadowMap[t].x_pos+ZoneShadow.texture[ShadowMap[t].id].width > x) &&
		        (ShadowMap[t].x_pos < x)) {
			if ((ShadowMap[t].y_pos+ZoneShadow.texture[ShadowMap[t].id].height > y) &&
			        (ShadowMap[t].y_pos < y)) {
				return t;
			}
		}
	}
	return -1;
}

int CZone::DeleteShadow(int x, int y)
{
	for (unsigned int t=0;t<ShadowMap.size();t++) {
		if ((ShadowMap[t].x_pos+ZoneShadow.texture[ShadowMap[t].id].width > x) &&
		        (ShadowMap[t].x_pos < x)) {
			if ((ShadowMap[t].y_pos+ZoneShadow.texture[ShadowMap[t].id].height > y) &&
			        (ShadowMap[t].y_pos < y)) {
				ShadowMap.erase(ShadowMap.begin()+t);
				return 0;
			}
		}
	}
	return 1;
}

int CZone::LocateCollisionbox(int x, int y)
{
	for (unsigned int t=0;t<CollisionMap.size();t++) {
		if ((CollisionMap[t].CR.x+CollisionMap[t].CR.w > x) && (CollisionMap[t].CR.x < x)) {
			if ((CollisionMap[t].CR.y+CollisionMap[t].CR.h > y) && (CollisionMap[t].CR.y < y)) {
				return t;
			}
		}
	}
	return -1;
}


int CZone::DeleteCollisionbox(int x, int y)
{
	for (unsigned int t=0;t<CollisionMap.size();t++) {
		if ((CollisionMap[t].CR.x+CollisionMap[t].CR.w > x) && (CollisionMap[t].CR.x < x)) {
			if ((CollisionMap[t].CR.y+CollisionMap[t].CR.h > y) && (CollisionMap[t].CR.y < y)) {
				CollisionMap.erase(CollisionMap.begin()+t);
				return 0;
			}
		}
	}
	return -1;
}
