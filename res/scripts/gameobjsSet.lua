-- Generate 15 new GameObjects
local i = 0;
local sandHeight = 110;
local dirtHeight = 150;
while (i < 15)
do
	-- Generate the new GameObject (of type Static)
	identifier = GameObject_Manager.add(1);
	new_game_object = GameObject_Manager.get(identifier);

	-- Set the newly created GameObject's model

	new_game_object:setModel("res/model/ball.obj");


	-- Configure the newly created GameObject's position
	local x = i * 5;
	local z = 0;
	local y = TerrainFactory.heightAt(x, z);
	new_game_object:setPos(x, y, z);

	-- Configure the newly created GameObject's scale
	new_game_object:setScale(1.5, 1.5, 1.5);

	-- Increment the counter to prevent infinite GameObject generation
	i = i + 1;
end
i = 0;
while (i < 100)
do
	identifier = GameObject_Manager.add(1);
	new_game_object = GameObject_Manager.get(identifier);
	local name = "res/model/vikings/SM_Env_Rock_0" .. math.random(1, 7) .. ".fbx";
	new_game_object:setModel(name);
	local x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local y = TerrainFactory.heightAt(x, z);
	new_game_object:setPos(x, y, z);
	new_game_object:setScale(0.05, 0.05, 0.05);
	i = i + 1;
end

i = 0;
while (i < 100)
do
	identifier = GameObject_Manager.add(1);
	new_game_object = GameObject_Manager.get(identifier);
	local name = "res/model/vikings/SM_Env_Tree_Pine_0" .. math.random(1, 4) .. ".fbx";
	new_game_object:setModel(name);
	local x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local y = 0;
	while ( y < sandHeight or y > dirtHeight)
	do
		x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
		z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
		y = TerrainFactory.heightAt(x, z);
	end
	new_game_object:setPos(x, y, z);
	local scale = 0.01 * math.random(1, 5);
	new_game_object:setScale(scale, scale, scale);
	i = i + 1;
end

i = 0;
while (i < 100)
do
	identifier = GameObject_Manager.add(1);
	new_game_object = GameObject_Manager.get(identifier);
	local name = "res/model/vikings/SM_Env_Tree_Pine_Large_0" .. math.random(1, 3) .. ".fbx";
	new_game_object:setModel(name);
	local x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
	local y = 0;
	while ( y < sandHeight or y > dirtHeight)
	do
		x = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
		z = math.random(TerrainFactory.chunkSize * -1, TerrainFactory.chunkSize);
		y = TerrainFactory.heightAt(x, z);
	end
	new_game_object:setPos(x, y, z);
	local scale = 0.01 * math.random(1, 2);
	new_game_object:setScale(scale, scale, scale);
	i = i + 1;
end
