InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();


local sphereShape = shapeFactory:createSphere(1);
local capsuleShape = shapeFactory:createCapsule(1.5,3);

-- Load the GameObject Lua Reporting Library functions from script
--dofile("res/scripts/gameObjsReporting.lua");

-- Load the GameObject Lua debugging script
--dofile("res/scripts/gameObjsTesting.lua");


-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.getPlayer();
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

position = vector(0,200,0);
print(gameObj_raw.model)
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 10);

rigidBody:SetBounciness(0);

gameObj_charData = GameObject.to_character(gameObj_raw);

--Create character attributes used for moving
gameObj_charData:status_assign("UseDynamics", 0);
gameObj_charData:status_assign("MoveForward", 0);
gameObj_charData:status_assign("MoveBackward", 0);
gameObj_charData:status_assign("MoveLeft", 0);
gameObj_charData:status_assign("MoveRight", 0);
gameObj_charData:status_assign("Sliding", 0);
gameObj_charData:status_assign("FreeCam", 0);



for i = 0, 20, 1 do
	-- Create a GameObject and store the returned identifier
	gameObj_id = GameObject.create(GameObject.Types.NPC());

	-- Gather the actual GameObject
	local gameObj_raw = GameObject.get(gameObj_id);
	local gameObj_char = GameObject.to_character(gameObj_raw);
	local gameObj_npc = GameObject.to_npc(gameObj_char);

	-- Configure the model, animator and scale
	gameObj_raw.model = resources.getModel("res/model/ClothedMan.gltf");
	gameObj_raw:anim_init();
	gameObj_raw.scale = vector(0.5, 0.5, 0.5);

	-- Configure the position
	local position = vector(5,200,20);
	dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);

	-- Set the rigid body's collision shape
	local rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
	rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 1);

	-- Set up the initial AI FSM State
	local npc_ai = FSM.get(gameObj_npc.context);
	npc_ai:stateLocal_setRegular(FSM.State.Wander());
end

-- Syncronise the physics of the GameObjects after configuring them
GameObject.syncPhys();
player = GameObject.getPlayer();

