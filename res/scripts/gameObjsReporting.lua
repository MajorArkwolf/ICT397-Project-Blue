-- Takes a GameObject_Type and turns it into a Lua string
function GameObject_StringifyType(gameObjType_in)
	-- A table can be used as a relatively efficient 'switch-case' control flow tool
	local switch = {
		[GameObject.Types.Invalid()] = "Invalid",
		[GameObject.Types.Static()] = "Static",
		[GameObject.Types.Item()] = "Item",
		[GameObject.Types.Player()] = "Player",
		[GameObject.Types.NPC()] = "NPC"
	}

	-- Return the output from the table lookup (default is nil)
	return switch[gameObjType_in];
end;

-- Outputs the GameObject's npc details to the screen
function GameObject_ReportNPC(gameObj_in)
	-- Catch an invalid GameObject
	if (gameObj_in == nil) then
		print("Not a GameObject_NPC! Stopping report...");
		return;
	end;

	-- Print the GameObject's FSM Context ID
	print("FSM Context ID: " .. gameObj_in.context);
end;

-- Outputs the GameObject's character details to the screen
function GameObject_ReportCharacter(gameObj_in)
	-- Catch an invalid GameObject
	if (gameObj_in == nil) then
		print("Not a GameObject_Character! Stopping report...");
		return;
	end;
		
	-- Keep track of the GameObject's status keys and expected statuses
	local keys_table = gameObj_in:status_list();
	local keys_expected = gameObj_in:status_count();

	-- Check if the table size matches the claimed amount of statuses
	if (keys_expected ~= #keys_table) then
		print("Unexpected amount of status keys returned!");
		print("Expected " .. keys_expected .. ", got " .. #keys_table .. "! Stopping report...");
		return;
	end;

	-- Print the amount of expected statuses for the GameObject
	print("Amount of Statuses: " .. keys_expected);

	-- Iterate through the statuses, and print their key and value pairs
	local keys_iterator;
	local keys_string;
	for keys_iterator, keys_string in pairs(keys_table) do
		-- Print the key and its status value
		print(" \"" .. keys_string .. "\": " .. gameObj_in:status_get(keys_string));
	end;

	-- Attempt to gather the GameObject's npc data and report it
	GameObject_ReportNPC(GameObject.to_npc(gameObj_in));
end;

-- Outputs the GameObject's base details to the screen
function GameObject_Report(gameObj_in)
	-- Catch an invalid GameObject
	if (gameObj_in == nil) then
		print("Not a GameObject_Base! Stopping report...");
		return;
	end;

	-- Print the GameObject's identifier
	print("GameObject ID: " .. gameObj_in.id);

	-- Print the GameObject's type
	print("GameObject Type: " .. GameObject_StringifyType(gameObj_in.type));

	-- Print the GameObject's Physics Body ID
	print("GameObject PhysBody ID: " .. gameObj_in.physBody);

	-- Print the GameObject's Model ID
	print("Model ID: " .. gameObj_in.model);

	-- Attempt to gather the GameObject's character data and report it
	GameObject_ReportCharacter(GameObject.to_character(gameObj_in));
end;
