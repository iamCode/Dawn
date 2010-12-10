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
#include "shop.h"
#include "configuration.h"
#include <memory>

extern void formatMultilineText( std::string text, std::vector< std::string > &textLines, int lineWidth, GLFT_Font *font );

/// calculates how many bits that is being used in a bit field enumerator.
/// WeaponType::WeaponType for example.
size_t getNumBitsToUse( size_t maxBitValue )
{
    return log(maxBitValue) / log(2);
}

itemTooltip::itemTooltip( Item *parent_, Player *player_ )
            :   parent( parent_ )
{
    player = player_;
    blockWidth = 32;
    blockHeight = 32;
    blockNumberWidth = 1;
    blockNumberHeight = 1;
    smallTooltip = false;
    isShopItem = false;
    loadTextures();
    getParentText();
}

spellTooltip::spellTooltip(CSpellActionBase *parent_, Player *player_ )
            :   parent( parent_ )
{
    player = player_;
    blockWidth = 32;
    blockHeight = 32;
    smallTooltip = false;
    loadTextures();
    getParentText();
}

Tooltip::~Tooltip()
{
}

void Tooltip::updateBlockNumbers()
{
	if ( smallTooltip ) {
		curBlockNumberWidth = blockNumberWidthSmall;
		curBlockNumberHeight = blockNumberHeightSmall;
	} else {
		curBlockNumberWidth = blockNumberWidth;
		curBlockNumberHeight = blockNumberHeight;
	}
}

void Tooltip::enableSmallTooltip()
{
    smallTooltip = true;
    updateBlockNumbers();
}

void Tooltip::disableSmallTooltip()
{
    smallTooltip = false;
    updateBlockNumbers();
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
    getTicketFromPlayer();
    shoppingState = player->isShopping();
    tooltipText.clear();
    getParentText();
}

void itemTooltip::setShopItem( bool isShopItem_ )
{
    if ( isShopItem != isShopItem_ )
    {
        isShopItem = isShopItem_;
        reloadTooltip();
    }
}

int Tooltip::getTooltipWidth() const
{
    return blockWidth * curBlockNumberWidth + blockWidth;
}

int Tooltip::getTooltipHeight() const
{
    return blockHeight * curBlockNumberHeight + blockHeight;
}

void itemTooltip::getTicketFromPlayer()
{
    ticketFromPlayer = player->getTicketForItemTooltip();
}

void spellTooltip::getTicketFromPlayer()
{
    ticketFromPlayer = player->getTicketForSpellTooltip();
}

void itemTooltip::draw( int x, int y )
{
    if ( tooltipText.empty() )
    {
        return;
    }

    // check to see if the ticket we got from the player is the same ticket as the player is offering.
    // if not, we reload our tooltip.
    if ( ticketFromPlayer != player->getTicketForItemTooltip() )
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
    if ( x + (curBlockNumberWidth + 2) * blockWidth > Configuration::screenWidth )
    {
        x = Configuration::screenWidth - (curBlockNumberWidth + 2) * blockWidth;
    }

    if ( y + (curBlockNumberHeight + 2) * blockHeight > Configuration::screenHeight )
    {
        y = Configuration::screenHeight - (curBlockNumberHeight + 2) * blockHeight;
    }

    // set the correct position based on where we are
    x += world_x;
    y += world_y;

	// set the first font Y-position on the top of the first tooltip block excluding topborder
    // (we could also center the text in the tooltip, but topaligned is probably bestlooking
    int font_y = y + blockHeight + (curBlockNumberHeight) * blockHeight - toplineHeight;

    Frames::drawFrame( x, y, curBlockNumberWidth, curBlockNumberHeight, blockWidth, blockHeight );

    // loop through the text vector and print all the text.
    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {

        if ( tooltipText[i].text.find("price:") != tooltipText[i].text.npos )
        {
            drawCoinsLine( x+blockWidth, blockWidth*curBlockNumberWidth-10, font_y, &tooltipText[i] );
        } else {
            glColor4fv(tooltipText[i].color);
            tooltipText[i].font->drawText(x+blockWidth,font_y,tooltipText[i].text);
            glColor4f(1.0f,1.0f,1.0f,1.0f);
        }
        font_y -= tooltipText[i].font->getHeight()+11;
        if ( smallTooltip ) {
            break;
        }
    }
}

