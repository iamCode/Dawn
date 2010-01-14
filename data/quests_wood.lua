
john = DawnInterface.addInteractionPoint();
john:setPosition( 500, 100, 32, 48 );
john:setBackgroundTexture( "data/character/link/link1.tga" );
john:setInteractionTexture( "data/spells/healing/symbol.tga" );
john:setInteractionCode( "onActivateJohn()" );

function onActivateJohn()
	DawnInterface.removeInteractionPoint( john );
	james = DawnInterface.addInteractionPoint();
	james:setPosition( 700, 100, 32, 48 );
	james:setBackgroundTexture( "data/character/link/link2.tga" );
	james:setInteractionTexture( "data/spells/healother/symbol.tga" );
	james:setInteractionCode( "DawnInterface.removeInteractionPoint( james );" );
end

