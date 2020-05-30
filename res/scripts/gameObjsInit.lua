InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();

sphereShape = shapeFactory:createSphere(1)

-- Outputs the GameObject's details to the screen
function GameObject_Report(GameObject_In)
	-- Catch an invalid GameObject
	if (GameObject_In == nil) then
		print("Caught nil GameObject!");
		return;
	end;

	-- Print the GameObject's identifier
	print("GameObject ID: " .. GameObject_In:id());

	-- Print the GameObject's type
	if (GameObject_In:type() == GameObject.Types.Invalid()) then
		print("GameObject Type: Invalid");
	end;
	if (GameObject_In:type() == GameObject.Types.Static()) then
		print("GameObject Type: Static");
	end;
	if (GameObject_In:type() == GameObject.Types.Item()) then
		print("GameObject Type: Item");
	end;
	if (GameObject_In:type() == GameObject.Types.Player()) then
		print("GameObject Type: Player");
	end;
	if (GameObject_In:type() == GameObject.Types.NPC()) then
		print("GameObject Type: NPC");
	end;

	-- Print the GameObject's Physics Body ID
	print("GameObject PhysBody ID: " .. GameObject_In.physBody);

	-- Print the GameObject's Model ID
	print("Model ID: " .. GameObject_In.model);
end;

-- Testing an Invalid GameObject
print("----------------------------");
print(" Invalid GameObject Example ");
print("----------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.Invalid());

-- Gather the actual GameObject
gameObj_raw = GameObject.get(gameObj_id);

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
position = vector(20,200,20);
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 1);

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

-- Testing a Player GameObject
print("\n---------------------------");
print(" Player GameObject Example ");
print("---------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.Player());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);

-- Testing a NPC GameObject
print("\n------------------------");
print(" NPC GameObject Example ");
print("------------------------");

for i = 0, 200, 1
do
gameObj_id = GameObject.create(GameObject.Types.NPC());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");
position = vector(5,200,20);
debug.printVector(math.normaliseVector(position));
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 1);

end


-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);
GameObject.syncPhys();