void itemTooltip::drawCoinsLine( int x, int frameWidth, int y, sTooltipText *tooltipText )
{
    std::string realString = tooltipText->text.substr(0,tooltipText->text.find_first_of(":")+1);

    int stringWidth = tooltipText->font->calcStringWidth( realString );
    int xoffset = 0;
    for ( size_t i = 0; i < 3; i++ )
    {
        if ( itemValue[i] != "0" )
        {
            Frames::drawCoin( x + frameWidth - xoffset, y+1, i );
            int stringWidth = tooltipText->font->calcStringWidth( itemValue[i] );
            tooltipText->font->drawText( x + frameWidth - xoffset - stringWidth, y, itemValue[i] );
            xoffset = xoffset + 25 + stringWidth;
        }
    }
    tooltipText->font->drawText( x + frameWidth - xoffset + 20 - stringWidth, y, realString );
}

void spellTooltip::draw( int x, int y )
{
    if ( tooltipText.empty() )
    {
        return;
    }

    // check to see if the ticket we got from the player is the same ticket as the player is offering.
    // if not, we reload our tooltip.
    if ( ticketFromPlayer != player->getTicketForSpellTooltip() )
    {
        reloadTooltip();
    }

    // make sure the tooltip doesnt go "off screen"
    if ( x + (curBlockNumberWidth + 2) * blockWidth > Configuration::screenWidth )
    {
        x = Configuration::screenWidth - (curBlockNumberWidth + 2) * blockWidth;
    }

    if ( y + (curBlockNumberHeight + 2) * blockHeight > Configuration::screenHeight )
    {
        y = Configuration::screenHeight - (curBlockNumberHeight + 2) * blockHeight;
    }

    // set the correct position based on where we are
    x += world_x;
    y += world_y;

	// set the first font Y-position on the top of the first tooltip block excluding topborder
    // (we could also center the text in the tooltip, but topaligned is probably bestlooking
    int font_y = y + blockHeight + (curBlockNumberHeight) * blockHeight - toplineHeight;

    Frames::drawFrame( x, y, curBlockNumberWidth, curBlockNumberHeight, blockWidth, blockHeight );

    // loop through the text vector and print all the text.
    for ( unsigned int i = 0; i < tooltipText.size(); i++ )
    {
        glColor4fv(tooltipText[i].color);
        tooltipText[i].font->drawText(x+blockWidth,font_y,tooltipText[i].text);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        font_y -= tooltipText[i].font->getHeight()+11;
        if ( smallTooltip ) {
            break;
        }
    }
}

