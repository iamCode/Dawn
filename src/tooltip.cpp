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

#include "tooltip.h"
#include "GLFT_Font.h"
#include "CDrawingHelpers.h"
#include "TimeConverterHelper.h"
#include "CCharacter.h"
#include "Player.h"
#include "StatsSystem.h"
#include "elements.h"
#include <memory>

itemTooltip::itemTooltip( Item *parent_, Player *player_ )
            :   parent( parent_ )
{
    player = player_;
    height = 0;
    width = 0;
    blockWidth = 32;
    blockHeight = 32;
    blockNumberWidth = 1;
    blockNumberHeight = 1;
    smallTooltip = false;
    loadTextures();
    getParentText();
}

spellTooltip::spellTooltip(CSpellActionBase *parent_, Player *player_ )
            :   parent( parent_ )
{
    player = player_;
    height = 0;
    width = 0;
    blockWidth = 32;
    blockHeight = 32;
    smallTooltip = false;
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

void Tooltip::enableSmallTooltip()
{
    smallTooltip = true;
}

void Tooltip::disableSmallTooltip()
{
    smallTooltip = false;
}

bool Tooltip::isTooltipSmall()
{
    return smallTooltip;
}

void Tooltip::loadTextures()
{
	Frames::initFrameTextures();
}

void Tooltip::reloadTooltip()
{
    loadedAtLevel = player->getLevel();
    tooltipText.clear();
    getParentText();
}

void itemTooltip::draw( int x, int y )
{
    if ( tooltipText.empty() )
    {
        return;
    }

    // check to see if the player's level is the same since he loaded the parentText to the tooltip.
    // if not, we clear the tooltip and get the parent text again.
    if ( loadedAtLevel != player->getLevel() )
    {
        reloadTooltip();
    }

    // we also check to see if the bound spell has changed the displayed cooldown.
    if ( parent->getSpell() != NULL )
    {
        if ( player->isSpellOnCooldown( parent->getSpell()->getName()) == true || !currentCooldownText.empty() )
        {
            if ( currentCooldownText != TimeConverter::convertTime( player->getTicksOnCooldownSpell( parent->getSpell()->getName() ), parent->getSpell()->getCooldown() ) )
            {
                reloadTooltip();
            }
        }
    }

    // make sure the tooltip doesnt go "off screen"
    if ( x + (blockNumberWidth + 2) * blockWidth > dawn_configuration::screenWidth )
    {
        x = dawn_configuration::screenWidth - (blockNumberWidth + 2) * blockWidth;
    }

    if ( y + (blockNumberHeight + 2) * blockHeight > dawn_configuration::screenHeight )
    {
        y = dawn_configuration::screenHeight - (blockNumberHeight + 2) * blockHeight;
    }

    // set the correct position based on where we are
    x += world_x;
    y += world_y;

	// set the first font Y-position on the top of the first tooltip block excluding topborder
    // (we could also center the text in the tooltip, but topaligned is probably bestlooking
    int font_y = y + blockHeight + (blockNumberHeight) * blockHeight - toplineHeight;

    Frames::drawFrame( x, y, blockNumberWidth, blockNumberHeight, blockWidth, blockHeight );

    // loop through the text vector and print all the text.
    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {
        glColor4fv(tooltipText[i].color);
        tooltipText[i].font->drawText(x+blockWidth,font_y,tooltipText[i].text);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        font_y -= tooltipText[i].font->getHeight()+19;
    }
}

void spellTooltip::draw( int x, int y )
{
    if ( tooltipText.empty() )
    {
        return;
    }

    // check to see if the player's level is the same since he loaded the parentText to the tooltip.
    // if not, we clear the tooltip and get the parent text again.
    if ( loadedAtLevel != player->getLevel() )
    {
        reloadTooltip();
    }

    // make sure the tooltip doesnt go "off screen"
    if ( x + (blockNumberWidth + 2) * blockWidth > dawn_configuration::screenWidth )
    {
        x = dawn_configuration::screenWidth - (blockNumberWidth + 2) * blockWidth;
    }

    if ( y + (blockNumberHeight + 2) * blockHeight > dawn_configuration::screenHeight )
    {
        y = dawn_configuration::screenHeight - (blockNumberHeight + 2) * blockHeight;
    }

    // set the correct position based on where we are
    x += world_x;
    y += world_y;

	// set the first font Y-position on the top of the first tooltip block excluding topborder
    // (we could also center the text in the tooltip, but topaligned is probably bestlooking
    int font_y = y + blockHeight + (blockNumberHeight) * blockHeight - toplineHeight;

    Frames::drawFrame( x, y, blockNumberWidth, blockNumberHeight, blockWidth, blockHeight );

    // loop through the text vector and print all the text.
    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {
        glColor4fv(tooltipText[i].color);
        tooltipText[i].font->drawText(x+blockWidth,font_y,tooltipText[i].text);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        font_y -= tooltipText[i].font->getHeight()+19;
    }
}

void Tooltip::drawSmallTooltip( int x, int y )
{
    if ( tooltipText.empty() )
    {
        return;
    }

    height = tooltipText[0].font->getHeight()+9;
    width = tooltipText[0].font->calcStringWidth( tooltipText[0].text );

    // make sure the tooltip doesnt go "off screen"
    if ( width + x + 32 > dawn_configuration::screenWidth )
    {
        x = dawn_configuration::screenWidth - width - 32;
    }

    if ( height + y + 32 > dawn_configuration::screenHeight )
    {
        y = dawn_configuration::screenHeight - height - 32;
    }

    // set the first font Y-position on the top of the tooltip.
    int font_y = y + world_y + height - 16;

    // set the correct position based on where we are
    x += world_x;
    y += world_y;

    // draw the corners
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture, x, 16, y, 16); // lower left corner
    DrawingHelpers::mapTextureToRect( textures.texture[1].texture, x+width+16, 16, y, 16); // lower right corner
    DrawingHelpers::mapTextureToRect( textures.texture[2].texture, x, 16, y+16, 16); // upper left corner
    DrawingHelpers::mapTextureToRect( textures.texture[3].texture, x+width+16, 16, y+16, 16); // upper right corner

    // draw the borders
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x+16,width,y,16); // bottom border
    DrawingHelpers::mapTextureToRect( textures.texture[4].texture, x+16,width,y+16,16); // top border

    // draw the name of the tooltip, since it's a small tooltip.
    glColor4fv(tooltipText[0].color);
    tooltipText[0].font->drawText(x+15,font_y,tooltipText[0].text);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void Tooltip::addTooltipText(GLfloat color[], uint8_t fontSize, std::string str, ...)
{
    std::va_list args;
	char buf[1024];

	va_start(args,str);
	vsnprintf(buf, 1024, str.c_str(), args);
	va_end(args);

    // push the data to the vector.
    tooltipText.push_back(sTooltipText(buf, color, fontSize));

    // adjust width and height depending on the content of the tooltip.
    width = 0;
    int newHeight = 0;
    toplineHeight = 0;
	if ( tooltipText.size() > 0 ) {
		toplineHeight = tooltipText[0].font->getHeight();
	}

    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {
    	int neededWidth = tooltipText[i].font->calcStringWidth(tooltipText[i].text);
        if ( width < neededWidth ) {
            width = neededWidth;
        }
        // add line and line distance
        newHeight += tooltipText[i].font->getHeight();
        if ( i+1 < tooltipText.size() ) {
        	newHeight += 19;
        }
    }
    height = newHeight;

    blockNumberHeight = ceil( static_cast<double>(height) / blockHeight );
    blockNumberWidth = ceil( static_cast<double>(width) / blockWidth );
}

