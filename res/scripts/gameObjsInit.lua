InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();


local sphereShape = shapeFactory:createSphere(1);
local capsuleShape = shapeFactory:createCapsule(1.5,3);

-- Load the GameObject Lua Reporting Library functions from script
dofile("res/scripts/gameObjsReporting.lua");

-- Load the GameObject Lua debugging script
--dofile("res/scripts/gameObjsTesting.lua");


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

gameObj_charData = GameObject.to_character(gameObj_raw);

--Create character attributes used for moving
gameObj_charData:status_assign("UseDynamics", 0);
gameObj_charData:status_assign("MoveForward", 0);
gameObj_charData:status_assign("MoveBackward", 0);
gameObj_charData:status_assign("MoveLeft", 0);
gameObj_charData:status_assign("MoveRight", 0);
gameObj_charData:status_assign("Sliding", 0);
gameObj_charData:status_assign("FreeCam", 0);
gameObj_charData:status_assign("Oxygen", 1000);
gameObj_charData:status_assign("Health", 100);

--[[

for i = 0, 20, 1 do
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

-- Create a GameObject and store the returned identifier
 BoundingWallID = GameObject.create(GameObject.Types.Static());

local BoundingWall = GameObject.get(BoundingWallID);

local wallXShape = shapeFactory:createBox(vector(2500,500, 100));
local wallZShape = shapeFactory:createBox(vector(100,500, 2500));

local BoundingWallCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(BoundingWall.physBody));
local BoundingWallRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(BoundingWall.physBody));

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

