-- Note about dynamic values for the speltooltip.
-- Dynamic values can be set here. In the setInfo function, you can use these values that will be displayed in the game:
--"%minWeaponDamage%"
--"%maxWeaponDamage%"
--"%minSpellDirectDamage%"
--"%maxSpellDirectDamage%"
--"%minSpellContinuousDamage%"
--"%maxSpellContinuousDamage%"
--"%minDirectHealing%"
--"%maxDirectHealing%"
--"%minContinuousHealing%"
--"%maxContinuousHealing%"

-- Spell ranks --
-- When creating a spell, it automatically becomes rank 1.
-- To create rank X of this spell, use DawnInterface.copySpell( spellDatabase["name_of_spell"] );
-- Example:
-- curSpell = DawnInterface.copySpell( spellDatabase["magicmissile"] );
-- spellDatabase["magicmissilerank2"] = curSpell;
-- curSpell:setRank( 2 );
-- curSpell:setDirectDamage( 12, 18, ElementType.Light );
--
-- It's possible to alter most of the properties of a spell in another rank.

spellDatabase = {};

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["magicmissile"] = curSpell;
curSpell:setName("Magic Missile");
curSpell:setInfo("A magical missile causing %minSpellDirectDamage%-%maxSpellDirectDamage% points of light damage to the target");
curSpell:setCastTime( 1000 );
curSpell:setSpellCost( 10 );
curSpell:setDirectDamage(  6, 10, ElementType.Light );
curSpell:setSpellSymbol( "data/spells/magicmissile/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/magicmissile/magicmissile.tga" );
curSpell:setMoveSpeed( 500 );
curSpell:setRequiredClass( CharacterClass.Liche );
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.copySpell( spellDatabase["magicmissile"] );
spellDatabase["magicmissilerank2"] = curSpell;
curSpell:setDirectDamage( 12, 18, ElementType.Light );
curSpell:setRank( 2 );
curSpell:setRequiredLevel( 3 );
curSpell:setSpellCost( 17 );

