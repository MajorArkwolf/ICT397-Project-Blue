-- Generate 15 new GameObjects
local i = 0;
while (i < 15)
do
	-- Generate the new GameObject (of type Static)
	identifier = GameObject_Manager.add(1);
	new_game_object = GameObject_Manager.get(identifier);

	-- Set the newly created GameObject's position and model
	new_game_object:setModel("res/model/player_male.obj");
	new_game_object:setPos_X(i * 5);

	-- Increment the counter to prevent infinite GameObject generation
	i = i + 1;
end
