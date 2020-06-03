InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();

sphereShape = shapeFactory:createSphere(1);
capsuleShape = shapeFactory:createCapsule(1,3);

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

-- Outputs the GameObject's character details to the screen
function GameObject_ReportCharacter(character_data)
	-- Check if the provided GameObject Character data is valid
	if (not character_data:is_valid()) then
		-- Catch the invalid data, report it, and stop
		print("No valid GameObject Character data found! Stopping report...");
		return;
	end;
	
	-- Catch if the GameObject should have the FSM system
	if (character_data:type() == GameObject.Types.NPC()) then
		-- Print the GameObject's FSM Context ID
		print("FSM Context ID: " .. character_data:npc_context());
	end;
		
	-- Keep track of the GameObject's status keys and expected statuses
	local keys_table = character_data:status_list();
	local keys_expected = character_data:status_count();

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
		print(" \"" .. keys_string .. "\": " .. character_data:status_get(keys_string));
	end;
end;

-- Outputs the GameObject's base details to the screen
function GameObject_Report(gameObj_in)
	-- Catch an invalid GameObject
	if (gameObj_in == nil) then
		print("Caught nil GameObject!");
		return;
	end;

	-- Print the GameObject's identifier
	print("GameObject ID: " .. gameObj_in:id());

	-- Print the GameObject's type
	print("GameObject Type: " .. GameObject_StringifyType(gameObj_in:type()));

	-- Print the GameObject's Physics Body ID
	print("GameObject PhysBody ID: " .. gameObj_in.physBody);

	-- Print the GameObject's Model ID
	print("Model ID: " .. gameObj_in.model);

	-- Attempt to gather the GameObject's character data and report it
	GameObject_ReportCharacter(GameObject.charData(gameObj_in:id()));
end;

--[[ Testing an Invalid GameObject
print("----------------------------");
print(" Invalid GameObject Example ");
print("----------------------------");

-- Create a GameObject and store the returned identifier
local gameObj_id = GameObject.create(GameObject.Types.Invalid());

-- Gather the actual GameObject
local gameObj_raw = GameObject.get(gameObj_id);

-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);

-- Testing a Static GameObject
print("\n---------------------------");
print(" Static GameObject Example ");
print("---------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.Static());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);

-- Testing a Item GameObject
print("\n-------------------------");
print(" Item GameObject Example ");
print("-------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.Item());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);
--]]
-- Testing a Player GameObject
print("\n---------------------------");
print(" Player GameObject Example ");
print("---------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.Player());
print(gameObj_id)
-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

position = vector(0,200,0);
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(capsuleShape), vector(0,0,0), quaternion(1,0,0,0), 1);
rigidBody:SetBounciness(0);
rigidBody:SetAngularDamping(1);
rigidBody:SetRollingResistance(1);

-- Gather the GameObject's Character data and configure it
local gameObj_charData = GameObject.charData(gameObj_raw:id());
gameObj_charData:status_assign("Health", 100);
gameObj_charData:status_assign("Stamina", 50);
gameObj_charData:status_assign("Charisma", -5);
gameObj_charData:status_assign("Lives", 10);
gameObj_charData:status_delete("Lives");

-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);

-- Testing a NPC GameObject
print("\n------------------------");
print(" NPC GameObject Example ");
print("------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.NPC());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

-- Gather the GameObject's Character data and configure it
gameObj_charData = GameObject.charData(gameObj_raw:id());
gameObj_charData:status_assign("ThisCanBeAnyNameYouWant", 80);
gameObj_charData:status_assign("AnyValueCanBeAssignedToStatuses", 50);
gameObj_charData:status_clear();
gameObj_charData:status_assign("Health", 40);
gameObj_charData:status_assign("Difficulty", 10);




-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);

--[[
for i = 0, 200, 1 do
-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.NPC());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");
position = vector(5,200,20);
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 1);
end
]]--
-- Syncronise the physics of the GameObjects after configuring them
GameObject.syncPhys();