void itemTooltip::addTooltipTextForPercentageAttribute( std::string attributeName, double attributePercentage )
{
	GLfloat red[] = { 1.0f, 0.0f, 0.0f };
	GLfloat green[] = { 0.0f, 1.0f, 0.0f };
	if ( attributePercentage > 0 ) {
		addTooltipText( green, 12, "+%.2f%% %s", attributePercentage, attributeName.c_str() );
	} else {
		addTooltipText( red, 12, "%.2f%% %s", attributePercentage, attributeName.c_str() );
	}
}

void itemTooltip::getParentText()
{
    // remember what level we generated this tooltip
    loadedAtLevel = player->getLevel();

    GLfloat grey[] = { 0.5f, 0.5f, 0.5f };
    GLfloat white[] = { 1.0f, 1.0f, 1.0f };
    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
    GLfloat orange[] = { 1.0f, 0.5f, 0.0f };
    GLfloat red[] = { 1.0f, 0.0f, 0.0f };
    GLfloat green[] = { 0.0f, 1.0f, 0.0f };
    GLfloat brownish[] = { 0.7f, 0.7f, 0.0f };
    std::string attribute_string[] = { "armor", "dexterity", "intellect", "strength", "vitality", "wisdom", "health", "mana" };
    int8_t attribute_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // setting the title of the tooltip based on item quality
    switch ( parent->getItemQuality() )
    {
        case ItemQuality::POOR:
            addTooltipText( grey, 14, parent->getName() );
        break;
        case ItemQuality::NORMAL:
            addTooltipText( white, 14, parent->getName() );
        break;
        case ItemQuality::ENHANCED:
            addTooltipText( yellow, 14, parent->getName() );
        break;
        case ItemQuality::RARE:
            addTooltipText( orange, 14, parent->getName() );
        break;
        case ItemQuality::LORE:
            addTooltipText( red, 14, parent->getName() );
        break;
    }

    // add an extra linefeed after the title
    addTooltipText( white, 14, "" );

    // displaying which type of item it is.
    switch ( parent->getItemType() )
    {
        case ItemType::QUESTITEM:
            addTooltipText( white, 12, "Quest item" );
        break;
        case ItemType::MISCELLANEOUS:
            // nothing here so far...
        break;
        case ItemType::ARMOR:
            addTooltipText( white, 12, parent->getArmorTypeText() );
        break;
        case ItemType::WEAPON:
            addTooltipText( white, 12, parent->getWeaponTypeText() );
        break;
        case ItemType::JEWELRY:
            // nothing here so far...
        break;
        case ItemType::DRINK:
            // nothing here so far...
        break;
        case ItemType::FOOD:
            // nothing here so far...
        break;
        case ItemType::POTION:
            addTooltipText( white, 12, "Potion" );
        break;
        case ItemType::SCROLL:
            addTooltipText( white, 12, "Scroll" );
        break;
        case ItemType::NEWSPELL:
            // nothing here so far...
        break;
        case ItemType::COUNT:
            dawn_debug_fatal("ItemType::COUNT found in getParentText(). This should not be.");
            abort();
        break;
    }

    // displaying where the item fits.
    if ( parent->getEquipPosition() != EquipPosition::NONE )
    {
        addTooltipText( white, 12, parent->getEquipPositionText() );
    }

    // displaying damage if it's a weapon.
    if ( parent->getItemType() == ItemType::WEAPON && parent->getWeaponType() != WeaponType::SHIELD )
    {
        addTooltipText( white, 12, "Damage: %d-%d", parent->getMinDamage(),parent->getMaxDamage() );
    }

    // display stats given from the item
    attribute_values[0] = parent->getStats( StatsType::Armor );
    attribute_values[1] = parent->getStats( StatsType::Dexterity );
    attribute_values[2] = parent->getStats( StatsType::Intellect );
    attribute_values[3] = parent->getStats( StatsType::Strength );
    attribute_values[4] = parent->getStats( StatsType::Vitality );
    attribute_values[5] = parent->getStats( StatsType::Wisdom );
    attribute_values[6] = parent->getStats( StatsType::Health );
    attribute_values[7] = parent->getStats( StatsType::Mana );

    for (unsigned int i = 0; i < 8; i++ )
    {
        if ( attribute_values[i] != 0 )
        {
            std::string input;
            if ( attribute_values[i] > 0 )
            {
                addTooltipText( green, 12, "+%d %s", attribute_values[i], attribute_string[i].c_str() );
            } else {
                addTooltipText( red, 12, "%d %s", attribute_values[i], attribute_string[i].c_str() );
            }
        }
    }

	int16_t damageModifier = parent->getStats( StatsType::DamageModifier );
	if ( damageModifier != 0 ) {
		double damageBonus = (StatsSystem::getStatsSystem()->complexGetDamageModifier( player->getLevel(), damageModifier, player->getLevel() ) - 1) * 100;
		addTooltipTextForPercentageAttribute( "damage bonus", damageBonus );
	}

	int16_t hitModifier = parent->getStats( StatsType::HitModifier );
	if ( hitModifier != 0 ) {
		double hitBonus = (StatsSystem::getStatsSystem()->complexGetHitChance( player->getLevel(), hitModifier, player->getLevel() )) * 100;
		addTooltipTextForPercentageAttribute( "chance to hit", hitBonus );
	}

	int16_t evadeModifier = parent->getStats( StatsType::EvadeModifier );
	if ( evadeModifier != 0 ) {
		double evadeBonus = (StatsSystem::getStatsSystem()->complexGetEvadeChance( player->getLevel(), evadeModifier, player->getLevel() )) * 100;
		addTooltipTextForPercentageAttribute( "chance to evade", evadeBonus );
	}

	int16_t blockModifier = parent->getStats( StatsType::BlockModifier );
	if ( blockModifier != 0 ) {
		double blockBonus = (StatsSystem::getStatsSystem()->complexGetEvadeChance( player->getLevel(), blockModifier, player->getLevel() )) * 100;
		addTooltipTextForPercentageAttribute( "chance to block", blockBonus );
	}

	int16_t meleeCriticalModifier = parent->getStats( StatsType::MeleeCritical );
	if ( meleeCriticalModifier != 0 ) {
		double meleeCriticalBonus = (StatsSystem::getStatsSystem()->complexGetMeleeCriticalStrikeChance( player->getLevel(), meleeCriticalModifier, player->getLevel() )) * 100;
		addTooltipTextForPercentageAttribute( "melee critical chance", meleeCriticalBonus );
	}

	for ( size_t curElement=0; curElement< static_cast<size_t>(ElementType::Count); ++curElement ) {
		ElementType::ElementType curElementType = static_cast<ElementType::ElementType>( curElement );
		int16_t resistElementModifierPoints = parent->getResistElementModifierPoints( curElementType ) + parent->getStats( StatsType::ResistAll );
		if ( resistElementModifierPoints != 0 ) {
			double resistBonus = (StatsSystem::getStatsSystem()->complexGetResistElementChance( player->getLevel(), resistElementModifierPoints, player->getLevel() )) * 100;
			addTooltipTextForPercentageAttribute( std::string("resist ").append(ElementType::getElementNameLowercase(curElementType)), resistBonus );
		}
	}

	for ( size_t curElement=0; curElement< static_cast<size_t>(ElementType::Count); ++curElement ) {
		ElementType::ElementType curElementType = static_cast<ElementType::ElementType>( curElement );
		int16_t spellEffectElementModifierPoints = parent->getSpellEffectElementModifierPoints( curElementType ) + parent->getStats( StatsType::SpellEffectAll );
		if ( spellEffectElementModifierPoints != 0 ) {
			double spellEffectBonus = (StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), spellEffectElementModifierPoints, player->getLevel() ) - 1.00) * 100;
			addTooltipTextForPercentageAttribute( ElementType::getElementNameLowercase(curElementType).append(" magic effect"), spellEffectBonus );
		}
	}

	int16_t spellCriticalModifier = parent->getStats( StatsType::SpellCritical );
	if ( spellCriticalModifier != 0 ) {
		double spellCriticalBonus = (StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( player->getLevel(), spellCriticalModifier, player->getLevel() )) * 100;
		addTooltipTextForPercentageAttribute( "spell critical chance", spellCriticalBonus );
	}

	// if the item is useable, display it here and what effect it has.
	if ( parent->isUseable() )
	{
	    addTooltipText( green, 11, parent->getUseableDescription() );
	    addTooltipText( white, 11, "Charges: %d", parent->getSpellCharges() );
	    if ( parent->getSpell() != NULL )
	    {
	        if ( player->isSpellOnCooldown( parent->getSpell()->getName()) == true )
            {
                currentCooldownText = TimeConverter::convertTime( player->getTicksOnCooldownSpell( parent->getSpell()->getName() ), parent->getSpell()->getCooldown() );
                addTooltipText( red, 11, "Cooldown: %s", currentCooldownText.c_str() );
            }
	    }
	}

    // display the item description, if any
    if ( !parent->getDescription().empty() )
    {
        addTooltipText( brownish, 10, parent->getDescription() );
    }

    // display item level requirements if player's level is too low.
    if ( parent->getLevelReq() > player->getLevel() )
    {
        addTooltipText( red, 12, "Requires level %d", parent->getLevelReq() );
    }
}

