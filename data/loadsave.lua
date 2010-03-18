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
		for innervarname,innervalue in pairs(value) 
		do 
			printValue(prefix..varname, innervarname, innervalue )
		end
	end
end

function saveGame( fileprefix )
	print( "saving lua game data to " .. fileprefix..'.lua' )
	local oldOut = io.output()
	io.output( fileprefix..'.lua' )
	for varname,value in pairs(_G) 
	do 
		if ( not initialGlobals[varname] )
		then
			printValue(nil,varname,value)
		end
	end
	-- map = LuaInterface.getCurrentMap()
	-- io.write( 'LuaInterface.enterMap( "',map:getFileName(),'", 3, 3 )' )

	-- TODO: save character values, inventory, monsters, items on floor(s) of all map(s)
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

