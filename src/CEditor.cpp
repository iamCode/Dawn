#include "CEditor.h"

void CEditor::inc_tilepos() {
    switch (current_object) {
        case 0: // tiles
            if (current_tilepos < zone1.ZoneTiles.NumberOfTextures) {
                current_tilepos++;
                tilepos_offset--;
            }
            break;
        case 1: // environment
            if (current_tilepos < zone1.ZoneEnvironment.NumberOfTextures) {
                current_tilepos++;
                tilepos_offset--;
            }
            break;
        case 2: // shadows
            if (current_tilepos < zone1.ZoneShadow.NumberOfTextures) {
                current_tilepos++;
                tilepos_offset--;
            }
            break;
        case 3: // collisionboxes
            break;
    }
}

void CEditor::dec_tilepos() {
    if (current_tilepos > 1) {
        current_tilepos--;
        tilepos_offset++;
    }
}

int CEditor::SaveZone() {
    FILE *fp;
    int x_pos, y_pos;
    // open the tilemap-file, so we can write our new mapfile ;D ///////////////////////////
    if ((fp=fopen("zone1.tilemap", "w")) == NULL) {
        printf("ERROR opening file zone1.tilemap\n\n");
        return -1;
    }
    fprintf(fp,"#x-pos y-pos tile-id");

    for (int x=-25;x<=25;x++) {
        for (int y=-25;y<=25;y++) {
            x_pos = x*40;
            y_pos = y*40;
            fprintf(fp,"\n%d %d %d",x_pos,y_pos,zone1.LocateTexture(x_pos,y_pos));
        }
    }

    fclose(fp);
    /////////////////////////////////////////////////////////////////////////////////////

    // open the environmentmap-file, so we can write our trees and stuff...
    if ((fp=fopen("zone1.environmentmap", "w")) == NULL) {
        printf("ERROR opening file zone1.environmentmap\n\n");
        return -1;
    }
    fprintf(fp,"#x-pos y-pos tile-id");


    for (unsigned int x=0;x<zone1.EnvironmentMap.size();x++) {
        fprintf(fp,"\n%d %d %d",zone1.EnvironmentMap[x].x_pos,zone1.EnvironmentMap[x].y_pos, zone1.EnvironmentMap[x].id);
    }
    fclose(fp);
    ////////////////////////////////////////////////////////////////////////


    // open the shadowmap-file, so we can save our shadow...
    if ((fp=fopen("zone1.shadowmap", "w")) == NULL) {
        printf("ERROR opening file zone1.shadowmap\n\n");
        return -1;
    }
    fprintf(fp,"#x-pos y-pos tile-id");

    for (unsigned int x=0;x<zone1.ShadowMap.size();x++) {
        fprintf(fp,"\n%d %d %d",zone1.ShadowMap[x].x_pos,zone1.ShadowMap[x].y_pos, zone1.ShadowMap[x].id);
    }
    fclose(fp);
    /////////////////////////////////////////////////////////
    return 0;
};

void CEditor::HandleKeys() {
    Uint8 *keys;
    keys = SDL_GetKeyState(NULL);
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)  { done = 1; }

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) { done = 1; }
            if (event.key.keysym.sym == SDLK_SPACE) { }
        }

        // scroll to choose a higher/lower tile
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            switch (event.button.button) {
                case 1: // mouse button 1, see if we can select an object being pointed at.
                switch (current_object) {
                    case 1: // environment
                    objectedit_selected = zone1.LocateEnvironment(world_x+mouseX,world_y+mouseY);
                    break;
                    case 2: // shadows
                    //objectedit_selected = zone1.LocateShadow(world_x+mouseX,world_y+mouseY);
                    break;
                    case 3: // collisionboxes
                    break;
                }
                break;

                case 4: // scroll up, increase our tileposition
                inc_tilepos();
                break;

                case 5: // scroll down, decrease our tileposition
                dec_tilepos();
                break;
            }
        }

        if (event.type == SDL_MOUSEMOTION) {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
    }

    if (keys[SDLK_DOWN]) { world_y += 3; }
    if (keys[SDLK_UP]) { world_y -= 3; }
    if (keys[SDLK_LEFT]) { world_x -= 3; }
    if (keys[SDLK_RIGHT]) { world_x += 3; }

    if (keys[SDLK_DELETE] && !KP_delete_environment) {
        KP_delete_environment = true;
        switch (current_object) {
            case 0: // tiles
                zone1.DeleteTile(zone1.LocateTile(world_x+mouseX,world_y+mouseY));
                break;
            case 1: // environment
                zone1.DeleteEnvironment(world_x+mouseX,world_y+mouseY);
                break;
            case 2: // shadows
                zone1.DeleteShadow(world_x+mouseX,world_y+mouseY);
                break;
            case 3: // collisionboxes
                break;
        }
    }

    if (!keys[SDLK_DELETE]) {
        KP_delete_environment = false;
    }

    if (keys[SDLK_KP_ENTER] && !KP_add_environment) {
        KP_add_environment = true;
        switch (current_object) {
            case 0: // tiles
                zone1.ChangeTile(zone1.LocateTile(world_x+mouseX,world_y+mouseY),current_tilepos);
                break;
            case 1: // environment
                zone1.AddEnvironment(world_x+mouseX,world_y+mouseY,current_tilepos);
                break;
            case 2: // shadows
                zone1.AddShadow(world_x+mouseX,world_y+mouseY,current_tilepos);
                break;
            case 3: // collisionboxes
                break;
        }
    }

    if (!keys[SDLK_KP_ENTER]) {
        KP_add_environment = false;
    }

    if (keys[SDLK_l] && !KP_toggle_editor) {
        enabled = false;
        KP_toggle_editor = true;
    }

    if (!keys[SDLK_l]) {
        KP_toggle_editor = false;
    }

    if (keys['.']) {
        zone1.EnvironmentMap[objectedit_selected].transparency -= 0.01f;
    }

    if (keys[SDLK_F1] && !KP_toggle_tileset) {
        current_tilepos = 1;
        tilepos_offset = 0;
        objectedit_selected = -1;
        KP_toggle_tileset = true;
        if (current_object < 2) {
            current_object++;
        } else {
            current_object = 0;
        }
    }

    if (!keys[SDLK_F1]) {
        KP_toggle_tileset = false;
    }

    if (keys[SDLK_s]) { SaveZone(); }
};

