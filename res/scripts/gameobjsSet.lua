-- Attempt to create and add a GameObject
gameObjID = GameObject_Manager.add(1);
exampleObj = GameObject_Manager.get(gameObjID);

-- If the GameObject creation was successful
if (exampleObj.isValid()) {
	-- Print the GameObject's identifier
	print(exampleObj.getUniqueID());

	-- Set the GameObject's model and position
	exampleObj.setModel("res/model/player_male.obj");
	exampleObj.setPos_Y(150);
}
