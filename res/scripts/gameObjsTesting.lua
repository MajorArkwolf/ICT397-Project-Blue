-- Testing an Invalid GameObject
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

-- Testing a Player GameObject
print("\n---------------------------");
print(" Player GameObject Example ");
print("---------------------------");

-- Create a GameObject and store the returned identifier
gameObj_id = GameObject.create(GameObject.Types.Player());

-- Gather the actual GameObject and configure it
gameObj_raw = GameObject.get(gameObj_id);
gameObj_raw.model = resources.getModel("res/model/ball.fbx");

-- Gather the GameObject's Character data and configure it
local gameObj_charData = GameObject.to_character(gameObj_raw);
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
gameObj_raw.model = resources.getModel("res/model/AnimatedHuman.gltf");

-- Gather the GameObject's Character data and configure it
gameObj_charData = GameObject.to_character(gameObj_raw);
gameObj_charData:status_assign("ThisCanBeAnyNameYouWant", 80);
gameObj_charData:status_assign("AnyValueCanBeAssignedToStatuses", 50);
gameObj_charData:status_clear();
gameObj_charData:status_assign("Health", 40);
gameObj_charData:status_assign("Difficulty", 10);
position = vector(0, 200, 0);
dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody)):AddCollisionShape(shapeFactory:GetShape(0), vector(0,0,0), quaternion(1,0,0,0), 10);

-- Output a report on the actual GameObject
GameObject_Report(gameObj_raw);
