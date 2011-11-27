--note: this is just for debug the items need to be copied not accessed directly else the same reference is used!!!

local thePlayer = DawnInterface.getPlayer();

-- items to give to our warriors
if( thePlayer:getClass() == CharacterClass.Warrior ) then
	DawnInterface.giveItemToPlayer( itemDatabase["axeofanguish"] );
		DawnInterface.giveItemToPlayer( itemDatabase["bladeofstrength"] );
end

-- items to give to our rangers
if( thePlayer:getClass() == CharacterClass.Ranger ) then
	DawnInterface.giveItemToPlayer(itemDatabase["weakenedbow"] );
end

-- items to give to our liches
if( thePlayer:getClass() == CharacterClass.Liche ) then
	DawnInterface.giveItemToPlayer( itemDatabase["bookofmagicmissilerank2"] );
	DawnInterface.giveItemToPlayer( itemDatabase["moldytome"] );
	DawnInterface.giveItemToPlayer( itemDatabase["daggerofflowingthought"] );
end

DawnInterface.giveItemToPlayer( itemDatabase["swordofkhazom"] );
DawnInterface.giveItemToPlayer( itemDatabase["eyeoflicor"] );
DawnInterface.giveItemToPlayer( itemDatabase["gnollshield"] );
DawnInterface.giveItemToPlayer( itemDatabase["gutteraxe"] );
DawnInterface.giveItemToPlayer( itemDatabase["snakeloop"] );
DawnInterface.giveItemToPlayer( itemDatabase["shadering"] );
DawnInterface.giveItemToPlayer( itemDatabase["scrolloftheboar"] );
DawnInterface.giveItemToPlayer( itemDatabase["scrolloftheboar"] );
DawnInterface.giveItemToPlayer( itemDatabase["scrolloftheboar"] );
DawnInterface.giveItemToPlayer( itemDatabase["smallhealingpotion"] );
DawnInterface.giveItemToPlayer( itemDatabase["tornleatherbelt"] );
DawnInterface.giveItemToPlayer( itemDatabase["coppernecklace"] );
DawnInterface.giveItemToPlayer( itemDatabase["fungalboots"] );
DawnInterface.giveItemToPlayer( itemDatabase["ajuicyapple"] );
DawnInterface.giveItemToPlayer( itemDatabase["ajuicyapple"] );
DawnInterface.giveItemToPlayer( itemDatabase["awaterpouch"] );
DawnInterface.giveItemToPlayer( itemDatabase["awaterpouch"] );
DawnInterface.giveItemToPlayer( itemDatabase["awaterpouch"] );
DawnInterface.giveItemToPlayer( itemDatabase["awaterpouch"] );
DawnInterface.giveItemToPlayer( itemDatabase["awaterpouch"] );
--note: this is just for debug the items need to be copied not accessed directly else the same reference is used!!!

dofile( "data/quests_wood.lua" );
