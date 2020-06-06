InitialisePhysics();
physManager = PhysicsManager:GetInstance();
shapeFactory = physManager:GetReactShapeFactory();
collisionWorld = physManager:GetCollisionWorld();
dynamicsWorld = physManager:GetDynamicsWorld();

sphereShape = shapeFactory:createSphere(1);
capsuleShape = shapeFactory:createCapsule(1,3);

-- Load the GameObject Lua Reporting Library functions from script
dofile("res/scripts/gameObjsReporting.lua");

-- Load the GameObject Lua debugging script
dofile("res/scripts/gameObjsTesting.lua");
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
