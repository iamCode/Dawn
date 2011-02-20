-- ===============================================================================================
-- Information about adding triggerspells.
--
-- addTriggerSpellOnSelf( CSpellActionBase *spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType );
-- addTriggerSpellOnTarget( CSpellActionBase *spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType );
--
-- addTriggerSpellOnSelf will execute the spell on the player if triggered.
-- addTriggerSpellOnTarget will execute the spell on the current target on the player (if any).
--
-- Two TriggerTypes to choose from so far, more might come: 
-- TriggerType.TAKING_DAMAGE - To be used if we want to trigger the spell when taking damage.
-- TriggerType.EXECUTING_ACTION - To be used if we want to trigger the spell when casting / attacking.
--
-- Example:
-- curItem:addTriggerSpellOnSelf( spellDatabase["leatherskin"], 0.05, TriggerType.TAKING_DAMAGE );
-- This will cast give the item a 5% chance to cast the spell leatherskin when we're taking damage.
-- ===============================================================================================

-- == item stacks ==
-- Itemstacks can be used to allow us to have several items of one sort in one item.
-- For example "Spellcharges" work this way now. If we want to let the player have 5 charges of an healing potion in one inventory position, then we need to set setMaxStackSize( 5 ) to that item.
-- Same goes for any other item we want to stack up.


itemDatabase = {};

itemDatabase["axeofanguish"]=DawnInterface.createNewItem( "Axe of Anguish", 2, 3, "data/items/Axe2.tga", ItemQuality.ENHANCED, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.TWOHAND_AXE );
curItem = itemDatabase["axeofanguish"];
curItem:setStats( StatsType.Strength, 2 );
curItem:setStats( StatsType.HitModifier, 5 );
curItem:setMinDamage( 7 );
curItem:setMaxDamage( 15 );
curItem:setRequiredLevel( 1 );
curItem:setStats( StatsType.MeleeCritical, 25 );
curItem:setValue( 56818 );


