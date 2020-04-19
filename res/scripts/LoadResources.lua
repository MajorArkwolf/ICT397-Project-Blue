--LoadResources.lua

--[[ 
Put all text strings in the Strings table and call resources.loadString("stringName")  *after defining the string* to load into the text manager

Strings = {
	WindowTitle = "ProjectBlue",
	HelpMenu = "Do stuff to win"
}
resources.loadString("WindowTitle")
resources.loadString("HelpMenu")

--]]


Strings = {
	WindowTitle = "ProjectBlue",
	OptionMenu_title = "Menu",
	ControlMenu_title = "Controls",
	InstructionMenu_title = "Instructions",
	InstructionMenu_instructions = "Press escape to open the menu \nUse WASD to move around \nUse the mouse to look around",
	Control_MoveForward_description = " ",
	Control_MoveBackward_description = " ",
	Control_MoveLeft_description = " ",
	Control_MoveRight_description = " ",
	Control_Jump_description = " ",
	Control_Crouch_description = " ",
	Control_Sprint_description = " ",
	Control_Action1_description = " ",
	Control_Action2_description = " ",
	Control_Action3_description = " ",
	Control_Action4_description = " "
}


resources.loadString("WindowTitle")
resources.loadString("OptionMenu_title")
resources.loadString("ControlMenu_title")
resources.loadString("InstructionMenu_title")
resources.loadString("InstructionMenu_instructions")


--[[ 
Load all models by passing their file path in 'resources.loadString("filePath")' Must use forward slashes rather than back slashes

resources.loadModel("res/models/ironman.obj")

--]]

resources.loadModel("res/model/IronMan/IronMan.obj")

resources.loadTexture("res/images/grass.jpg", "grass")
resources.loadTexture("res/images/water.jpg", "water")
resources.loadTexture("res/images/sand.jpg", "sand")
resources.loadTexture("res/images/dirt.jpg", "dirt")
resources.loadTexture("res/images/snow.jpg", "snow")
resources.loadTexture("res/images/endscene.jpg", "exitScreen")
