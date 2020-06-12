-- Debugging
print("difficulty " .. getDifficulty());

-- Initialise the physics system, and prepare it for use
InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();
local sphereShape = shapeFactory:createSphere(1);
local capsuleShape = shapeFactory:createCapsule(1.5,3);
local capsuleShape_npc = shapeFactory:createCapsule(0.5,1);

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.create(GameObject.Types.Player());
gameObj_raw = GameObject.getPlayer();
gameObj_raw.model = resources.getModel("res/model/ball.fbx");
position = vector(0,200,0);
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
collisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 10);
collisionBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0));
rigidBody:SetBounciness(0);

-- Create character attributes used for moving
gameObj_charData = GameObject.to_character(gameObj_raw);
gameObj_charData:status_assign("UseDynamics", 0);
gameObj_charData:status_assign("MoveForward", 0);
gameObj_charData:status_assign("MoveBackward", 0);
gameObj_charData:status_assign("MoveLeft", 0);
gameObj_charData:status_assign("MoveRight", 0);
gameObj_charData:status_assign("Sliding", 0);
gameObj_charData:status_assign("FreeCam", 0);
gameObj_charData:status_assign("Oxygen", 1000);
gameObj_charData:status_assign("Health", 100);

-- Ensure randomness by setting the seed relative to the current time and removing any starting bias
math.randomseed(os.time());
math.random();

-- Get the environment's playable size
local npcSpawningRegion = getMapSize();
npcSpawningRegion = npcSpawningRegion / 4;
npcSpawningRegion = npcSpawningRegion - 100;

-- The function to use for the NPC's Global State behaviours
NPC_catchIfDead = function(npc_raw)
	-- Make sure you have access to the character specific properties
	local npc_char = GameObject.to_character(npc_raw);

	-- Catch if the NPC has died
	if ((npc_char:status_get("Health") < 0) or (npc_char:status_get("Health") == 0)) then
		-- Make sure you have access to the NPC specific properties
		local npc_npc = GameObject.to_npc(npc_char);

		-- Set the NPC's State to die
		local npc_ai = FSM.get(npc_npc.context);
		npc_ai:stateLocal_setRegular(FSM.State.Die());
	end
end

-- Generate 50 NPCs
for i = 0, 50, 1 do
	-- Create a GameObject and store the returned identifier
	local npc_id = GameObject.create(GameObject.Types.NPC());

	-- Gather the actual GameObject
	local npc_gameObj_raw = GameObject.get(npc_id);
	local npc_gameObj_char = GameObject.to_character(npc_gameObj_raw);
	local npc_gameObj_npc = GameObject.to_npc(npc_gameObj_char);

	-- Configure the model, animator and scale
	npc_gameObj_raw.model = resources.getModel("res/model/ClothedMan.gltf");
	npc_gameObj_raw:anim_init();
	npc_gameObj_raw.scale = vector(0.15, 0.15, 0.15);

	-- Configure the NPC to be in a random position surrounding the player's spawning location
	local position = vector(math.random(0 - npcSpawningRegion, npcSpawningRegion), 0, math.random(0 - npcSpawningRegion, npcSpawningRegion));
	position.y = getHeightAt(position.x, position.z) + 0.1;
	dynamicsWorld:GetRigidBody(npc_gameObj_raw.physBody):SetPosition(position);

	-- Set the NPC's rigid body collision shape and stop the NPC from being affected by gravity
	local npc_rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(npc_gameObj_raw.physBody));
	npc_rigidBody:AddCollisionShape(shapeFactory:GetShape(capsuleShape_npc), vector(0,0,0), quaternion(1,0,0,0), 1);
	npc_rigidBody:SetAngularDamping(1);
	npc_rigidBody:SetSleeping(true);

	-- Make the NPC have a randomly variant offset of time before they start to wander
	npc_gameObj_char:status_assign("Wander_ActionTime", math.random(-8.0, 2.0));

	-- Assign a starting health value to the NPC
	npc_gameObj_char:status_assign("Health", 100);

	-- Set up the NPC's initial AI FSM States
	local npc_ai = FSM.get(npc_gameObj_npc.context);
	npc_ai:stateLocal_setRegular(FSM.State.Wander());
	npc_ai:stateGlobal_setCustom("NPC_catchIfDead", "NPC_catchIfDead", "NPC_catchIfDead", "NPC_catchIfDead");
end

print("Finished generating the AIs");

-- Create a GameObject and store the returned identifier
BoundingWallID = GameObject.create(GameObject.Types.Static());
local BoundingWall = GameObject.get(BoundingWallID);

-- Generate the shapes for the GameObject's physics
local wallXShape = shapeFactory:createBox(vector(2500,500, 100));
local wallZShape = shapeFactory:createBox(vector(100,500, 2500));

-- Gather the GameObject's physics objects
local BoundingWallCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(BoundingWall.physBody));
local BoundingWallRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(BoundingWall.physBody));

-- Configure the GameObject's physics objects
BoundingWallCollisionBody:AddCollisionShape(shapeFactory:GetShape(wallXShape), vector(0,0,1900), quaternion(1,0,0,0));
BoundingWallCollisionBody:AddCollisionShape(shapeFactory:GetShape(wallXShape), vector(0,0,-1900), quaternion(1,0,0,0));
BoundingWallCollisionBody:AddCollisionShape(shapeFactory:GetShape(wallZShape), vector(1900,0,0), quaternion(1,0,0,0));
BoundingWallCollisionBody:AddCollisionShape(shapeFactory:GetShape(wallZShape), vector(-1900,0,0), quaternion(1,0,0,0)); 
BoundingWallRigidBody:AddCollisionShape(shapeFactory:GetShape(wallXShape), vector(0,0,1900), quaternion(1,0,0,0), 1);
BoundingWallRigidBody:AddCollisionShape(shapeFactory:GetShape(wallXShape), vector(0,0,-1900), quaternion(1,0,0,0), 1);
BoundingWallRigidBody:AddCollisionShape(shapeFactory:GetShape(wallZShape), vector(1900,0,0), quaternion(1,0,0,0), 1);
BoundingWallRigidBody:AddCollisionShape(shapeFactory:GetShape(wallZShape), vector(-1900,0,0), quaternion(1,0,0,0), 1);

-- Syncronise the physics of the GameObjects after configuring them
GameObject.syncPhys();
player = GameObject.getPlayer();
