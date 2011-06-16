local state = TestInterface.getDawnState();

-- Dawn's states:
-- 0 - NoState
-- 1 - MainMenu
-- 2 - ChooseClass
-- 3 - LoadingScreen
-- 4 - OptionsMenu
-- 5 - InGame

-- wait until we get to the MainMenu
while true do
    state = TestInterface.getDawnState();
    if state == 1 then
        break
    end
end

-- we're in the Main Menu, now click on choose class
TestInterface.clickOnNewGame();

-- wait until we get to the choose class screen
while true do
    state = TestInterface.getDawnState();
    if state == 2 then
        break
    end
end

-- we're in the choose class screen, pick a class
TestInterface.chooseClass( CharacterClass.Liche );

-- wait until we get inside the game
while true do
    state = TestInterface.getDawnState();
    if state == 5 then
        break
    end
end

-- we're in the game, exit Dawn
TestInterface.quitDawn(0);