curSpell = DawnInterface.createGeneralRayDamageSpell();
spellDatabase["venomspiteffect1"] = curSpell;
curSpell:setName("Venomspit");
curSpell:setSpellSymbol( "data/spells/venomspit/symbol.tga" );
curSpell:setContinuousDamage( 5, 7, 10000, ElementType.Earth );

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["venomspit"] = curSpell;
curSpell:setName("Venomspit");
curSpell:setCastTime( 2500 );
curSpell:setCooldown( 10 );
curSpell:setSpellCost( 50 );
curSpell:setDirectDamage(  10, 20, ElementType.Earth );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/venomspit/0.tga" );
curSpell:setMoveSpeed( 600 );
curSpell:addAdditionalSpell( spellDatabase["venomspiteffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Warrior );

curSpell = DawnInterface.createGeneralRayDamageSpell();
spellDatabase["electrocute"] = curSpell;
curSpell:setName("Electrocute");
curSpell:setInfo("Electrocutes the target with %minSpellDirectDamage%-%maxSpellDirectDamage% point of air damage +  %minSpellContinuousDamage%-%maxSpellContinuousDamage% air damage over 2 seconds.");
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
curSpell:setRequiredClass( CharacterClass.Liche );

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
curSpell:setAnimationTexture( 0, "data/spells/lightning/1_small.tga" );
curSpell:setAnimationTexture( 1, "data/spells/lightning/2_small.tga" );
curSpell:setAnimationTexture( 2, "data/spells/lightning/3_small.tga" );
curSpell:setAnimationTexture( 3, "data/spells/lightning/4_small.tga" );
curSpell:setAnimationTexture( 4, "data/spells/lightning/5_small.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:setRequiredClass( CharacterClass.Liche );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["healing"] = curSpell;
curSpell:setName("Healing");
curSpell:setInfo("Heals %minDirectHealing% points of damage by heavenly light on self.");
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 30 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDirectHealing( 50, 50, ElementType.Light );
curSpell:setRequiredClass( CharacterClass.Liche );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["forcedhealing"] = curSpell;
curSpell:setName("Forced Healing");
curSpell:setInfo("Heals %minDirectHealing%-%maxDirectHealing% points of damage by dark magic on target.");
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 40 );
curSpell:setSpellSymbol( "data/spells/healother/symbol.tga" );
curSpell:setEffectType( EffectType.SingleTargetSpell );
curSpell:setDirectHealing( 50, 70, ElementType.Dark );
curSpell:setRequiredClass( CharacterClass.Liche );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["hymnofrestoration"] = curSpell;
curSpell:setName("Hymn of restoration");
curSpell:setInfo("Heals you for %minContinuousHealing%-%maxContinuousHealing% points of damage over 12 seconds.");
curSpell:setCastTime( 500 );
curSpell:setSpellCost( 25 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setCooldown( 30 );
curSpell:setContinuousHealing( 10, 15, 12000, ElementType.Light );
curSpell:setRequiredClass( CharacterClass.Liche );

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
curSpell:setRequiredClass( CharacterClass.Liche );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.copySpell( spellDatabase["leatherskin"] );
spellDatabase["leatherskinrank2"] = curSpell;
curSpell:setRank( 2 );
curSpell:setStats( StatsType.Armor, 120 );
curSpell:setSpellCost( 125 );
curSpell:setRequiredLevel( 4 );
curSpell:setInfo( "Encoats your skin with leather, increasing armor by 125." );

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
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["layingofhands"] = curSpell;
curSpell:setName("Laying of hands");
curSpell:setInfo("Instantly heals you for %minDirectHealing% points of damage.");
curSpell:setCastTime( 0 );
curSpell:setCooldown( 600 );
curSpell:setSpellCost( 0 );
curSpell:setSpellSymbol( "data/spells/layingofhands/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDirectHealing( 500, 500, ElementType.Light );
curSpell:setRequiredClass( CharacterClass.Warrior );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );


curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["smallhealingpotion"] = curSpell;
curSpell:setName("Small healing potion");
curSpell:setInfo("Heals %minDirectHealing%-%maxDirectHealing% points of damage on self.");
curSpell:setCastTime( 0 );
curSpell:setSpellCost( 0 );
curSpell:setCooldown( 120 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDirectHealing( 10, 25, ElementType.Light );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

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
curSpell:setRequiredClass( CharacterClass.Liche );

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
curSpell:setRequiredClass( CharacterClass.Liche );

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
curSpell:setRequiredClass( CharacterClass.Liche );

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
curSpell:setRequiredClass( CharacterClass.Liche );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["melee"] = curSpell;
curSpell:setName("Melee");
curSpell:setDamageBonus( 1.0 );
curSpell:setCooldown( 2 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 0 );
curSpell:setInfo("Attack with your weapon, causing %minWeaponDamage%-%maxWeaponDamage% damage.");
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["phantomstrike"] = curSpell;
curSpell:setName("Phantom strike");
curSpell:setDamageBonus( 4.0 );
curSpell:setCooldown( 12 );
curSpell:setInfo("Devastating strike, causing %minWeaponDamage% to %maxWeaponDamage% damage.");
curSpell:setSpellSymbol( "data/spells/earthenseeds/symbol.tga" );
curSpell:setSpellCost( 50 );
curSpell:setRequiredClass( CharacterClass.Warrior );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralRayDamageSpell();
spellDatabase["shardsofvenomeffect1"] = curSpell;
curSpell:setName("Shards of Venom");
curSpell:setSpellSymbol( "data/spells/venomspit/symbol.tga" );
curSpell:setContinuousDamage( 4, 6, 12000, ElementType.Earth );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["shardsofvenom"] = curSpell;
curSpell:setName("Shards of Venom");
curSpell:setDamageBonus( 2.0 );
curSpell:setCooldown( 4 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 25 );
curSpell:setInfo("Striking your enemy with a blade coated with venom, causing %minWeaponDamage% to %maxWeaponDamage% damage.");
curSpell:addAdditionalSpell( spellDatabase["shardsofvenomeffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Warrior );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["rabies"] = curSpell;
curSpell:setName("Rabies");
curSpell:setStats( StatsType.HealthRegen, -25 );
curSpell:setStats( StatsType.Vitality, -5 );
curSpell:setDuration( 60 );
curSpell:setInfo("Rabies reducing your health regen and vitality.");
curSpell:setSpellCost( 0 );
curSpell:setCastTime( 0 );
curSpell:setSpellSymbol( "data/spells/earthenseeds/symbol.tga" );
curSpell:setEffectType( EffectType.SingleTargetSpell );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["rabidbite"] = curSpell;
curSpell:setName("Rabid bite");
curSpell:setDamageBonus( 1.5 );
curSpell:setCooldown( 1 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 0 );
curSpell:addAdditionalSpell( spellDatabase["rabies"], 0.05 );
curSpell:setRequiredClass( CharacterClass.Warrior );

curSpell = DawnInterface.createGeneralHealingSpell();
spellDatabase["bandages"] = curSpell;
curSpell:setName("Bandages");
curSpell:setInfo("Bandaging yourself, healing %minContinuousHealing%-%maxContinuousHealing% points of damage over 10 seconds.");
curSpell:setCastTime( 1000 );
curSpell:setSpellCost( 0 );
curSpell:setContinuousHealing( 15, 20, 10000, ElementType.Light );
curSpell:setCooldown( 60 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setRequiredClass( CharacterClass.Warrior );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["lungeeffect1"] = curSpell;
curSpell:setName("Lunge");
curSpell:setStats( StatsType.ParryModifier, 15 );
curSpell:setDuration( 6 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["lunge"] = curSpell;
curSpell:setName("Lunge");
curSpell:setDamageBonus( 1.5 );
curSpell:setCooldown( 12 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 30 );
curSpell:setInfo("Tactical strike, causing %minWeaponDamage% to %maxWeaponDamage% and increasing your parry chance the next 6 seconds.");
curSpell:addAdditionalSpell( spellDatabase["lungeeffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Warrior );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["shoot"] = curSpell;
curSpell:setName("Shoot");
curSpell:setInfo("Shoot with your ranged weapon, causing %minWeaponDamage%-%maxWeaponDamage% damage.");
curSpell:setDamageBonus( 1.0 );
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 0 );
curSpell:setSpellSymbol( "data/spells/magicmissile/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/shoot/0.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:setRequiredClass( CharacterClass.Ranger );
