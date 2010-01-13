--[[
itemdatabase.lua generated 2009-12-03 23:12:08 by arnestig.
--]]

itemDatabase = {};

itemDatabase["axeofanguish"]=DawnInterface.createNewItem( "Axe of Anguish", 2, 3, "data/items/Axe2.tga", ItemQuality.ENHANCED, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.TWOHAND_AXE );
curItem = itemDatabase["axeofanguish"];
curItem:setStats(StatsType.Strength, 2 );
curItem:setStats(StatsType.HitModifier, 5 );
curItem:setMinDamage( 7 );
curItem:setMaxDamage( 15 );
curItem:setLevelReq( 1 );
curItem:setStats(StatsType.MeleeCritical, 25 );


itemDatabase["arustysword"]=DawnInterface.createNewItem( "A rusty sword", 1, 3, "data/items/Sword1.tga", ItemQuality.POOR, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["arustysword"];
curItem:setStats(StatsType.Strength, -1 );
curItem:setMinDamage( 3 );
curItem:setMaxDamage( 6 );


itemDatabase["swordofkhazom"]=DawnInterface.createNewItem( "Sword of Khazom", 1, 3, "data/items/Sword1.tga", ItemQuality.LORE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["swordofkhazom"];
curItem:setStats(StatsType.Dexterity, 5 );
curItem:setStats(StatsType.Strength, 10 );
curItem:setStats(StatsType.Health, 75 );
curItem:setMinDamage( 10 );
curItem:setMaxDamage( 25 );
curItem:setDescription( "Once wielded by Irk the Unholy." );
curItem:setResistElementModifierPoints( ElementType.Dark, 15 );


itemDatabase["shortsword"]=DawnInterface.createNewItem( "Shortsword", 1, 3, "data/items/Sword1.tga", ItemQuality.NORMAL, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["shortsword"];
curItem:setMinDamage( 6 );
curItem:setMaxDamage( 10 );


itemDatabase["eyeoflicor"]=DawnInterface.createNewItem( "Eye of Licor", 1, 1, "data/items/Ring3.tga", ItemQuality.RARE, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["eyeoflicor"];
curItem:setStats(StatsType.Intellect, 4 );
curItem:setStats(StatsType.Strength, -1 );
curItem:setDescription( "No'dre entoras lictor." );


itemDatabase["gnollshield"]=DawnInterface.createNewItem( "Gnoll shield", 2, 2, "data/items/Shield1.tga", ItemQuality.ENHANCED, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SHIELD );
curItem = itemDatabase["gnollshield"];
curItem:setStats(StatsType.Vitality, 3 );
curItem:setStats(StatsType.Armor, 70 );


itemDatabase["gutteraxe"]=DawnInterface.createNewItem( "Gutteraxe", 2, 3, "data/items/Axe1.tga", ItemQuality.RARE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.TWOHAND_AXE );
curItem = itemDatabase["gutteraxe"];
curItem:setStats(StatsType.Dexterity, 10 );
curItem:setStats(StatsType.Strength, 10 );
curItem:setMinDamage( 32 );
curItem:setMaxDamage( 81 );
curItem:setLevelReq( 5 );


itemDatabase["snakeloop"]=DawnInterface.createNewItem( "Snakeloop", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["snakeloop"];
curItem:setStats(StatsType.Intellect, 3 );
curItem:setLevelReq( 1 );
curItem:setSpellEffectElementModifierPoints( ElementType.Light, 20 );


itemDatabase["bladeofstrength"]=DawnInterface.createNewItem( "Blade of Strength", 1, 3, "data/items/Sword1.tga", ItemQuality.ENHANCED, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["bladeofstrength"];
curItem:setStats(StatsType.Strength, 4 );
curItem:setStats(StatsType.Health, 5 );
curItem:setMinDamage( 5 );
curItem:setMaxDamage( 13 );
curItem:setLevelReq( 3 );


itemDatabase["ringofdefense"]=DawnInterface.createNewItem( "Ring of Defense", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["ringofdefense"];
curItem:setStats(StatsType.Armor, 30 );
curItem:setStats(StatsType.EvadeModifier, 5 );
curItem:setStats(StatsType.ResistAll, 1 );


itemDatabase["shadering"]=DawnInterface.createNewItem( "Shade ring", 1, 1, "data/items/Ring2.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["shadering"];
curItem:setStats(StatsType.Dexterity, 2 );
curItem:setStats(StatsType.EvadeModifier, 10 );
curItem:setLevelReq( 3 );


itemDatabase["scrollofleatherskin"]=DawnInterface.createNewItem( "Scroll of Leatherskin", 1, 1, "data/items/Scroll1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.SCROLL, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["scrollofleatherskin"];
curItem:setLevelReq( 1 );