void spellTooltip::getParentText()
{
    // remember what level we generated this tooltip
    loadedAtLevel = player->getLevel();

    GLfloat white[] = { 1.0f, 1.0f, 1.0f };
    GLfloat blue[] = { 0.3f, 0.3f, 1.0f };

    // name of the spell
    addTooltipText( white, 14, parent->getName() );
    addTooltipText( white, 12, "" );

    // display healing (direct and healing over time,
    //damage, damagetype (direct damage, damage over time) and damageschool (physical, fire, etc..)
    // not added yet.

    // display mana-cost
    addTooltipText( blue, 12, "Mana: %d", parent->getManaCost() );

    // display duration
//    addTooltipText( blue, 12, "Duration: %d", parent->getDuration() );

    if ( parent->getCooldown() > 0 )
    {
        addTooltipText( white, 12, "Cooldown: %s", TimeConverter::convertTime( parent->getCooldown() ).c_str() );
    }

    // display cast time
    if ( parent->getCastTime() == 0 )
    {
        addTooltipText( white, 12, "Casttime: Instant");
    } else {
        addTooltipText( white, 12, "Casttime: %.2f sec",static_cast<float>( parent->getCastTime() ) / 1000 );
    }

    // display description. This shouldnt say "does x amount of damage" but more of a general description.
    addTooltipText( white, 12, "" ); // newline
    addTooltipText( white, 12, parent->getInfo() );
}

