if ( arinoxMagesGuild == nil )
then
	arinoxMagesGuild = {};
	dofile("data/arinoxMagesGuild.spawnpoints.lua");
	arinoxMagesGuild.leavePoint = DawnInterface.addInteractionPoint();
	arinoxMagesGuild.leavePoint:setPosition( -160, -94, 80, 80 );
	arinoxMagesGuild.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	arinoxMagesGuild.leavePoint:setInteractionType( InteractionType.Zone );
	arinoxMagesGuild.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/zone1", 430, 2020 );\nDawnInterface.setSavingAllowed( true );' );

	arinoxMagesGuild.trader = DawnInterface.addMobSpawnPoint( "Human", -344, 180, 1, 0 );
	arinoxMagesGuild.trader:setAttitude( Attitude.FRIENDLY );
	arinoxMagesGuild.trader:setName( "Rake Fleetwood" );
	arinoxMagesGuild.traderInteraction = DawnInterface.addCharacterInteractionPoint( arinoxMagesGuild.trader );
	arinoxMagesGuild.traderInteraction:setInteractionType( InteractionType.Shop );
	arinoxMagesGuild.traderInteraction:setInteractionCode( "arinoxMagesGuild.onActivateTrader()" );
	arinoxMagesGuild.traderShop = DawnInterface.addShop();
	arinoxMagesGuild.traderShop:addItem( itemDatabase["leynorscap"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["bladeofstrength"] );
	arinoxMagesGuild.traderShop:addItem( itemDatabase["bookofleatherskinrank2"] );
end

function arinoxMagesGuild.onEnterMap(x,y)
	local textWindow = DawnInterface.createTextWindow();
	textWindow:setPosition( PositionType.CENTER, 512, 382 );
	textWindow:setText( "Arinox mage guild" );
	textWindow:setAutocloseTime( 1000 );
end

function arinoxMagesGuild.onActivateTrader()
	arinoxMagesGuild.traderShop:toggle()
end