void CEditor::DrawEditor() {
    glEnable(GL_BLEND);
    if (objectedit_selected >= 0) { // we have selected an object to edit it's properties, show the edit-screen.
        switch (current_object) {
            case 1:
            DrawEditFrame(&zone1.ZoneEnvironment, zone1.EnvironmentMap[objectedit_selected].id);
            break;
            case 2:
            break;
            case 3:
            break;
        }
    }

    glBindTexture( GL_TEXTURE_2D, interfacetexture.texture[0].texture);
    glBegin( GL_QUADS );
        //Top-left vertex (corner)
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x, world_y, 0.0f );
        //Bottom-left vertex (corner)
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+RES_X, world_y, 0.0f );
        //Bottom-right vertex (corner)
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+RES_X, world_y+100, 0.0f );
        //Top-right vertex (corner)
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x, world_y+100, 0.0f );
    glEnd();

    glBindTexture( GL_TEXTURE_2D, interfacetexture.texture[1].texture);
    glBegin( GL_QUADS );
        //Top-left vertex (corner)
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-5, world_y+5, 0.0f );
        //Bottom-left vertex (corner)
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)+45, world_y+5, 0.0f );
        //Bottom-right vertex (corner)
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)+45, world_y+55, 0.0f );
        //Top-right vertex (corner)
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-5, world_y+55, 0.0f );
    glEnd();

    glBegin( GL_LINES );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(mouseX-20+world_x, mouseY+world_y, 0.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(mouseX+20+world_x, mouseY+world_y, 0.0f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(mouseX+world_x, mouseY+20+world_y, 0.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(mouseX+world_x, mouseY-20+world_y, 0.0f );
    glEnd();

    switch (current_object) {
        case 0:
            for (tilepos=1;tilepos<=zone1.ZoneTiles.NumberOfTextures;tilepos++) {
                glBindTexture( GL_TEXTURE_2D, zone1.ZoneTiles.texture[tilepos].texture);
                glBegin( GL_QUADS );
                    //Top-left vertex (corner)
                    glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-50+(tilepos*50)+(tilepos_offset*50), world_y+10, 0.0f );
                    //Bottom-left vertex (corner)
                    glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-10+(tilepos*50)+(tilepos_offset*50), world_y+10, 0.0f );
                    //Bottom-right vertex (corner)
                    glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-10+(tilepos*50)+(tilepos_offset*50), world_y+50, 0.0f );
                    //Top-right vertex (corner)
                    glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-50+(tilepos*50)+(tilepos_offset*50), world_y+50, 0.0f );
                glEnd();
            }

            break;

        case 1:
            for (tilepos=1;tilepos<=zone1.ZoneEnvironment.NumberOfTextures; tilepos++) {
                glBindTexture( GL_TEXTURE_2D, zone1.ZoneEnvironment.texture[tilepos].texture);
                glBegin( GL_QUADS );
                    //Top-left vertex (corner)
                    glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-50+(tilepos*50)+(tilepos_offset*50), world_y+10, 0.0f );
                    //Bottom-left vertex (corner)
                    glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-10+(tilepos*50)+(tilepos_offset*50), world_y+10, 0.0f );
                    //Bottom-right vertex (corner)
                    glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-10+(tilepos*50)+(tilepos_offset*50), world_y+50, 0.0f );
                    //Top-right vertex (corner)
                    glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-50+(tilepos*50)+(tilepos_offset*50), world_y+50, 0.0f );
                glEnd();
            }

            for (unsigned int x = 0; x < zone1.CollisionMap.size(); x++) {
                glBindTexture( GL_TEXTURE_2D, interfacetexture.texture[1].texture);
                glBegin( GL_QUADS );
                    //Top-left vertex (corner)
                    glTexCoord2f( 0.0f, 0.0f ); glVertex3f(zone1.CollisionMap[x].CR.x, zone1.CollisionMap[x].CR.y, 0.0f );
                    //Bottom-left vertex (corner)
                    glTexCoord2f( 1.0f, 0.0f ); glVertex3f(zone1.CollisionMap[x].CR.x+zone1.CollisionMap[x].CR.w, zone1.CollisionMap[x].CR.y, 0.0f );
                    //Bottom-right vertex (corner)
                    glTexCoord2f( 1.0f, 1.0f ); glVertex3f(zone1.CollisionMap[x].CR.x+zone1.CollisionMap[x].CR.w, zone1.CollisionMap[x].CR.y+zone1.CollisionMap[x].CR.h, 0.0f );
                    //Top-right vertex (corner)
                    glTexCoord2f( 0.0f, 1.0f ); glVertex3f(zone1.CollisionMap[x].CR.x, zone1.CollisionMap[x].CR.y+zone1.CollisionMap[x].CR.h, 0.0f );
                glEnd();
            }

            break;

        case 2:
            for (tilepos=1;tilepos<=zone1.ZoneShadow.NumberOfTextures; tilepos++) {
                glBindTexture( GL_TEXTURE_2D, zone1.ZoneShadow.texture[tilepos].texture);
                glBegin( GL_QUADS );
                    //Top-left vertex (corner)
                    glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-50+(tilepos*50)+(tilepos_offset*50), world_y+10, 0.0f );
                    //Bottom-left vertex (corner)
                    glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+(RES_X/2)-10+(tilepos*50)+(tilepos_offset*50), world_y+10, 0.0f );
                    //Bottom-right vertex (corner)
                    glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-10+(tilepos*50)+(tilepos_offset*50), world_y+50, 0.0f );
                    //Top-right vertex (corner)
                    glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x+(RES_X/2)-50+(tilepos*50)+(tilepos_offset*50), world_y+50, 0.0f );
                glEnd();
            }

            break;

        case 3:
            break;

    }
    glDisable(GL_BLEND);
};

