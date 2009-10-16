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

#include "tooltip.h"
#include "GLFT_Font.h"
#include "CDrawingHelpers.h"

itemTooltip::itemTooltip(Item *parent_)
            : parent( parent_ )
{
    height = 0;
    width = 0;
    loadTextures();
    getParentText();
}

spellTooltip::spellTooltip(CSpellActionBase *parent_)
            : parent( parent_ )
{
    height = 0;
    width = 0;
    loadTextures();
    getParentText();
}

Tooltip::~Tooltip()
{
    for (unsigned int i = 0; i < tooltipText.size(); i++) {
        if ( tooltipText[i].font != NULL )
        {
            delete tooltipText[i].font;
        }
    }
}

void Tooltip::loadTextures()
{
    textures.texture.reserve( 5 );
    textures.LoadIMG( "data/interface/tooltip/lower_left.tga", 0 );
    textures.LoadIMG( "data/interface/tooltip/lower_right.tga", 1 );
    textures.LoadIMG( "data/interface/tooltip/upper_left.tga", 2 );
    textures.LoadIMG( "data/interface/tooltip/upper_right.tga", 3 );
    textures.LoadIMG( "data/interface/tooltip/background.tga", 4 );
}

void Tooltip::draw( int x, int y )
{
    // set the first font Y-position on the top of the tooltip.
    int font_y = y + world_y + height;

    // make sure the tooltip doesnt go "off screen"
    if ( width + x + 32 > dawn_configuration::screenWidth )
    {
        x = dawn_configuration::screenWidth - width - 32;
    }

    // set the correct position based on where we are
    x += world_x;
    y += world_y;

    // draw the corners
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture, x, 16, y, 16); // lower left corner
    DrawingHelpers::mapTextureToRect( textures.texture[1].texture, x+width+16, 16, y, 16); // lower right corner
    DrawingHelpers::mapTextureToRect( textures.texture[2].texture, x, 16, y+height+16, 16); // upper left corner
    DrawingHelpers::mapTextureToRect( textures.texture[3].texture, x+width+16, 16, y+height+16, 16); // upper right corner

    // draw the borders
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x,16,y+16,height); // left border
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x+width+16,16,y+16,height); // right border
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x+16,width,y,16); // bottom border
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x+16,width,y+height+16,16); // top border

    // draw the background
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x+16,width,y+16,height);

    // loop through the text vector and print all the text.
    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {
        glColor4fv(tooltipText[i].color);
        tooltipText[i].font->drawText(x+15,font_y,tooltipText[i].text);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        font_y -= tooltipText[i].font->getHeight()+10;
    }
}

void Tooltip::addTooltipText(std::string text, GLfloat color[], uint8_t fontSize)
{
    // push the data to the vector.
    tooltipText.push_back(sTooltipText(text, color, fontSize));

    // adjust width and height depending on the content of the tooltip.
    int newHeight = 0;
    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {
        if ( width < tooltipText[i].font->calcStringWidth(tooltipText[i].text) ) {
            width = tooltipText[i].font->calcStringWidth(tooltipText[i].text);
        }
        newHeight += tooltipText[i].font->getHeight()+10;
    }

    height = newHeight;
}

void itemTooltip::getParentText()
{
    GLfloat grey[] = { 0.5f, 0.5f, 0.5f };
    GLfloat white[] = { 1.0f, 1.0f, 1.0f };
    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
    GLfloat orange[] = { 1.0f, 0.5f, 0.0f };
    GLfloat red[] = { 1.0f, 0.0f, 0.0f };
    GLfloat green[] = { 0.0f, 1.0f, 0.0f };
    GLfloat brownish[] = { 0.7f, 0.7f, 0.0f };
    std::string attribute_string[] = { "armor", "dexterity", "intellect", "strength", "vitality", "wisdom", "health", "mana", "energy" };
    int8_t attribute_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // setting the title of the tooltip based on item quality
    switch ( parent->getItemQuality() )
    {
        case ItemQuality::POOR:
            addTooltipText(parent->getName(), grey, 14);
        break;
        case ItemQuality::NORMAL:
            addTooltipText(parent->getName(), white, 14);
        break;
        case ItemQuality::ENHANCED:
            addTooltipText(parent->getName(), yellow, 14);
        break;
        case ItemQuality::RARE:
            addTooltipText(parent->getName(), orange, 14);
        break;
        case ItemQuality::LORE:
            addTooltipText(parent->getName(), red, 14);
        break;
    }

    // add an extra linefeed after the title
    addTooltipText("", white, 14);

    // displaying which type of item it is.
    switch ( parent->getItemType() )
    {
        case ItemType::QUESTITEM:
            addTooltipText( "Quest item", white, 12 );
        break;
        case ItemType::MISCELLANEOUS:
            // nothing here so far...
        break;
        case ItemType::ARMOR:
            addTooltipText( parent->getArmorTypeText(), white, 12 );
        break;
        case ItemType::WEAPON:
            addTooltipText( parent->getWeaponTypeText(), white, 12 );
        break;
    }

    // displaying where the item fits.
    if ( parent->getEquipPosition() != EquipPosition::NONE )
    {
        addTooltipText( parent->getEquipPositionText(), white, 12 );
    }

    // displaying damage if it's a weapon.
    if ( parent->getItemType() == ItemType::WEAPON && parent->getWeaponType() != WeaponType::SHIELD )
    {
        std::string input;
        char tempchar[200];
        sprintf(tempchar,"Damage: %d-%d",parent->getMinDamage(),parent->getMaxDamage());
        input.assign(tempchar);
        addTooltipText( input, white, 12 );
    }

    // display stats given from the item
    attribute_values[0] = parent->getArmor();
    attribute_values[1] = parent->getDexterity();
    attribute_values[2] = parent->getIntellect();
    attribute_values[3] = parent->getStrength();
    attribute_values[4] = parent->getVitality();
    attribute_values[5] = parent->getWisdom();
    attribute_values[6] = parent->getHealth();
    attribute_values[7] = parent->getMana();
    attribute_values[8] = parent->getEnergy();

    for (unsigned int i = 0; i < 9; i++ )
    {
        if ( attribute_values[i] != 0 )
        {
            std::string input;
            char tempchar[200];

            if ( attribute_values[i] > 0 )
            {
                sprintf(tempchar,"+%d %s",attribute_values[i],attribute_string[i].c_str());
                input.assign(tempchar);
                addTooltipText( input, green, 12 );
            } else {
                sprintf(tempchar,"%d %s",attribute_values[i],attribute_string[i].c_str());
                input.assign(tempchar);
                addTooltipText( input, red, 12 );
            }
        }
    }

    // display the item description, if any
    if ( !parent->getDescription().empty() )
    {
        addTooltipText( parent->getDescription(), brownish, 10 );
    }
}

void spellTooltip::getParentText()
{

}