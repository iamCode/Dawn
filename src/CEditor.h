#ifndef __C_EDITOR_
#define __C_EDITOR_

#include "CZone.h"
#include "CTexture.h"
#include <stdio.h>

extern int world_x, world_y, mouseX, mouseY, RES_X, RES_Y, done;
extern CZone zone1;

class CEditor {
    public:
    CEditor() { enabled = false; tilepos_offset = 0; tilepos = 1; current_tilepos = 1; current_object = 0; objectedit_selected = -1; };

    bool enabled, KP_toggle_editor;
    void DrawEditor();
    int SaveZone();
    void HandleKeys();
    void LoadTextures();

    private:
    void inc_tilepos();
    void dec_tilepos();
    void DrawEditFrame(CTexture *edit_object, int object_id);

    int tilepos_offset, tilepos, current_tilepos, current_object, objectedit_selected;
    bool KP_tile_dec, KP_tile_inc, KP_add_environment, KP_delete_environment, KP_toggle_tileset;

    CTexture interfacetexture;
};

#endif
