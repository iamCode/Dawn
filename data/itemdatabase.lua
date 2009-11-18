itemDatabase = {};

nextName="A wooden shield";
itemDatabase[nextName]=DawnInterface.createNewItem( nextName, 2, 2, "data/items/shield.tga", ItemQuality.NORMAL, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SHIELD );
	curItem = itemDatabase[nextName];
	curItem:setArmor( 20 );

nextName="A rusty sword";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName, 1, 3, "data/items/sword.tga", ItemQuality.POOR, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
	curItem = itemDatabase[nextName];
	curItem:setStrength( -1 );
	curItem:setMinDamage( 3 );
	curItem:setMaxDamage( 6 );

nextName="Sword of Khazom";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName, 1, 3, "data/items/SwordOfKhazom.tga", ItemQuality.LORE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
	curItem = itemDatabase[nextName];
	curItem:setDexterity( 5 );
	curItem:setStrength( 10 );
	curItem:setHealth( 75 );
	curItem:setMinDamage( 10 );
	curItem:setMaxDamage( 25 );
	curItem:setDamageModifierPoints( 10 );
	curItem:setHitModifierPoints( 30 );
	curItem:setDescription( "Once wielded by Irk the Unholy." );

nextName="Shortsword";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName,1,3, "data/items/Sword1.tga", ItemQuality.NORMAL, EquipPosition.MAIN_HAND,ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.ONEHAND_SWORD );
	curItem = itemDatabase[nextName];
	curItem:setMinDamage( 6 );
	curItem:setMaxDamage( 10 );

nextName="Eye of Licor";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName, 1, 1, "data/items/EyeOfLicor.tga", ItemQuality.RARE, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
	curItem = itemDatabase[nextName];
	curItem:setIntellect( 4 );
	curItem:setMana( 15 );
	curItem:setStrength ( -1 );
	
nextName="Gnoll shield";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName, 2, 2, "data/items/shield0.tga", ItemQuality.ENHANCED, EquipPosition.OFF_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.SHIELD );
	curItem = itemDatabase[nextName];
	curItem:setArmor( 70 );
	curItem:setVitality( 3 );
	curItem:setEvadeModifierPoints( 20 );
	
nextName="Gutteraxe";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName, 2, 3, "data/items/Axe1.tga", ItemQuality.RARE, EquipPosition.MAIN_HAND, ItemType.WEAPON, ArmorType.NO_ARMOR, WeaponType.TWOHAND_AXE);
	curItem = itemDatabase[nextName];
	curItem:setDexterity( 10 );
	curItem:setStrength( 10 );
	curItem:setLevelReq( 5 );
	curItem:setMinDamage( 32 );
	curItem:setMaxDamage( 81 );
	
nextName="Snakeloop";
itemDatabase[nextName]=DawnInterface.createNewItem(nextName, 1, 1, "data/items/Ring1.tga", ItemQuality.ENHANCED, EquipPosition.RING, ItemType.JEWELRY, ArmorType.NO_ARMOR, WeaponType.NO_WEAPON );
	curItem = itemDatabase[nextName];
	curItem:setVitality( 2 );
	curItem:setLevelReq( 2 );

