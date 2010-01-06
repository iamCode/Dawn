spellDatabase = {};

spellDatabase["demonstration"] = DawnInterface.createGeneralDamageSpell();
curSpell = spellDatabase["demonstration"];
curSpell:setName("Demonstration");
curSpell:setInfo("Some new spell for demonstration");
curSpell:setCastTime( 5000 );
curSpell:setManaCost( 25 );
curSpell:setDirectDamage(  50, 100, ElementType.Light );
curSpell:setContinuousDamage( 10, 20, 2000, ElementType.Dark );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/magicmissile/magicmissile.tga" );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

