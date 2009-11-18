--[[
itemdatabase.lua generated 2009-11-18 23:11:58 by arnestig.
--]]

itemDatabase = {};

itemDatabase["awoodenshield"]=DawnInterface.createNewItem( "A wooden shield", 2, 2, "data/items/shield.tga", ItemQuality.NORMAL, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SHIELD );
curItem = itemDatabase["awoodenshield"];
curItem:setArmor( 30 );


itemDatabase["arustysword"]=DawnInterface.createNewItem( "A rusty sword", 1, 3, "data/items/sword.tga", ItemQuality.POOR, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["arustysword"];
curItem:setStrength( -1 );
curItem:setMinDamage( 3 );
curItem:setMaxDamage( 6 );


itemDatabase["swordofkhazom"]=DawnInterface.createNewItem( "Sword of Khazom", 1, 3, "data/items/SwordOfKhazom.tga", ItemQuality.LORE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["swordofkhazom"];
curItem:setDexterity( 5 );
curItem:setStrength( 10 );
curItem:setHealth( 75 );
curItem:setMinDamage( 10 );
curItem:setMaxDamage( 25 );
curItem:setDescription( "Once wielded by Irk the Unholy." );


itemDatabase["shortsword"]=DawnInterface.createNewItem( "Shortsword", 1, 3, "data/items/Sword1.tga", ItemQuality.NORMAL, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["shortsword"];
curItem:setMinDamage( 6 );
curItem:setMaxDamage( 10 );


itemDatabase["eyeoflicor"]=DawnInterface.createNewItem( "Eye of Licor", 1, 1, "data/items/EyeOfLicor.tga", ItemQuality.RARE, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["eyeoflicor"];
curItem:setIntellect( 4 );
curItem:setStrength( -1 );
curItem:setDescription( "No'dre entoras lictor." );


itemDatabase["gnollshield"]=DawnInterface.createNewItem( "Gnoll shield", 2, 2, "data/items/shield0.tga", ItemQuality.ENHANCED, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SHIELD );
curItem = itemDatabase["gnollshield"];
curItem:setVitality( 3 );
curItem:setArmor( 70 );


itemDatabase["gutteraxe"]=DawnInterface.createNewItem( "Gutteraxe", 2, 3, "data/items/Axe1.tga", ItemQuality.RARE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.TWOHAND_AXE );
curItem = itemDatabase["gutteraxe"];
curItem:setDexterity( 10 );
curItem:setStrength( 10 );
curItem:setMinDamage( 32 );
curItem:setMaxDamage( 81 );
curItem:setLevelReq( 5 );


itemDatabase["snakeloop"]=DawnInterface.createNewItem( "Snakeloop", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["snakeloop"];
curItem:setVitality( 2 );
curItem:setLevelReq( 2 );


itemDatabase["bladeofstrength"]=DawnInterface.createNewItem( "Blade of Strength", 1, 3, "data/items/Sword1.tga", ItemQuality.ENHANCED, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["bladeofstrength"];
curItem:setStrength( 4 );
curItem:setHealth( 5 );
curItem:setMinDamage( 5 );
curItem:setMaxDamage( 13 );
curItem:setLevelReq( 3 );


itemDatabase["ringofdefense"]=DawnInterface.createNewItem( "Ring of Defense", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["ringofdefense"];
curItem:setArmor( 30 );
curItem:setEvadeModifierPoints( 5 );


itemDatabase["shadering"]=DawnInterface.createNewItem( "Shade ring", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["shadering"];
curItem:setDexterity( 2 );
curItem:setEvadeModifierPoints( 10 );
curItem:setLevelReq( 3 );


