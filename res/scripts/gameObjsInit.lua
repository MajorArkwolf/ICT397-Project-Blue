-- Initialise the physics system, and prepare it for use

---------Variables
EnemiesLeft = 0;
DifficultyMultiplier = getDifficulty() + 1;
HasOpenedExitScreen = false;



---------------------Physics Set up------------------------------
InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();
local sphereShape = shapeFactory:createSphere(1);
local capsuleShape = shapeFactory:createCapsule(1.5,3);
local bulletShape = shapeFactory:createSphere(0.4);
local bulletShapeCollision = shapeFactory:createSphere(1);
local capsuleShape_npc = shapeFactory:createCapsule(3,7);
local treeShape = shapeFactory:createBox(vector(1,20,1));
local rockShape = shapeFactory:createBox(vector(3,3,3));
-------------------------------------------------------------------

---------------------Player Setup------------------------------------------
-- Set up player game object
gameObj_raw = GameObject.create(GameObject.Types.Player());
gameObj_raw = GameObject.getPlayer();
gameObj_raw.model = resources.getModel("res/model/ball.fbx");
-- Set up player dynamics
position = vector(0,200,0);
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
collisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(gameObj_raw.physBody));
rigidBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0), 10);
collisionBody:AddCollisionShape(shapeFactory:GetShape(sphereShape), vector(0,0,0), quaternion(1,0,0,0));
rigidBody:SetBounciness(0);
--Create character attributes used for character
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
gameObj_charData:status_assign("Jetpack", 500);
gameObj_charData:status_assign("UsingJetpack", 0);
------------------------------------------------------------------

----------------Misc Object setup-------------------------------------------------------

for i = 0, 100, 1 do
	identifier = GameObject.create(GameObject.Types.Static());
	new_game_object = GameObject.get(identifier);
	local name = "res/model/vikings/SM_Env_Rock_01.fbx";
	new_game_object.model = resources.getModel(name);
	new_game_object.scale = vector(0.05, 0.05, 0.05);
	local x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local y = TerrainFactory.heightAt(x, z);

	local objectRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(new_game_object.physBody));
	objectRigidBody:SetPosition(vector(x, y, z));
	objectRigidBody:AddCollisionShape(shapeFactory:GetShape(rockShape), vector(0,0,0), quaternion(1,0,0,0), 5);

end

local sandHeight = 110;
local dirtHeight = 150;
for i = 0, 1000, 1 do
	identifier = GameObject.create(GameObject.Types.Static());
	new_game_object = GameObject.get(identifier);
	local name = "res/model/vikings/SM_Env_Tree_Pine_0" .. math.random(1, 4) .. ".fbx";
	new_game_object.model = resources.getModel(name);
	local x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local y = 0;
	while ( y < sandHeight or y > dirtHeight)
	do
		x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
		z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
		y = TerrainFactory.heightAt(x, z);
	end
	local objectRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(new_game_object.physBody));
	objectRigidBody:SetPosition(vector(x, y - 3, z));
	objectRigidBody:AddCollisionShape(shapeFactory:GetShape(treeShape), vector(0,0,0), quaternion(1,0,0,0), 5);
	local scale = 0.1;
	new_game_object.scale = vector(scale, scale, scale);
end

------------------------Bullet setup-------------------------------------------
BulletID = GameObject.create(GameObject.Types.NPC());
BulletObject = GameObject.get(BulletID);
BulletObject.scale = vector(0.5, 0.5, 0.5)
BulletCharData = GameObject.to_character(BulletObject);
BulletCharData:status_assign("Projectile", 1)
BulletCharData:status_assign("Damage", 25)
BulletObject.model = resources.getModel("res/model/throwingstar.obj");
BulletRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(BulletObject.physBody));
BulletCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(BulletObject.physBody));
BulletRigidBody:AddCollisionShape(shapeFactory:GetShape(bulletShape), vector(0,0,0), quaternion(1,0,0,0), 5);
BulletCollisionBody:AddCollisionShape(shapeFactory:GetShape(bulletShapeCollision), vector(0,0,0), quaternion(1,0,0,0));
-----------------------------------------------------------------------------------
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
for i = 0, 25 * DifficultyMultiplier, 1 do
	-- Create a GameObject and store the returned identifier
	local npc_id = GameObject.create(GameObject.Types.NPC());

	-- Gather the actual GameObject
	local npc_gameObj_raw = GameObject.get(npc_id);
	-- Configure the model, animator and scale
	npc_gameObj_raw.model = resources.getModel("res/model/ClothedMan.gltf");
	npc_gameObj_raw:anim_init();
	npc_gameObj_raw.scale = vector(1, 1, 1);

	local npc_gameObj_char = GameObject.to_character(npc_gameObj_raw);
	local npc_gameObj_npc = GameObject.to_npc(npc_gameObj_char);



	-- Configure the NPC to be in a random position surrounding the player's spawning location
	local position = vector(math.random(0 - npcSpawningRegion, npcSpawningRegion), 0, math.random(0 - npcSpawningRegion, npcSpawningRegion));
	position.y = getHeightAt(position.x, position.z) + 0.1;
	dynamicsWorld:GetRigidBody(npc_gameObj_raw.physBody):SetPosition(position);

	-- Set the NPC's rigid body collision shape and stop the NPC from being affected by gravity
	local npc_rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(npc_gameObj_raw.physBody));
	local npc_collisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(npc_gameObj_raw.physBody));
	npc_rigidBody:AddCollisionShape(shapeFactory:GetShape(capsuleShape_npc), vector(0,0,0), quaternion(1,0,0,0), 1);
	npc_collisionBody:AddCollisionShape(shapeFactory:GetShape(capsuleShape_npc), vector(0,0,0), quaternion(1,0,0,0));
	npc_rigidBody:SetAngularDamping(1);
	npc_rigidBody:SetSleeping(true);

	-- Make the NPC have a randomly variant offset of time before they start to wander
	npc_gameObj_char:status_assign("Wander_ActionTime", math.random(-8.0, 2.0));

	-- Assign a starting health value to the NPC
	npc_gameObj_char:status_assign("Health", 100);
	npc_gameObj_char:status_assign("Enemy", 1);

	-- Assign the NPC's speed
	npc_gameObj_char:status_assign("Wander_WalkSpeed", 4);
	npc_gameObj_char:status_assign("Chase_RunSpeed",8);
    npc_gameObj_char:status_assign("NPC_RangeScale", 2);

	-- Set up the NPC's initial AI FSM States
	local npc_ai = FSM.get(npc_gameObj_npc.context);
	npc_ai:stateLocal_setRegular(FSM.State.Wander());
	npc_ai:stateGlobal_setCustom("NPC_catchIfDead", "NPC_catchIfDead", "NPC_catchIfDead", "NPC_catchIfDead");
end
print("Finished generating the AIs");

-----------------------------------Boundary Wall Setup--------------------------------------------------
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
--------------------------------------------------------------------------------------------------------------




-- Syncronise the physics of the GameObjects after configuring them
GameObject.syncPhys();
player = GameObject.getPlayer();
