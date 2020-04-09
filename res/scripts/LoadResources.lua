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
	HelpMenu = "Do stuff to win",
	OptionMenu_title = "Menu",
	ControlMenu_title = "Controls",
	ControlMenu_instructions = " ",
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

resources.loadString("HelpMenu")
resources.loadString("WindowTitle")
resources.loadString("OptionMenu_title")
resources.loadString("ControlMenu_title")

resources.loadModel("ironman.fbx")