/// FRAMES

std::auto_ptr<CTexture> frameTextures( NULL );

namespace Frames
{

	void initFrameTextures()
	{
		if ( frameTextures.get() != NULL ) {
			return;
		}

		frameTextures = std::auto_ptr<CTexture>(new CTexture());
		frameTextures->texture.reserve( 9 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower_left2.tga", 0 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower_right2.tga", 1 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper_left2.tga", 2 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper_right2.tga", 3 );
		frameTextures->LoadIMG( "data/interface/tooltip/background2.tga", 4 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper2.tga", 5 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower2.tga", 6 );
		frameTextures->LoadIMG( "data/interface/tooltip/left2.tga", 7 );
		frameTextures->LoadIMG( "data/interface/tooltip/right2.tga", 8 );

	}

	void drawFrame( int leftX, int bottomY, int numBlocksX, int numBlocksY, int blockWidth, int blockHeight )
	{
		// draw the corners
		DrawingHelpers::mapTextureToRect( frameTextures->texture[0].texture, leftX, blockWidth, bottomY, blockHeight); // lower left corner
		DrawingHelpers::mapTextureToRect( frameTextures->texture[1].texture, leftX+blockWidth+(numBlocksX*blockWidth), blockWidth, bottomY, blockHeight); // lower right corner
		DrawingHelpers::mapTextureToRect( frameTextures->texture[2].texture, leftX, blockWidth, bottomY+blockHeight+(numBlocksY*blockHeight), blockHeight); // upper left corner
		DrawingHelpers::mapTextureToRect( frameTextures->texture[3].texture, leftX+blockWidth+(numBlocksX*blockWidth), blockWidth, bottomY+blockHeight+(numBlocksY*blockHeight), blockHeight); // upper right corner

		// draw the top and bottom borders
		for ( int blockX = 0; blockX < numBlocksX; blockX++ )
		{
			DrawingHelpers::mapTextureToRect( frameTextures->texture[5].texture, leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY+blockHeight+(numBlocksY*blockHeight),blockHeight); // top border
			DrawingHelpers::mapTextureToRect( frameTextures->texture[6].texture, leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY,blockHeight); // bottom border
		}

		// draw the right and left borders
		for ( int blockY = 0; blockY < numBlocksY; blockY++ )
		{
			DrawingHelpers::mapTextureToRect( frameTextures->texture[7].texture, leftX,blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight); // left border
			DrawingHelpers::mapTextureToRect( frameTextures->texture[8].texture, leftX+blockWidth+(numBlocksX*blockWidth),blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight); // right border
		}

		// draw the background
		for ( int blockY = 0; blockY < numBlocksY; blockY++ )
		{
			for ( int blockX = 0; blockX < numBlocksX; blockX++ )
			{
				DrawingHelpers::mapTextureToRect( frameTextures->texture[4].texture, leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight);
			}
		}
	}
} // namespace Frames


