#include "CCharacter.h"

void CCharacter::Draw() {
    glBindTexture( GL_TEXTURE_2D, texture.texture[1].texture);
    glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x_pos, y_pos, 0.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x_pos+texture.texture[1].width, y_pos, 0.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x_pos+texture.texture[1].width, y_pos+texture.texture[1].height, 0.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x_pos, y_pos+texture.texture[1].height, 0.0f );
    glEnd();
};

int LocateTilex(int x_pos, int y_pos) {
    for (unsigned int t=0;t<zone1.CollisionMap.size();t++) {
        if ((zone1.CollisionMap[t].CR.x+zone1.CollisionMap[t].CR.w >= x_pos) && (zone1.CollisionMap[t].CR.x <= x_pos)) {
            if ((zone1.CollisionMap[t].CR.y+zone1.CollisionMap[t].CR.h >= y_pos) && (zone1.CollisionMap[t].CR.y <= y_pos)) {
                return 1;
            }
        }
    }
    return 0;
}

int CCharacter::CollisionCheck(int direction) {
    /** directions:
      8-1-2
      7-X-3
      6-5-4 **/

    switch (direction) {
        case 1:
        // check upper left corner
        if (LocateTilex(x_pos,y_pos-1) == 1) {
            return 1;
        }
        // check upper right corner
        if (LocateTilex(x_pos+40,y_pos-1) == 1) {
            return 1;
        }
        break;

        case 3:
        // check upper right corner
        if (LocateTilex(x_pos+41,y_pos) == 1) {
            return 1;
        }
        // check lower right corner
        if (LocateTilex(x_pos+41,y_pos+40) == 1) {
            return 1;
        }
        break;

        case 5:
        // check lower left corner
        if (LocateTilex(x_pos,y_pos+41) == 1) {
            return 1;
        }
        // check lower right corner
        if (LocateTilex(x_pos+40,y_pos+41) == 1) {
            return 1;
        }
        break;

        case 7:
        // check upper left corner
        if (LocateTilex(x_pos-1,y_pos) == 1) {
            return 1;
        }
        // check lower left corner
        if (LocateTilex(x_pos-1,y_pos+40) == 1) {
            return 1;
        }
        break;
    }
    return 0;
};

void CCharacter::MoveUp() {
    if (CollisionCheck(1) == 0) {
        world_y--;
        y_pos--;
    }
};

void CCharacter::MoveDown() {
    if (CollisionCheck(5) == 0) {
        world_y++;
        y_pos++;
    }
};

void CCharacter::MoveLeft() {
    if (CollisionCheck(7) == 0) {
        world_x--;
        x_pos--;
    }
};

void CCharacter::MoveRight() {
    if (CollisionCheck(3) == 0) {
        world_x++;
        x_pos++;
    }
};