itemDatabase["arustysword"]=DawnInterface.createNewItem( "A rusty sword", 1, 3, "data/items/Sword1.tga", ItemQuality.POOR, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["arustysword"];
curItem:setStats( StatsType.Strength, -1 );
curItem:setMinDamage( 3 );
curItem:setMaxDamage( 6 );
curItem:setValue( 80 );


itemDatabase["swordofkhazom"]=DawnInterface.createNewItem( "Sword of Khazom", 1, 3, "data/items/Sword1.tga", ItemQuality.LORE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["swordofkhazom"];
curItem:setStats( StatsType.Dexterity, 5 );
curItem:setStats( StatsType.Strength, 10 );
curItem:setStats( StatsType.Health, 75 );
curItem:setMinDamage( 10 );
curItem:setMaxDamage( 25 );
curItem:setDescription( "Once wielded by Irk the Unholy." );
curItem:setResistElementModifierPoints( ElementType.Dark, 15 );
curItem:setValue( 101280 );


itemDatabase["shortsword"]=DawnInterface.createNewItem( "Shortsword", 1, 3, "data/items/Sword1.tga", ItemQuality.NORMAL, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["shortsword"];
curItem:setMinDamage( 6 );
curItem:setMaxDamage( 10 );
curItem:setValue( 100 );


itemDatabase["eyeoflicor"]=DawnInterface.createNewItem( "Eye of Licor", 1, 1, "data/items/Ring3.tga", ItemQuality.RARE, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["eyeoflicor"];
curItem:setStats( StatsType.Intellect, 4 );
curItem:setStats( StatsType.Strength, -1 );
curItem:setDescription( "No'dre entoras lictor." );
curItem:setValue( 1090 );


itemDatabase["gnollshield"]=DawnInterface.createNewItem( "Gnoll shield", 2, 2, "data/items/Shield1.tga", ItemQuality.ENHANCED, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SHIELD );
curItem = itemDatabase["gnollshield"];
curItem:setStats( StatsType.Vitality, 3 );
curItem:setStats( StatsType.ParryModifier, 3 );
curItem:setStats( StatsType.Armor, 70 );
curItem:addTriggerSpellOnSelf( spellDatabase["steelgrip"], 0.05, TriggerType.TAKING_DAMAGE );
curItem:setValue( 225 );


itemDatabase["gutteraxe"]=DawnInterface.createNewItem( "Gutteraxe", 2, 3, "data/items/Axe1.tga", ItemQuality.RARE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.TWOHAND_AXE );
curItem = itemDatabase["gutteraxe"];
curItem:setStats( StatsType.Dexterity, 10 );
curItem:setStats( StatsType.Strength, 10 );
curItem:setMinDamage( 32 );
curItem:setMaxDamage( 81 );
curItem:setRequiredLevel( 5 );
curItem:setValue( 11500 );


itemDatabase["snakeloop"]=DawnInterface.createNewItem( "Snakeloop", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["snakeloop"];
curItem:setStats( StatsType.Intellect, 3 );
curItem:setRequiredLevel( 1 );
curItem:setSpellEffectElementModifierPoints( ElementType.Light, 20 );
curItem:setValue( 2500 );


itemDatabase["bladeofstrength"]=DawnInterface.createNewItem( "Blade of Strength", 1, 3, "data/items/Sword1.tga", ItemQuality.ENHANCED, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
curItem = itemDatabase["bladeofstrength"];
curItem:setStats( StatsType.Strength, 4 );
curItem:setStats( StatsType.Health, 5 );
curItem:setMinDamage( 5 );
curItem:setMaxDamage( 13 );
curItem:setRequiredLevel( 3 );
curItem:setValue( 300 );


itemDatabase["ringofdefense"]=DawnInterface.createNewItem( "Ring of Defense", 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["ringofdefense"];
curItem:setStats( StatsType.Armor, 30 );
curItem:setStats( StatsType.EvadeModifier, 5 );
curItem:setStats( StatsType.ResistAll, 1 );
curItem:setValue( 215 );


itemDatabase["shadering"]=DawnInterface.createNewItem( "Shade ring", 1, 1, "data/items/Ring2.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["shadering"];
curItem:setStats( StatsType.Dexterity, 2 );
curItem:setStats( StatsType.EvadeModifier, 10 );
curItem:setRequiredLevel( 3 );
curItem:setValue( 110 );


itemDatabase["scrolloftheboar"]=DawnInterface.createNewItem( "Scroll of the Boar", 1, 1, "data/items/Scroll1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.SCROLL, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["scrolloftheboar"];
curItem:setRequiredLevel( 1 );
curItem:setSpell( spellDatabase["spiritoftheboar"] );
curItem:setValue( 100 );
curItem:setMaxStackSize( 5 );


itemDatabase["smallhealingpotion"]=DawnInterface.createNewItem( "Small healing potion", 1, 1, "data/items/Potion1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.POTION, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["smallhealingpotion"];
curItem:setSpell( spellDatabase["smallhealingpotion"] );
curItem:setValue( 500 );
curItem:setMaxStackSize( 5 );


itemDatabase["tornleatherbelt"]=DawnInterface.createNewItem( "Torn leather belt", 2, 1, "data/items/Belt1.tga", ItemQuality.NORMAL, EquipPosition.BELT, ItemType.ARMOR, ArmorType.LEATHER, WeaponType.NO_WEAPON );
curItem = itemDatabase["tornleatherbelt"];
curItem:setStats( StatsType.Armor, 12 );
curItem:setValue( 86 );

itemDatabase["bookofmagicmissilerank2"]=DawnInterface.createNewItem( "Book of Magic Missile", 2, 2, "data/items/Spellbook1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.NEWSPELL, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["bookofmagicmissilerank2"];
curItem:setSpell( spellDatabase["magicmissilerank2"] );
curItem:setValue( 2500 );

itemDatabase["coppernecklace"]=DawnInterface.createNewItem( "Copper necklace", 1, 1, "data/items/Necklace1.tga", ItemQuality.ENHANCED, EquipPosition.AMULET,ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["coppernecklace"];
curItem:setStats( StatsType.Vitality, 1 );
curItem:setStats( StatsType.Wisdom, 1 );
curItem:setValue( 20 );

itemDatabase["daggerofflowingthought"]=DawnInterface.createNewItem( "Dagger of flowing thought", 1, 2, "data/items/Dagger1.tga", ItemQuality.RARE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.DAGGER );
curItem = itemDatabase["daggerofflowingthought"];
curItem:setStats( StatsType.SpellCritical, 7 );
curItem:setStats( StatsType.Wisdom, 3 );
curItem:setStats( StatsType.ManaRegen, 2 );
curItem:setMinDamage( 2 );
curItem:setMaxDamage( 6 );
curItem:setValue( 216 );
curItem:addTriggerSpellOnSelf( spellDatabase["flowingthought"], 0.1, TriggerType.EXECUTING_ACTION );

itemDatabase["fungalboots"]=DawnInterface.createNewItem( "Fungal boots", 2, 2, "data/items/Boots1.tga", ItemQuality.ENHANCED, EquipPosition.BOOTS, ItemType.ARMOR, ArmorType.LEATHER, WeaponType.NO_WEAPON );
curItem = itemDatabase["fungalboots"];
curItem:setStats( StatsType.Armor, 7 );
curItem:setStats( StatsType.HealthRegen, 2 );
curItem:setValue( 78 );

itemDatabase["bookofleatherskinrank2"]=DawnInterface.createNewItem( "Book of Leatherskin", 2, 2, "data/items/Spellbook1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.NEWSPELL, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["bookofleatherskinrank2"];
curItem:setSpell( spellDatabase["leatherskinrank2"] );
curItem:setValue( 2500 );

itemDatabase["ajuicyapple"]=DawnInterface.createNewItem( "A juicy apple", 1, 1, "data/items/Food1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.FOOD, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["ajuicyapple"];
curItem:setSpell( spellDatabase["food"] );
curItem:setValue( 25 );
curItem:setMaxStackSize( 5 );

itemDatabase["patchofwolfskin"]=DawnInterface.createNewItem( "Patch of wolf skin", 1, 1, "data/items/Skin1.tga", ItemQuality.POOR, EquipPosition.NONE, ItemType.MISCELLANEOUS, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["patchofwolfskin"];
curItem:setValue( 5 );
curItem:setMaxStackSize( 20 );

itemDatabase["spidersilk"]=DawnInterface.createNewItem( "Spidersilk", 1, 1, "data/items/Web1.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.MISCELLANEOUS, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["spidersilk"];
curItem:setValue( 16 );
curItem:setMaxStackSize( 20 );

itemDatabase["wolfmeat"]=DawnInterface.createNewItem( "Wolf meat", 1, 1, "data/items/Meat2.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.MISCELLANEOUS, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["wolfmeat"];
curItem:setValue( 10 );
curItem:setMaxStackSize( 20 );

itemDatabase["awaterpouch"]=DawnInterface.createNewItem( "A waterpouch", 1, 1, "data/items/Food2.tga", ItemQuality.NORMAL, EquipPosition.NONE, ItemType.FOOD, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
curItem = itemDatabase["awaterpouch"];
curItem:setSpell( spellDatabase["drink"] );
curItem:setValue( 40 );
curItem:setMaxStackSize( 5 );

itemDatabase["weakenedbow"]=DawnInterface.createNewItem( "Weakened bow", 2, 3, "data/items/Bow1.tga", ItemQuality.POOR, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.BOW );
curItem = itemDatabase["weakenedbow"];
curItem:setMinDamage( 4 );
curItem:setMaxDamage( 7 );
curItem:setValue( 78 );

itemDatabase["moldytome"]=DawnInterface.createNewItem( "Moldy tome", 2, 2, "data/items/Spellbook2.tga", ItemQuality.ENHANCED, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SPELLBOOK );
curItem = itemDatabase["moldytome"];
curItem:setSpellEffectElementModifierPoints( ElementType.Dark, 6 );
curItem:setStats( StatsType.Wisdom, 2 );
curItem:setStats( StatsType.ManaRegen, 1 );
