spellDatabase = {};

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["magicmissile"] = curSpell;
curSpell:setName("Magic Missile");
curSpell:setInfo("A magical missile causing 6-10 points of light damage to the target");
curSpell:setCastTime( 1000 );
curSpell:setManaCost( 10 );
curSpell:setDirectDamage(  6, 10, ElementType.Light );
curSpell:setSpellSymbol( "data/spells/magicmissile/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/magicmissile/magicmissile.tga" );
curSpell:setMoveSpeed( 500 );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBarDamageSpell();
spellDatabase["electrocute"] = curSpell;
curSpell:setName("Electrocute");
curSpell:setInfo("Electrocutes the target with 50-100 point of air damage + 10-20 points per second for 2 seconds.");
curSpell:setCastTime( 5000 );
curSpell:setManaCost( 50 );
curSpell:setDirectDamage(  50, 100, ElementType.Air );
curSpell:setContinuousDamage( 10, 20, 2000, ElementType.Air );
curSpell:setSpellSymbol( "data/spells/lightning/symbol.tga" );
curSpell:setNumAnimations( 5 );
curSpell:setAnimationTexture( 0, "data/spells/lightning/1.tga" );
curSpell:setAnimationTexture( 1, "data/spells/lightning/2.tga" );
curSpell:setAnimationTexture( 2, "data/spells/lightning/3.tga" );
curSpell:setAnimationTexture( 3, "data/spells/lightning/4.tga" );
curSpell:setAnimationTexture( 4, "data/spells/lightning/5.tga" );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["lightningbolt"] = curSpell;
curSpell:setName("Lightning Bolt");
curSpell:setInfo("A bolt of raw lightning aimed at the target causing 20-40 points of lightning damage.");
curSpell:setCastTime( 1500 );
curSpell:setManaCost( 25 );
curSpell:setDirectDamage(  20, 40, ElementType.Air );
--curSpell:setContinuousDamage( 10, 20, 2000, ElementType.Dark );
curSpell:setSpellSymbol( "data/spells/lightning/symbol.tga" );
curSpell:setNumAnimations( 5 );
curSpell:setAnimationTexture( 0, "data/spells/lightning/1.tga" );
curSpell:setAnimationTexture( 1, "data/spells/lightning/2.tga" );
curSpell:setAnimationTexture( 2, "data/spells/lightning/3.tga" );
curSpell:setAnimationTexture( 3, "data/spells/lightning/4.tga" );
curSpell:setAnimationTexture( 4, "data/spells/lightning/5.tga" );
curSpell:setMoveSpeed( 1000 );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

