if ( arinoxGeneralShop == nil )
then
	arinoxGeneralShop = {};
	dofile("data/arinoxGeneralShop.spawnpoints.lua");
	arinoxGeneralShop.leavePoint = DawnInterface.addInteractionPoint();
	arinoxGeneralShop.leavePoint:setPosition( -160, -94, 80, 80 );
	arinoxGeneralShop.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	arinoxGeneralShop.leavePoint:setInteractionType( InteractionType.Zone );
	arinoxGeneralShop.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/zone1", 747, 1530 );\nDawnInterface.setSavingAllowed( true );' );

	trader = DawnInterface.addMobSpawnPoint( "Human", -344, 180, 1, 0 );
	trader:setAttitude( Attitude.FRIENDLY );
	trader:setName( "Rake Fleetwood" );
	traderInteraction = DawnInterface.addCharacterInteractionPoint( trader );
	traderInteraction:setInteractionType( InteractionType.Shop );
	traderInteraction:setInteractionCode( "arinoxGeneralShop.onActivateTrader()" );
	traderShop = DawnInterface.addShop();
	traderShop:addItem( itemDatabase["leynorscap"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["bladeofstrength"] );
	traderShop:addItem( itemDatabase["bookofleatherskinrank2"] );
end

function arinoxGeneralShop.onEnterMap(x,y)
	local textWindow = DawnInterface.createTextWindow();
	textWindow:center();
	textWindow:setText( "Arinox general shop" );
	textWindow:setAutocloseTime( 1000 );
end

function arinoxGeneralShop.onActivateTrader()
	traderShop:toggle()
end
