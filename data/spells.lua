-- ==== Dynamic values ====
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

-- ==== Spell ranks ====
-- When creating a spell, it automatically becomes rank 1.
-- To create rank X of this spell, use DawnInterface.copySpell( spellDatabase["name_of_spell"] );
-- Example:
-- curSpell = DawnInterface.copySpell( spellDatabase["magicmissile"] );
-- spellDatabase["magicmissilerank2"] = curSpell;
-- curSpell:setRank( 2 );
-- curSpell:setDirectDamage( 12, 18, ElementType.Light );
--
-- It's possible to alter most of the properties of a spell in another rank.

-- ==== Character States ====
-- To set character states to an effect we use setCharacterState( CharacterStates::CharacterStates );
--
-- Following CharacterStates are available:
--
--	Channeling
--	Charmed
--	Confused
--	Feared
--	Invisible
--	Mesmerized
--	Movementspeed
--	SeeInvisible
--	SeeSneaking
--	Sneaking
--	Stunned

-- === Other notes ===
-- % needs to be written with %%. So 50%% will be displayed in the tooltips as: "50%" 

spellDatabase = {};

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["magicmissile"] = curSpell;
curSpell:setName("Magic Missile");
curSpell:setInfo("A magical missile causing %minSpellDirectDamage%-%maxSpellDirectDamage% points of light damage to the target");
curSpell:setCastTime( 1000 );
curSpell:setSpellCost( 10 );
curSpell:setSoundSpellCasting( "data/sound/spellcast.ogg" );
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
curSpell:setContinuousDamage( 4, 6, 10000, ElementType.Earth );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["venomspit"] = curSpell;
curSpell:setName("Venomspit");
curSpell:setDamageBonus( 1.0 );
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 0 );
curSpell:setSoundSpellStart( "data/spells/venomspit/venomspit.ogg" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/venomspit/0.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:addAdditionalSpellOnTarget( spellDatabase["venomspiteffect1"], 0.05 );
curSpell:setRequiredClass( CharacterClass.Ranger );

curSpell = DawnInterface.createGeneralRayDamageSpell();
spellDatabase["electrocute"] = curSpell;
curSpell:setName("Electrocute");
curSpell:setInfo("Electrocutes the target with %minSpellDirectDamage%-%maxSpellDirectDamage% point of air damage +  %minSpellContinuousDamage%-%maxSpellContinuousDamage% air damage over 2 seconds.");
curSpell:setCastTime( 5000 );
curSpell:setCooldown( 5 );
curSpell:setSpellCost( 50 );
curSpell:setSoundSpellCasting( "data/sound/spellcast.ogg" );
curSpell:setDirectDamage(  50, 100, ElementType.Air );
curSpell:setContinuousDamage( 10, 20, 2000, ElementType.Air );
curSpell:setSpellSymbol( "data/spells/electrocute/symbol.tga" );
curSpell:setSoundSpellStart( "data/spells/lightning/lightning.ogg" );
curSpell:setNumAnimations( 5 );
curSpell:setAnimationTexture( 0, "data/spells/lightning/1.tga" );
curSpell:setAnimationTexture( 1, "data/spells/lightning/2.tga" );
curSpell:setAnimationTexture( 2, "data/spells/lightning/3.tga" );
curSpell:setAnimationTexture( 3, "data/spells/lightning/4.tga" );
curSpell:setAnimationTexture( 4, "data/spells/lightning/5.tga" );
curSpell:setRequiredClass( CharacterClass.Liche );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralAreaDamageSpell();
spellDatabase["inferno"] = curSpell;
curSpell:setName("Inferno");
curSpell:setInfo("Burns the target with %minSpellDirectDamage%-%maxSpellDirectDamage% point of fire damage + %minSpellContinuousDamage%-%maxSpellContinuousDamage% fire damage over 5 seconds.");
curSpell:setCastTime( 2000 );
curSpell:setCooldown( 5 );
curSpell:setSpellCost( 75 );
curSpell:setDirectDamage(  15, 30, ElementType.Fire );
curSpell:setContinuousDamage( 4, 7, 5000, ElementType.Fire );
curSpell:setSpellSymbol( "data/spells/inferno/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/inferno/inferno.tga" );
curSpell:setRadius( 120 );
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
spellDatabase["steelgrip"] = curSpell;
curSpell:setName("Steelgrip");
curSpell:setInfo("Slams against your shield causing your blood to boil, increasing strength by 5.");
curSpell:setStats( StatsType.Strength, 5 );
curSpell:setCastTime( 0 );
curSpell:setSpellCost( 0 );
curSpell:setSpellSymbol( "data/spells/shieldbash/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setDuration( 30 );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

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
curSpell:setRequiredClass( CharacterClass.Ranger );

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
curSpell:setSpellCost( 0 );
curSpell:setSpellSymbol( "data/spells/mightofthetitan/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setRequiredClass( CharacterClass.Warrior );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["flowingthought"] = curSpell;
curSpell:setName("Flowing thought");
curSpell:setStats( StatsType.ManaRegen, 5 );
curSpell:setDuration( 3 );
curSpell:setInfo("Clears your mind, regenerating 15 mana over 3 seconds.");
curSpell:setCastTime( 0 );
curSpell:setSpellSymbol( "data/spells/vortex/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

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
spellDatabase["spiderbite"] = curSpell;
curSpell:setName("Spiderbite");
curSpell:setDamageBonus( 1.0 );
curSpell:setCooldown( 2 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 0 );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["wolfbite"] = curSpell;
curSpell:setName("Wolfbite");
curSpell:setDamageBonus( 1.0 );
curSpell:setCooldown( 2 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 0 );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );
curSpell = DawnInterface.createMeleeDamageAction();

spellDatabase["melee"] = curSpell;
curSpell:setName("Melee");
curSpell:setDamageBonus( 1.0 );
curSpell:setCooldown( 2 );
curSpell:setSpellSymbol( "data/spells/melee/symbol.tga" );
curSpell:setSpellCost( 0 );
curSpell:setSoundSpellStart( "data/spells/melee/melee_swing.ogg" );
curSpell:setSoundSpellHit( "data/spells/melee/melee_hit.ogg" );
curSpell:setInfo("Attack with your weapon, causing %minWeaponDamage%-%maxWeaponDamage% damage.");
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["phantomstrike"] = curSpell;
curSpell:setName("Phantom strike");
curSpell:setDamageBonus( 4.0 );
curSpell:setCooldown( 12 );
curSpell:setInfo("Devastating strike, causing %minWeaponDamage% to %maxWeaponDamage% damage.");
curSpell:setSpellSymbol( "data/spells/phantomstrike/symbol.tga" );
curSpell:setSpellCost( 50 );
curSpell:setRequiredClass( CharacterClass.Warrior );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["venomweaveeffect2"] = curSpell;
curSpell:setName("Venomweave");
curSpell:setInfo("Spiderweb entangled your entire body, rendering you unable to act or move!");
curSpell:setCharacterState( CharacterStates.Stunned );
curSpell:setDuration( 5 );
curSpell:setSpellSymbol( "data/spells/venomweave/symbol.tga" );

curSpell = DawnInterface.createGeneralRayDamageSpell();
spellDatabase["venomweaveeffect1"] = curSpell;
curSpell:setName("Venomweave");
curSpell:setSpellSymbol( "data/spells/venomspit/symbol.tga" );
curSpell:setContinuousDamage( 4, 6, 3000, ElementType.Earth );
curSpell:addAdditionalSpellOnTarget( spellDatabase["venomweaveeffect2"], 0.1 );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["venomweave"] = curSpell;
curSpell:setName("Venomweave");
curSpell:setDamageBonus( 2.0 );
curSpell:setCooldown( 4 );
curSpell:setSpellSymbol( "data/spells/venomweave/symbol.tga" );
curSpell:setSpellCost( 25 );
curSpell:addAdditionalSpellOnTarget( spellDatabase["venomweaveeffect1"], 0.75 );
curSpell:setRequiredClass( CharacterClass.Warrior );

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
curSpell:setSoundSpellStart( "data/spells/rabidbite/rabidbite.ogg" );
curSpell:addAdditionalSpellOnTarget( spellDatabase["rabies"], 0.05 );
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
curSpell:addAdditionalSpellOnCreator( spellDatabase["lungeeffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Warrior );
curSpell:addRequiredWeapon( WeaponType.ONEHAND_SWORD );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["shieldbasheffect1"] = curSpell;
curSpell:setName("Shield bash");
curSpell:setCharacterState( CharacterStates.Stunned );
curSpell:setDuration( 3 );
curSpell:setSpellSymbol( "data/spells/shieldbash/symbol.tga" );

curSpell = DawnInterface.createMeleeDamageAction();
spellDatabase["shieldbash"] = curSpell;
curSpell:setName("Shield bash");
curSpell:setDamageBonus( 1.2 );
curSpell:setCooldown( 12 );
curSpell:setSpellSymbol( "data/spells/shieldbash/symbol.tga" );
curSpell:setSpellCost( 40 );
curSpell:setInfo("Bash with your shield, causing %minWeaponDamage% to %maxWeaponDamage% and stunning your enemy for 3 seconds.");
curSpell:addAdditionalSpellOnTarget( spellDatabase["shieldbasheffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Warrior );
curSpell:addRequiredWeapon( WeaponType.SHIELD ); 

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["shoot"] = curSpell;
curSpell:setName("Shoot");
curSpell:setInfo("Shoot with your ranged weapon, causing %minWeaponDamage%-%maxWeaponDamage% damage.");
curSpell:setDamageBonus( 1.0 );
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 0 );
curSpell:setSpellSymbol( "data/spells/shoot/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/shoot/0.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:setRequiredClass( CharacterClass.Ranger );
curSpell:setSoundSpellStart( "data/spells/shoot/shoot.ogg" );
curSpell:addRequiredWeapon( WeaponType.BOW );
curSpell:addRequiredWeapon( WeaponType.CROSSBOW );
curSpell:addRequiredWeapon( WeaponType.SLINGSHOT );

-- add this spell to players spellbook
DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["invisibility"] = curSpell;
curSpell:setName("Invisibility");
curSpell:setDuration( 12 );
curSpell:setInfo("Granting you invisibility, making you undetectable by most enemies.");
curSpell:setSpellCost( 50 );
curSpell:setCastTime( 1000 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setRequiredClass( CharacterClass.NOCLASS );
curSpell:setCharacterState( CharacterStates.Invisible );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["sneak"] = curSpell;
curSpell:setName("Sneak");
curSpell:setDuration( 30 );
curSpell:setInfo("Hiding in shadows and sneaking allows you to go undetected from most enemies.");
curSpell:setSpellCost( 50 );
curSpell:setCastTime( 1000 );
curSpell:setSpellSymbol( "data/spells/healing/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setRequiredClass( CharacterClass.NOCLASS );
curSpell:setCharacterState( CharacterStates.Sneaking );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["terrifyeffect2"] = curSpell;
curSpell:setName("Terrify");
curSpell:setCastTime( 0 );
curSpell:setDuration( 60 );
curSpell:setSpellCost( 0 );
curSpell:setResistElementModifierPoints( ElementType.Dark, -10 );
curSpell:setSpellSymbol( "data/spells/terrify/symbol.tga" );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["terrifyeffect1"] = curSpell;
curSpell:setName("Terrify");
curSpell:setCharacterState( CharacterStates.Feared );
curSpell:setDuration( 4 );
curSpell:setSpellSymbol( "data/spells/terrify/symbol.tga" );
curSpell:addAdditionalSpellOnTarget( spellDatabase["terrifyeffect2"], 1.0 );

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["terrify"] = curSpell;
curSpell:setName("Terrify");
curSpell:setCooldown( 30 );
curSpell:setDirectDamage( 20, 30, ElementType.Dark );
curSpell:setCastTime( 1500 );
curSpell:setSpellSymbol( "data/spells/terrify/symbol.tga" );
curSpell:setSpellCost( 40 );
curSpell:setSoundSpellStart( "data/spells/terrify/terrify.ogg" );
curSpell:setInfo("Sends a dark soul of the Umbral'un to terrorize the target dealing %minSpellDirectDamage%-%maxSpellDirectDamage% damage and causing it to flee for a short period. When the soul leaves it curses the target, reducing Dark magic resistance for a minute.");
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/terrify/0.tga" );
curSpell:setMoveSpeed( 650 );
curSpell:addAdditionalSpellOnTarget( spellDatabase["terrifyeffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Liche );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["food"] = curSpell;
curSpell:setName("Food");
curSpell:setStats( StatsType.HealthRegen, 10 );
curSpell:setDuration( 18 );
curSpell:setInfo("Increases health regeneration by 10 while eating.");
curSpell:setSpellSymbol( "data/spells/food/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setCharacterState( CharacterStates.Channeling );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

curSpell = DawnInterface.copySpell( spellDatabase["food"] );
spellDatabase["foodrank2"] = curSpell;
curSpell:setRank( 2 );
curSpell:setStats( StatsType.HealthRegen, 15 );
curSpell:setInfo("Increases health regeneration by 15 while eating.");
curSpell:setRequiredLevel( 3 );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["drink"] = curSpell;
curSpell:setName("Drink");
curSpell:setStats( StatsType.ManaRegen, 15 );
curSpell:setDuration( 18 );
curSpell:setInfo("Increases mana regeneration by 15 while drinking.");
curSpell:setSpellSymbol( "data/spells/food/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setCharacterState( CharacterStates.Channeling );
curSpell:setRequiredClass( CharacterClass.ANYCLASS );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["frozenshoteffect1"] = curSpell;
curSpell:setName("Frozen shot ef");
curSpell:setDuration( 12 );
curSpell:setSpellSymbol( "data/spells/frozenshot/symbol.tga" );
curSpell:setCharacterState( CharacterStates.Movementspeed, 0.5 );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["frozenshot"] = curSpell;
curSpell:setName("Frozen shot");
curSpell:setInfo("Launches a frozen projectile, causing %minWeaponDamage%-%maxWeaponDamage% damage and slowing the target's movementspeed by 50%% for 12 seconds.");
curSpell:setDamageBonus( 2.0 );
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 25 );
curSpell:setSpellSymbol( "data/spells/frozenshot/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setCooldown( 18 );
curSpell:setAnimationTexture( 0, "data/spells/shoot/0.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:setRequiredClass( CharacterClass.Ranger );
curSpell:addRequiredWeapon( WeaponType.BOW );
curSpell:addRequiredWeapon( WeaponType.CROSSBOW );
curSpell:addRequiredWeapon( WeaponType.SLINGSHOT );
curSpell:addAdditionalSpellOnTarget( spellDatabase["frozenshoteffect1"], 1.0 );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["pindowneffect1"] = curSpell;
curSpell:setName("Pin down ef");
curSpell:setDuration( 5 );
curSpell:setSpellSymbol( "data/spells/pindown/symbol.tga" );
curSpell:setCharacterState( CharacterStates.Movementspeed, 0.0 );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["pindown"] = curSpell;
curSpell:setName("Pin down");
curSpell:setInfo("Skillfully pins down your target with your missile causing them to be immobilized for 5 seconds and causing %minWeaponDamage%-%maxWeaponDamage% damage.");
curSpell:setDamageBonus( 0.5 );
curSpell:setCastTime( 500 );
curSpell:setSpellCost( 10 );
curSpell:setCooldown( 14 );
curSpell:setSpellSymbol( "data/spells/pindown/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/shoot/0.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:setRequiredClass( CharacterClass.Ranger );
curSpell:addRequiredWeapon( WeaponType.BOW );
curSpell:addRequiredWeapon( WeaponType.CROSSBOW );
curSpell:addRequiredWeapon( WeaponType.SLINGSHOT );
curSpell:addAdditionalSpellOnTarget( spellDatabase["pindowneffect1"], 1.0 );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBoltDamageSpell();
spellDatabase["flamingarroweffect1"] = curSpell;
curSpell:setName("Flaming arrow ef");
curSpell:setSpellSymbol( "data/spells/frozenshot/symbol.tga" );
curSpell:setNumAnimations( 0 );
curSpell:setInstant( true );
curSpell:setDirectDamage( 15, 30, ElementType.Earth );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["flamingarrow"] = curSpell;
curSpell:setName("Flaming arrow");
curSpell:setInfo("Launching a projectile imbued with the fire of Angyr. Causing %minWeaponDamage%-%maxWeaponDamage% + 15-30 earth magic damage.");
curSpell:setDamageBonus( 1 );
curSpell:setCastTime( 1500 );
curSpell:setSpellCost( 20 );
curSpell:setCooldown( 5 );
curSpell:setSoundSpellStart( "data/spells/flamingarrow/flamingarrow.ogg" );
curSpell:setSpellSymbol( "data/spells/flamingarrow/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/shoot/0.tga" );
curSpell:setMoveSpeed( 1000 );
curSpell:setRequiredClass( CharacterClass.Ranger );
curSpell:addRequiredWeapon( WeaponType.BOW );
curSpell:addRequiredWeapon( WeaponType.CROSSBOW );
curSpell:addRequiredWeapon( WeaponType.SLINGSHOT );
curSpell:addAdditionalSpellOnTarget( spellDatabase["flamingarroweffect1"], 1.0 );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["landyrsforce"] = curSpell;
curSpell:setName("Landyr's force");
curSpell:setInfo("Carefully aiming and striking with Landyr's force causing %minWeaponDamage%-%maxWeaponDamage% damage.");
curSpell:setDamageBonus( 4.0 );
curSpell:setCastTime( 4000 );
curSpell:setSpellCost( 35 );
curSpell:setSpellSymbol( "data/spells/landyrsforce/symbol.tga" );
curSpell:setNumAnimations( 1 );
curSpell:setCooldown( 24 );
curSpell:setAnimationTexture( 0, "data/spells/shoot/0.tga" );
curSpell:setMoveSpeed( 1200 );
curSpell:setRequiredClass( CharacterClass.Ranger );
curSpell:addRequiredWeapon( WeaponType.BOW );
curSpell:addRequiredWeapon( WeaponType.CROSSBOW );
curSpell:addRequiredWeapon( WeaponType.SLINGSHOT );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["voiceoftheforest"] = curSpell;
curSpell:setName("Voice of the forest");
curSpell:setStats( StatsType.MeleeCritical, 5 );
curSpell:setStats( StatsType.Dexterity, 15 );
curSpell:setDuration( 180 );
curSpell:setInfo("The spirits of the forest imbues your body, increasing your melee critical strike chance and dexterity.");
curSpell:setCastTime( 2000 );
curSpell:setSpellSymbol( "data/spells/voiceoftheforest/symbol.tga" );
curSpell:setEffectType( EffectType.SelfAffectingSpell );
curSpell:setRequiredClass( CharacterClass.Ranger );

DawnInterface.inscribeSpellInPlayerSpellbook( curSpell );

curSpell = DawnInterface.createGeneralBuffSpell();
spellDatabase["sylphiricacideffect1"] = curSpell;
curSpell:setName("Terrify");
curSpell:setCharacterState( CharacterStates.Feared );
curSpell:setDuration( 4 );
curSpell:setSpellSymbol( "data/spells/terrify/symbol.tga" );

curSpell = DawnInterface.createRangedDamageAction();
spellDatabase["sylphiricacid"] = curSpell;
curSpell:setName("Sylphiric Acid");
curSpell:setInfo("Burning acid sphews over the victim, causing agonizing pain and sometimes inflicts terror in the victim.");
curSpell:setDamageBonus( 2.5 );
curSpell:setCastTime( 2000 );
curSpell:setSpellCost( 35 );
curSpell:setSoundSpellStart( "data/spells/venomspit/venomspit.ogg" );
curSpell:setNumAnimations( 1 );
curSpell:setAnimationTexture( 0, "data/spells/venomspit/0.tga" );
curSpell:setMoveSpeed( 600 );
curSpell:setSpellSymbol( "data/spells/landyrsforce/symbol.tga" );
curSpell:setCooldown( 12 );
curSpell:addAdditionalSpellOnTarget( spellDatabase["sylphiricacideffect1"], 1.0 );
curSpell:setRequiredClass( CharacterClass.Ranger );
