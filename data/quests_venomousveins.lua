-- init quest namespace so different quests / zones don't conflict in names
if( quest_venomousveins == nil )
then
  quest_venomousveins = {}
end

function quest_venomousveins.init()
  -- this quest is initialized from zone zone1
  quest_venomousveins.effreyLongback = DawnInterface.addMobSpawnPoint( "Human", -1510, 500, 1, 0 );
  quest_venomousveins.effreyLongback:setAttitude( Attitude.FRIENDLY );
  quest_venomousveins.effreyLongback:setWanderRadius( 50 );
  quest_venomousveins.effreyLongback:setName( "Effrey Longback" );
  quest_venomousveins.effreyLongbackInteraction = DawnInterface.addCharacterInteractionPoint( quest_venomousveins.effreyLongback );
  quest_venomousveins.effreyLongbackInteraction:setInteractionType( InteractionType.Quest );
  quest_venomousveins.effreyLongbackInteraction:setInteractionCode( "quest_venomousveins.speakWithEffrey()" );

  quest_venomousveins.jemma = DawnInterface.addMobSpawnPoint( "Witch", -2162, -4580, 1, 0 );
  quest_venomousveins.jemma:setAttitude( Attitude.FRIENDLY );
  quest_venomousveins.jemma:setWanderRadius( 50 );
  quest_venomousveins.jemma:setName( "Jemma" );
  quest_venomousveins.jemmaInteraction = DawnInterface.addCharacterInteractionPoint( quest_venomousveins.jemma );
  quest_venomousveins.jemmaInteraction:setInteractionType( InteractionType.Quest );
  quest_venomousveins.jemmaInteraction:setInteractionCode( "quest_venomousveins.speakWithJemma()" );

  local sylphirwoodsEnter = DawnInterface.addInteractionRegion();
  sylphirwoodsEnter:setPosition( -1215, -1000, 100, 360 );
  sylphirwoodsEnter:setOnEnterText( "quest_venomousveins.enterWoods()" );
end

function quest_venomousveins.enterWoods()
  local textWindow = DawnInterface.createTextWindow();
  textWindow:setPosition( PositionType.CENTER, 512, 382 );
  textWindow:setText( "The Sylphir woods." );
  textWindow:setAutocloseTime( 1000 );
end

function quest_venomousveins.speakWithJemma()
  if( quest_venomousveins.quest_one and not quest_venomousveins.gotAntidote ) then
    if( not quest_venomousveins.completed and not quest_venomousveins.gotAntidote ) then
      if( quest_venomousveins.added == true and quest_venomousveins.completed == false and quest_venomousveins.gotInstructionFromJemma == false ) then
        quest_venomousveins.showJemmaText( 2 );
        quest_venomousveins.gotInstructionFromJemma = true;
        quest_venomousveins.quest_one:setDescription( "Jemma requires two fangs from the small spiderlings and three pristine spidersilks from the Webweaves in order to make an antidote." );
        quest_venomousveins.quest_one:addRequiredItemForCompletion( itemDatabase["pristinesylphirsilk"], 3 );
        quest_venomousveins.quest_one:addRequiredItemForCompletion( itemDatabase["sylphirfang"], 2 );
      elseif( quest_venomousveins.added == true and quest_venomousveins.completed == false and quest_venomousveins.gotInstructionFromJemma == true ) then
        quest_venomousveins.showJemmaText( 4 );
      end
    end

    -- try to finish the quest if possible.
    if( quest_venomousveins.quest_one:finishQuest() == true ) then
      quest_venomousveins.quest_one = nil;
      quest_venomousveins.gotAntidote = true;
      quest_venomousveins.showJemmaText( 5 );
      quest_venomousveins.quest_two = DawnInterface.addQuest( "Sylphir antidote", "Deliver the antidote to Effrey's daughter before it's too late!" );
      quest_venomousveins.quest_two:addRequiredItemForCompletion( itemDatabase["sylphirantidote"], 1 );
      quest_venomousveins.quest_two:setExperienceReward( 350 );
      quest_venomousveins.quest_two:setItemReward( itemDatabase["ringofdefense"] );
    end
  else
    quest_venomousveins.showJemmaText( 1 );
  end
end


