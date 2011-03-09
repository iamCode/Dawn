function saveGlobals( t )
	for name, value in pairs(_G)
	do
		t[name] = 1
	end
end

function printValue( surroundingName, varname, value )
	local prefix=''
	if ( surroundingName )
	then
		prefix=surroundingName..'.'
	end

	if ( value == nil )
	then
		io.write( prefix..varname..'='..'nil'..'\n' )
	elseif ( type(value) == "number" )
	then
		io.write( prefix..varname..'='..value..'\n' )
	elseif ( type(value) == "boolean" )
	then
		if ( value == true )
		then
			io.write( prefix..varname..'='..'true'..'\n' )
		else
			io.write( prefix..varname..'='..'false'..'\n' )
		end
	elseif ( type(value) == "string" )
	then
		io.write( prefix..varname..'='..'"'..value..'"'..'\n' )
	elseif ( type(value) == "table" )
	then
		io.write( prefix..varname..'='..'{}'..'\n' )
		-- all variables in tables/namespaces with name DontSave are not saved. This allows for some temporary data
		if ( varname ~= "DontSave" )
		then
			for innervarname,innervalue in pairs(value) 
			do 
				printValue(prefix..varname, innervarname, innervalue )
			end
		end
	elseif ( type(value) == "userdata" )
	then
		local restoreString = DawnInterface.getItemReferenceRestore( value );
		io.write( prefix..varname.."="..restoreString..'\n' );
	end
end

function saveGame( fileprefix )
	print( "saving lua game data to " .. fileprefix..'.lua' )
	local oldOut = io.output()
	io.output( fileprefix..'.lua' )
	-- save all zones (needed for variable lookups on user types)
	io.write( DawnInterface.getAllZonesSaveText() );

	for varname,value in pairs(_G) 
	do 
		if ( not initialGlobals[varname] )
		then
			printValue(nil,varname,value)
		end
	end
	io.write( DawnInterface.getQuestSaveText() );
	io.write( DawnInterface.getInventorySaveText() );
	local player = DawnInterface.getPlayer();
	io.write( player:getSaveText() );
	io.write( DawnInterface.getSpellbookSaveText() );
	io.write( DawnInterface.getActionbarSaveText() );
	io.write( DawnInterface.getReenterCurrentZoneText() );
	local saveAllowedBoolText = "false";
	if ( DawnInterface.isSavingAllowed() )
	then
		saveAllowedBoolText = "true";
	end
	io.write( "DawnInterface.setSavingAllowed( " .. saveAllowedBoolText .. " );\n" );
	-- map = LuaInterface.getCurrentMap()
	-- io.write( 'LuaInterface.enterMap( "',map:getFileName(),'", 3, 3 )' )
	io.close()
	io.output( oldOut )
end

function reinitGlobalsRecursive( surroundingName, varname, value )
	local prefix=''
	if ( surroundingName )
	then
		prefix=surroundingName..'.'
	end

	if ( value == nil )
	then
		return true
	elseif ( type(value) == "table" )
	then
		haveOnlyNil = true
		for innervarname,innervalue in pairs(value)
		do
			if ( reinitGlobalsRecursive(prefix..varname, innervarname, innervalue) == false )
			then
				haveOnlyNil = false;
			end
		end
		if ( haveOnlyNil )
		then
			value = nil;
			return true;
		end
	else
		_G[''..prefix..varname..'']=nil
	end
	return false;
end

function loadGame( fileprefix )
	print( "loading lua game data from " .. fileprefix..'.lua' )
	for varname,value in pairs(_G) 
	do 
		if ( not initialGlobals[varname] )
		then
			_G[''..varname..'']=nil
		end
	end
	dofile( fileprefix..'.lua' )	
end

initialGlobals = {}
saveGlobals( initialGlobals )

