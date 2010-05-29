spellDatabase = {};

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["magicmissile"] = curSpell;
curSpell:setName("Magic Missile");
curSpell:setInfo("A magical missile causing 6-10 points of light damage to the target");
curSpell:setCastTime( 1000 );
curSpell:setSpellCost( 10 );
curSpell:setDirectDamage(  6, 10, ElementType.Light );
curSpell:setSpellSymbol( "data/spells/magicmissile/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/magicmissile/magicmissile.tga" );
curSpell:setMoveSpeed( 500 );

curSpell = DawnInterface.createGeneralRayDamageSpell();
spellDatabase["electrocute"] = curSpell;
curSpell:setName("Electrocute");
curSpell:setInfo("Electrocutes the target with 50-100 point of air damage + 10-20 points per second for 2 seconds.");
curSpell:setCastTime( 5000 );
curSpell:setCooldown( 5 );
curSpell:setSpellCost( 50 );
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
curSpell:setSpellCost( 25 );
curSpell:setDirectDamage(  20, 40, ElementType.Air );
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

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["healing"] = curSpell;
curSpell:setName("Healing");
curSpell:setInfo("Heals 50 points of damage by heavenly light on self.");
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 30 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDirectHealing( 50, 50, ElementType.Light );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["forcedhealing"] = curSpell;
curSpell:setName("Forced Healing");
curSpell:setInfo("Heals 50-70 points of damage by dark magic on target.");
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 40 );
curSpell:setSpellSymbol( "data/spells/healother/symbol.tga" );
curSpell:setEffectType( EffectType.SingleTargetSpell );
curSpell:setDirectHealing( 50, 70, ElementType.Dark );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["hymnofrestoration"] = curSpell;
curSpell:setName("Hymn of restoration");
curSpell:setInfo("Heals you for 120-180 points of damage over 12 seconds.");
curSpell:setCastTime( 500 );
curSpell:setSpellCost( 25 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setCooldown( 30 );
curSpell:setContinuousHealing( 10, 15, 12000, ElementType.Light );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["leatherskin"] = curSpell;
curSpell:setName("Leatherskin");
curSpell:setInfo("Encoats your skin with leather, increasing armor by 80.");
curSpell:setStats( StatsType.Armor, 80 );
curSpell:setCastTime( 2500 );
curSpell:setSpellCost( 75 );
curSpell:setSpellSymbol( "data/spells/leatherskin/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDuration( 300 );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["spiritoftheboar"] = curSpell;
curSpell:setName("Spirit of the Boar");
curSpell:setInfo("Embraces you with the spirit of the boar, increasing vitality by 5.");
curSpell:setStats( StatsType.Vitality, 5 );
curSpell:setCastTime( 0 );
curSpell:setSpellCost( 0 );
curSpell:setSpellSymbol( "data/spells/leatherskin/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDuration( 600 );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["layingofhands"] = curSpell;
curSpell:setName("Laying of hands");
curSpell:setInfo("Instantly heals you for 500 points of damage.");
curSpell:setCastTime( 0 );
curSpell:setCooldown( 600 );
curSpell:setSpellCost( 10 );
curSpell:setSpellSymbol( "data/spells/layingofhands/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDirectHealing( 500, 500, ElementType.Light );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );


curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["smallhealingpotion"] = curSpell;
curSpell:setName("Small healing potion");
curSpell:setInfo("Heals 10-25 points of damage on self.");
curSpell:setCastTime( 0 );
curSpell:setSpellCost( 0 );
curSpell:setCooldown( 120 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDirectHealing( 10, 25, ElementType.Light );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["callingofthegrave"] = curSpell;
curSpell:setName("Calling of the grave");
curSpell:setSpellEffectElementModifierPoints( ElementType.Dark, 25 );
curSpell:setDuration( 600 );
curSpell:setInfo("The ancient tombs of Ark'li engulfs you, increasing Dark spell damage.");
curSpell:setCastTime( 4000 );
curSpell:setSpellCost( 100 );
curSpell:setSpellSymbol( "data/spells/callingofthegrave/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["mightofthetitan"] = curSpell;
curSpell:setName("Might of the Titan");
curSpell:setStats( StatsType.Strength, 15 );
curSpell:setDuration( 600 );
curSpell:setInfo("Calls for the power of the Titans, increasing your strength.");
curSpell:setCastTime( 1000 );
curSpell:setSpellCost( 25 );
curSpell:setSpellSymbol( "data/spells/mightofthetitan/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["manavortex"] = curSpell;
curSpell:setName("Mana Vortex");
curSpell:setStats( StatsType.ManaRegen, 10 );
curSpell:setDuration( 15 );
curSpell:setInfo("Expanding your mind with a vortex of knowledge, increasing mana regen rate.");
curSpell:setCastTime( 500 );
curSpell:setCooldown( 120 );
curSpell:setSpellSymbol( "data/spells/vortex/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["earthenseeds"] = curSpell;
curSpell:setName("Earthen Seeds");
curSpell:setStats( StatsType.HealthRegen, 3 );
curSpell:setDuration( 180 );
curSpell:setInfo("Seeds in the earth increases your health regen.");
curSpell:setSpellCost( 75 );
curSpell:setCastTime( 2000 );
curSpell:setSpellSymbol( "data/spells/earthenseeds/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["melee"] = curSpell;
curSpell:setName("Melee");
curSpell:setDamageBonus( 1.0 );
curSpell:setCooldown( 2 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 0 );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["phantomstrike"] = curSpell;
curSpell:setName("Phantom strike");
curSpell:setDamageBonus( 4.0 );
curSpell:setCooldown( 12 );
curSpell:setSpellSymbol( "data/spells/earthenseeds/symbol.tga" );
curSpell:setSpellCost( 50 );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