function quest_venomousveins.speakWithEffrey()
  if( quest_venomousveins.quest_two ) then
    if( quest_venomousveins.quest_two:finishQuest() == true ) then
      quest_venomousveins.quest_two = nil;
      quest_venomousveins.completed = true;
      quest_venomousveins.showJeffreyText( 4 );
    end
  end

  if( not quest_venomousveins.completed ) then
    if( quest_venomousveins.added == nil ) then
      quest_venomousveins.added = true;
      quest_venomousveins.completed = false;
      quest_venomousveins.gotReward = false;
      quest_venomousveins.gotAntidote = false;
      quest_venomousveins.gotInstructionFromJemma = false;
      quest_venomousveins.quest_one = DawnInterface.addQuest( "Venomous veins", "Effrey Longback's daughter was bitten by a Sylphir spider. Search out Jemma the alchemist in the southern part of the Sylphir woods and obtain an antidote for Effrey." );
      quest_venomousveins.quest_one:setItemReward( itemDatabase["sylphirantidote"] );
      quest_venomousveins.showJeffreyText( 1 );
    elseif( quest_venomousveins.added == true and quest_venomousveins.completed == false and quest_venomousveins.gotAntidote == false ) then
      quest_venomousveins.showJeffreyText( 3 );
    end
  end
end

function quest_venomousveins.showJeffreyText( part )
  if( part == 1 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "My daughter was bitten by a spider this morning. She is really sick and I am fearing the worst. I don't know if she went playing near the Sylphir woods... She knows it's forbidden! It's only getting worse and if I don't get an antidote to cure her I don't know what I will do. I have heard about an alchemist named Jemma in the southern part of the Sylphir woods. I would go myself but I cannot leave my little girl. You look like you could make it to Jemma's house unharmed." );
    textWindow:setAutocloseTime( 0 );
    textWindow:setOnCloseText( "quest_venomousveins.showJeffreyText( 2 )" );
  end

  if( part == 2 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "Could you visit Jemma and bring me back an antidote? I'm no rich man, but I do have some pieces of equipment I could trade in return for the antidote. Please hurry!" );
    textWindow:setAutocloseTime( 0 );
  end

  if( part == 3 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "Please seek out Jemma down in the southern part of the Sylphir woods. My daugher is really sick!" );
    textWindow:setAutocloseTime( 0 );
  end

  if( part == 4 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "Thank you so much brave one! You have saved my daughters life! I know I can't repay you for this, but here.. take this armor. Does more use with you than with me." );
    textWindow:setAutocloseTime( 0 );
  end
end

function quest_venomousveins.showJemmaText( part )
  if( part == 1 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "I'm Jemma. Not many people dare to wander down here due to the spiders around. Don't you know these woods are dangerous? Sylphirs are growing stronger these days. Beware of the small ones. They may not look tough, but they can give you quite a bite..." );
    textWindow:setAutocloseTime( 7000 );
  end

  if( part == 2 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "Someone got bitten? Well, you shouldn't wander out in the woods unless you are prepared to face off against those pesky spiders. Lucky for you I know just what you need... " );
    textWindow:setAutocloseTime( 0 );
    textWindow:setOnCloseText( "quest_venomousveins.showJemmaText( 3 )" );
  end

  if( part == 3 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "To make this antidote I will require two fangs from the small spiderlings. Also, three pristine spidersilks from the Webweavers. Bring me this and I have enough to make your antidote. We can discuss my fee when you return." );
    textWindow:setAutocloseTime( 0 );
  end

  if( part == 4 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "How is the gathering coming along? Remember, I need spidersilks in pristine condition and two spiderling fangs!" );
    textWindow:setAutocloseTime( 0 );
  end

  if( part == 5 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "Excellent! I hope it wasn't too much trouble getting all this." );
    textWindow:setAutocloseTime( 0 );
    textWindow:setOnCloseText( "quest_venomousveins.showJemmaText( 6 )" );
  end

  if( part == 6 ) then
    local textWindow = DawnInterface.createTextWindow();
    textWindow:setPosition( PositionType.CENTER, 512, 382 );
    textWindow:setText( "I have already finished the potion in the waiting of your arrival. You better hurry up, you might not have that much time left. Now remember, you are in my debt. I will call upon you to do me a favor once the time is right." );
    textWindow:setAutocloseTime( 0 );
  end
end

-- init quest if this has not been done yet
if( quest_venomousveins.inited == nil ) then
  quest_venomousveins.inited = true;
  quest_venomousveins.init();
end
