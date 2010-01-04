newSpell = DawnInterface.createGeneralDamageSpell();

newSpell:setCastTime( 5000 );
newSpell:setManaCost( 25 );
newSpell:setDirectDamage(  50, 100, ElementType.Light );
newSpell:setContinuousDamage( 10, 20, 2000, ElementType.Dark );

newSpell:setName("Demonstration");
newSpell:setInfo("Some new spell for demonstration");

newSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
newSpell:setNumAnimations( 1 );
newSpell:setAnimationTexture( 0, "data/spells/magicmissile/magicmissile.tga" );