void CEditor::LoadTextures() {
    interfacetexture.texture.reserve(4);
    interfacetexture.LoadIMG("data/background_editor.tga",0);
    interfacetexture.LoadIMG("data/current_tile_backdrop.tga",1);
    interfacetexture.LoadIMG("data/tile.tga",2);
    interfacetexture.LoadIMG("data/edit_backdrop.tga",3);
}

void CEditor::DrawEditFrame(CTexture *edit_object, int object_id) {
    glBindTexture( GL_TEXTURE_2D, interfacetexture.texture[3].texture);
        glBegin( GL_QUADS );
            //Top-left vertex (corner)
            glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x+50, world_y+(RES_Y/2), 0.0f );
            //Bottom-left vertex (corner)
            glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+interfacetexture.texture[3].width, world_y+(RES_Y/2), 0.0f );
            //Bottom-right vertex (corner)
            glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+interfacetexture.texture[3].width, world_y+(RES_Y/2)+interfacetexture.texture[3].height, 0.0f );
            //Top-right vertex (corner)
            glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x+50, world_y+(RES_Y/2)+interfacetexture.texture[3].height, 0.0f );
        glEnd();

        glBindTexture( GL_TEXTURE_2D, edit_object->texture[object_id].texture);
        glBegin( GL_QUADS );
            //Top-left vertex (corner)
            glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x+55, world_y+(RES_Y/2), 0.0f );
            //Bottom-left vertex (corner)
            glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+55+edit_object->texture[object_id].width, world_y+(RES_Y/2), 0.0f );
            //Bottom-right vertex (corner)
            glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+55+edit_object->texture[object_id].width, world_y+(RES_Y/2)+edit_object->texture[object_id].height, 0.0f );
            //Top-right vertex (corner)
            glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x+55, world_y+(RES_Y/2)+edit_object->texture[object_id].height, 0.0f );
        glEnd();
}