void Tooltip::addTooltipText(GLfloat color[], uint8_t fontSize, std::string str, ...)
{
    std::va_list args;
	char buf[1024];

	va_start(args,str);
	vsnprintf(buf, 1024, str.c_str(), args);
	va_end(args);

    // if it's just a newline we're adding then just add it without checking for multiline...
    if ( str.empty() == true ) {
        tooltipText.push_back( sTooltipText( "", color, fontSize ) );
    } else if ( str.find("price:") != str.npos ) {
        // else check to see if the text contains price information. if so we dont wordwrap.
        tooltipText.push_back( sTooltipText( buf, color, fontSize ) );
    } else {
        // format the text into several lines so that the tooltip doesnt get too wide,
        //then push all the text lines to our vector.
        GLFT_Font *tempfont = FontCache::getFontFromCache("data/verdana.ttf",fontSize);
        std::vector<std::string> formattedLines;
        formatMultilineText( buf, formattedLines, 300, tempfont );
        for ( size_t curLine = 0; curLine < formattedLines.size(); curLine++ ) {
            tooltipText.push_back( sTooltipText( formattedLines[ curLine ], color, fontSize ) );
        }
    }

    // adjust width and height depending on the content of the tooltip.
    int width = 0;
    int height = 0;
    int widthSmall = 0;
    int heightSmall = 0;
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
        height += tooltipText[i].font->getHeight();
        if ( i+1 < tooltipText.size() ) {
        	height += 11;
        }
        if ( i==0 ) {
            widthSmall = width;
            heightSmall = height;
        }
    }

    blockNumberHeight = ceil( static_cast<double>(height) / blockHeight );
    blockNumberWidth = ceil( static_cast<double>(width) / blockWidth );
    blockNumberHeightSmall = ceil( static_cast<double>(heightSmall) / blockHeight );
    blockNumberWidthSmall = ceil( static_cast<double>(widthSmall) / blockWidth );

    updateBlockNumbers();
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
    ticketFromPlayer = player->getTicketForItemTooltip();
    shoppingState = player->isShopping();

    GLfloat grey[] = { 0.5f, 0.5f, 0.5f };
    GLfloat white[] = { 1.0f, 1.0f, 1.0f };
    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
    GLfloat orange[] = { 1.0f, 0.5f, 0.0f };
    GLfloat red[] = { 1.0f, 0.0f, 0.0f };
    GLfloat green[] = { 0.0f, 1.0f, 0.0f };
    GLfloat brownish[] = { 0.7f, 0.7f, 0.0f };
    std::string attribute_string[] = { "armor", "dexterity", "intellect", "strength", "vitality", "wisdom", "health", "mana", "fatigue", "health regen / s", "mana regen / s", "fatigue regen / s" };
    int8_t attribute_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
            addTooltipText( white, 12, ArmorType::getArmorTypeText( parent->getArmorType() ) );
        break;
        case ItemType::WEAPON:
            addTooltipText( white, 12, WeaponType::getWeaponTypeText( parent->getWeaponType() ) );
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
        addTooltipText( white, 12, EquipPosition::getEquipPositionText( parent->getEquipPosition() ) );
    }

    // displaying damage if it's a weapon.
    if ( parent->getItemType() == ItemType::WEAPON && parent->getWeaponType() != WeaponType::SHIELD && parent->getWeaponType() != WeaponType::SPELLBOOK )
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
    attribute_values[8] = parent->getStats( StatsType::Fatigue );
    attribute_values[9] = parent->getStats( StatsType::HealthRegen );
    attribute_values[10] = parent->getStats( StatsType::ManaRegen );
    attribute_values[11] = parent->getStats( StatsType::FatigueRegen );

    for (unsigned int i = 0; i < 12; i++ )
    {
        if ( attribute_values[i] != 0 )
        {
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

    int16_t parryModifier = parent->getStats( StatsType::ParryModifier );
	if ( parryModifier != 0 ) {
		double parryBonus = (StatsSystem::getStatsSystem()->complexGetParryChance( player->getLevel(), parryModifier, player->getLevel() )) * 100;
		addTooltipTextForPercentageAttribute( "chance to parry", parryBonus );
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
        addTooltipText( green, 11, parseInfoText( parent->getSpell(), parent->getUseableDescription() ) );
        if ( parent->getSpellCharges() > 0 ) {
	        addTooltipText( white, 11, "Charges: %d", parent->getSpellCharges() );
	    }
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
    uint8_t requiredLevel = 1;
    if ( parent->isUseable() ) {
        if ( parent->getSpell()->getRequiredLevel() > parent->getRequiredLevel() ) {
            requiredLevel = parent->getSpell()->getRequiredLevel();
        } else {
            requiredLevel = parent->getRequiredLevel();
        }
    } else {
        requiredLevel = parent->getRequiredLevel();
    }

    if ( requiredLevel > player->getLevel() ) {
        addTooltipText( white, 12, "" );
        addTooltipText( red, 12, "Requires level %d", requiredLevel );
    }

    // display item level requirements if player's level is too low.
    if ( parent->isUseable() ) {
        if ( parent->getSpell()->getRequiredClass() != player->getClass() && parent->getSpell()->getRequiredClass() != CharacterClass::ANYCLASS ) {
            addTooltipText( red, 12, "Requires class %s", CharacterClass::getCharacterClassName( parent->getSpell()->getRequiredClass() ).c_str() );
        }

        if ( parent->getItemType() == ItemType::NEWSPELL ) {
            if ( player->isSpellInscribedInSpellbook( parent->getSpell() ) == true ) {
                addTooltipText( red, 11, "Already inscribed in spellbook." );
            }
        }
    }

    int32_t coins = parent->getValue();

    if ( player->isShopping() )
    {
        if ( isShopItem )
        {
            itemValue[0] = currency::convertCoinsToString(currency::COPPER, coins );
            itemValue[1] = currency::convertCoinsToString(currency::SILVER, coins );
            itemValue[2] = currency::convertCoinsToString(currency::GOLD, coins );
            addTooltipText( white, 12, "Buy price: xxxxxxxxxxxx" );
        } else {
            itemValue[0] = currency::convertCoinsToString(currency::COPPER, coins * 0.75 );
            itemValue[1] = currency::convertCoinsToString(currency::SILVER, coins * 0.75 );
            itemValue[2] = currency::convertCoinsToString(currency::GOLD, coins * 0.75 );
            addTooltipText( white, 12, "Sell price: xxxxxxxxxxx" );
    	}
    }
}

void spellTooltip::getParentText()
{
    // remember what level we generated this tooltip
    ticketFromPlayer = player->getTicketForSpellTooltip();

    GLfloat white[] = { 1.0f, 1.0f, 1.0f };
    GLfloat grey[] = { 0.7f, 0.7f, 0.7f };
    GLfloat blue[] = { 0.3f, 0.3f, 1.0f };
    GLfloat green[] = { 0.0f, 1.0f, 0.0f };
    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };

    // name of the spell and rank
    addTooltipText( white, 14, parent->getName() );
    addTooltipText( white, 12, "" );
    addTooltipText( grey, 12, "Rank %d", parent->getRank() );

    // display mana or fatigue-cost, if any.
    if ( parent->getSpellCost() > 0 )
    {
        if ( player->getArchType() == CharacterArchType::Caster ) {
            addTooltipText( blue, 12, "Mana: %d", parent->getSpellCost() );
        } else if ( player->getArchType() == CharacterArchType::Fighter ) {
            addTooltipText( yellow, 12, "Fatigue: %d", parent->getSpellCost() );
        }
    }

    /// display required weapons
    if ( parent->getRequiredWeapons() != 0 ) {
        int numberOfRequiredWeapons = 0;
        std::string reqWeaponString = "Requires: ";

        for ( size_t curWeaponType = 0; curWeaponType < getNumBitsToUse( WeaponType::COUNT ); curWeaponType++ ) {
            if ( parent->getRequiredWeapons() & static_cast<WeaponType::WeaponType>( 1 << curWeaponType ) ) {
                if ( numberOfRequiredWeapons > 0 ) { reqWeaponString.append( ", " ); }
                reqWeaponString.append( WeaponType::getWeaponTypeText( static_cast<WeaponType::WeaponType>( 1 << curWeaponType ) ) );
                numberOfRequiredWeapons++;
            }
         }
        if ( numberOfRequiredWeapons > 1 ) {
            reqWeaponString.replace( reqWeaponString.find_last_of( "," ), 1, " or" );
        }
        addTooltipText(blue, 12, reqWeaponString );
    }

    // display duration if we have any
    if ( parent->getDuration() > 0 ) {
        addTooltipText( white, 12, "Duration: %s", TimeConverter::convertTime( parent->getDuration() ).c_str() );
    }

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

    // display description.
    addTooltipText( white, 12, "" ); // newline
    addTooltipText( green, 12, parseInfoText( parent, parent->getInfo() ) );
}

std::string Tooltip::getDynamicValues( CSpellActionBase *spell, size_t val ) const
{
    const StatsSystem *statsSystem = StatsSystem::getStatsSystem();
    std::stringstream ss;
    ss.str() = "";

    switch ( val ) {
        case 0: // minWeaponDamage
            if ( dynamic_cast<MeleeDamageAction*>( spell )  != NULL ) {
                MeleeDamageAction *curSpell = dynamic_cast<MeleeDamageAction*>( spell );
                ss << static_cast<int16_t>( player->getModifiedMinDamage() * statsSystem->complexGetDamageModifier( player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel() ) * curSpell->getDamageBonus() );
                return ss.str();
            } else if ( dynamic_cast<RangedDamageAction*>( spell ) != NULL ) {
                RangedDamageAction *curSpell = dynamic_cast<RangedDamageAction*>( spell );
                ss << static_cast<int16_t>( player->getModifiedMinDamage() * statsSystem->complexGetDamageModifier( player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel() ) * curSpell->getDamageBonus() );
                return ss.str();
            }
        break;
        case 1: // maxWeaponDamage
            if ( dynamic_cast<MeleeDamageAction*>( spell ) != NULL ) {
                MeleeDamageAction *curSpell = dynamic_cast<MeleeDamageAction*>( spell );
                ss << static_cast<int16_t>( player->getModifiedMaxDamage() * statsSystem->complexGetDamageModifier( player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel() ) * curSpell->getDamageBonus() );
                return ss.str();
            } else if ( dynamic_cast<RangedDamageAction*>( spell ) != NULL ) {
                RangedDamageAction *curSpell = dynamic_cast<RangedDamageAction*>( spell );
                ss << static_cast<int16_t>( player->getModifiedMaxDamage() * statsSystem->complexGetDamageModifier( player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel() ) * curSpell->getDamageBonus() );
                return ss.str();
            }
        break;
        case 2: // minSpellDirectDamage
            if ( dynamic_cast<GeneralDamageSpell*>( spell ) != NULL ) {
                GeneralDamageSpell *curSpell = dynamic_cast<GeneralDamageSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDirectDamageMin() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getDirectDamageElement() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 3: // maxSpellDirectDamage
            if ( dynamic_cast<GeneralDamageSpell*>( spell ) != NULL ) {
                GeneralDamageSpell *curSpell = dynamic_cast<GeneralDamageSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDirectDamageMax() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getDirectDamageElement() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 4: // minSpellContinuousDamage
            if ( dynamic_cast<GeneralDamageSpell*>( spell ) != NULL ) {
                GeneralDamageSpell *curSpell = dynamic_cast<GeneralDamageSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDuration() * curSpell->getContinuousDamageMin() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getContinuousDamageElement() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 5: // maxSpellContinuousDamage
            if ( dynamic_cast<GeneralDamageSpell*>( spell ) != NULL ) {
                GeneralDamageSpell *curSpell = dynamic_cast<GeneralDamageSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDuration() * curSpell->getContinuousDamageMax() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getContinuousDamageElement() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 6: // minDirectHealing
            if ( dynamic_cast<GeneralHealingSpell*>( spell ) != NULL ) {
                GeneralHealingSpell *curSpell = dynamic_cast<GeneralHealingSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDirectHealingMin() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getDirectElementType() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 7: // maxDirectHealing
            if ( dynamic_cast<GeneralHealingSpell*>( spell ) != NULL ) {
                GeneralHealingSpell *curSpell = dynamic_cast<GeneralHealingSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDirectHealingMax() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getDirectElementType() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 8: // minContinuousHealing
            if ( dynamic_cast<GeneralHealingSpell*>( spell ) != NULL ) {
                GeneralHealingSpell *curSpell = dynamic_cast<GeneralHealingSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDuration() * curSpell->getContinuousHealingMin() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getContinuousElementType() ), player->getLevel() ) );
                return ss.str();
            }
        break;
        case 9: // maxContinuousHealing
            if ( dynamic_cast<GeneralHealingSpell*>( spell ) != NULL ) {
                GeneralHealingSpell *curSpell = dynamic_cast<GeneralHealingSpell*>( spell );
                ss << static_cast<int16_t>( curSpell->getDuration() * curSpell->getContinuousHealingMax() * StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curSpell->getContinuousElementType() ), player->getLevel() ) );
                return ss.str();
            }
        break;
    }
    return "";
}

std::string Tooltip::parseInfoText( CSpellActionBase *spell, const std::string infoText ) const
{
    std::string toReturn = infoText;
    std::vector<std::string> stats;
    stats.push_back( "%minWeaponDamage%" );
    stats.push_back( "%maxWeaponDamage%" );
    stats.push_back( "%minSpellDirectDamage%" );
    stats.push_back( "%maxSpellDirectDamage%" );
    stats.push_back( "%minSpellContinuousDamage%" );
    stats.push_back( "%maxSpellContinuousDamage%" );
    stats.push_back( "%minDirectHealing%" );
    stats.push_back( "%maxDirectHealing%" );
    stats.push_back( "%minContinuousHealing%" );
    stats.push_back( "%maxContinuousHealing%" );

    for ( size_t index = 0; index < stats.size(); index++ ) {
        if ( toReturn.find( stats[ index ] ) != toReturn.npos ) {
            int findRet = toReturn.find( stats[ index ] );
            toReturn.replace( findRet, stats[ index ].length(), getDynamicValues( spell, index ) );
        }
    }
    return toReturn;
}

CSpellActionBase *spellTooltip::getParent() const
{
    return parent;
}

Item *itemTooltip::getParent() const
{
    return parent;
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
		frameTextures->texture.resize( 12 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower_left2.tga", 0 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower_right2.tga", 1 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper_left2.tga", 2 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper_right2.tga", 3 );
		frameTextures->LoadIMG( "data/interface/tooltip/background2.tga", 4 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper2.tga", 5 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower2.tga", 6 );
		frameTextures->LoadIMG( "data/interface/tooltip/left2.tga", 7 );
		frameTextures->LoadIMG( "data/interface/tooltip/right2.tga", 8 );
		frameTextures->LoadIMG( "data/interface/inventory/goldcoin.tga", 9 );
        frameTextures->LoadIMG( "data/interface/inventory/silvercoin.tga", 10 );
        frameTextures->LoadIMG( "data/interface/inventory/coppercoin.tga", 11 );

	}

	void drawFrame( int leftX, int bottomY, int numBlocksX, int numBlocksY, int blockWidth, int blockHeight )
	{
		// draw the corners
		DrawingHelpers::mapTextureToRect( frameTextures->texture[0], leftX, blockWidth, bottomY, blockHeight); // lower left corner
		DrawingHelpers::mapTextureToRect( frameTextures->texture[1], leftX+blockWidth+(numBlocksX*blockWidth), blockWidth, bottomY, blockHeight); // lower right corner
		DrawingHelpers::mapTextureToRect( frameTextures->texture[2], leftX, blockWidth, bottomY+blockHeight+(numBlocksY*blockHeight), blockHeight); // upper left corner
		DrawingHelpers::mapTextureToRect( frameTextures->texture[3], leftX+blockWidth+(numBlocksX*blockWidth), blockWidth, bottomY+blockHeight+(numBlocksY*blockHeight), blockHeight); // upper right corner

		// draw the top and bottom borders
		for ( int blockX = 0; blockX < numBlocksX; blockX++ )
		{
			DrawingHelpers::mapTextureToRect( frameTextures->texture[5], leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY+blockHeight+(numBlocksY*blockHeight),blockHeight); // top border
			DrawingHelpers::mapTextureToRect( frameTextures->texture[6], leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY,blockHeight); // bottom border
		}

		// draw the right and left borders
		for ( int blockY = 0; blockY < numBlocksY; blockY++ )
		{
			DrawingHelpers::mapTextureToRect( frameTextures->texture[7], leftX,blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight); // left border
			DrawingHelpers::mapTextureToRect( frameTextures->texture[8], leftX+blockWidth+(numBlocksX*blockWidth),blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight); // right border
		}

		// draw the background
		for ( int blockY = 0; blockY < numBlocksY; blockY++ )
		{
			for ( int blockX = 0; blockX < numBlocksX; blockX++ )
			{
				DrawingHelpers::mapTextureToRect( frameTextures->texture[4], leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight);
			}
		}
	}

	void drawCoin( int x, int y, int coin )
	{
	    if ( coin == currency::GOLD )
	    {
	        DrawingHelpers::mapTextureToRect( frameTextures->texture[9], x, 16, y, 16 );
	    }
	    if ( coin == currency::SILVER )
	    {
	        DrawingHelpers::mapTextureToRect( frameTextures->texture[10], x, 16, y, 16 );
	    }
	    if ( coin == currency::COPPER )
	    {
	        DrawingHelpers::mapTextureToRect( frameTextures->texture[11], x, 16, y, 16 );
	    }
	}
} // namespace Frames


