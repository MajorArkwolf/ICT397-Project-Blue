handleInput = function(inputData)
	if(inputData.inputType == "KeyRelease") then
			if(inputData.action == "Jump") then
				physManager = PhysicsManager:GetInstance();
				dynamicsWorld = physManager:GetDynamicsWorld();
				gameObj_raw = GameObject.get(20);
				dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
				rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
				force = vector(0,0.0000001,0);
				debug.printVector(force);
				rigidBody:SetSleeping(true);
				rigidBody:SetSleeping(false);
				rigidBody:ApplyForceToCentre(force);
			elseif(inputData.action == "Move Forward") then

			elseif(inputData.action == "Move Backward") then

			elseif(inputData.action == "Move Left") then

			elseif(inputData.action == "Move Right") then

			elseif(inputData.action == "Escape") then
				toggleGUIWindow("menu");
			elseif(inputData.action == "Sprint") then
				physManager = PhysicsManager:GetInstance();
				dynamicsWorld = physManager:GetDynamicsWorld();
				gameObj_raw = GameObject.get(20);
				rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
				force = vector(0,5000,0);
				rigidBody:ApplyForceToCentre(force);
			elseif(inputData.action == "Crouch") then

			elseif(inputData.action == "Menu") then

			elseif(inputData.action == "Action 1") then

			elseif(inputData.action == "Action 2") then
				toggleWireframe();
			elseif(inputData.action == "Action 3") then
				toggleGUIWindow("instructions");
			elseif(inputData.action == "Action 4") then
				toggleGUIWindow("exit");
	        end 
	elseif(inputData.inputType == "KeyPress") then
			if(inputData.action == "Jump") then

			elseif(inputData.action == "Move Forward") then

			elseif(inputData.action == "Move Backward") then

			elseif(inputData.action == "Move Left") then

			elseif(inputData.action == "Move Right") then

			elseif(inputData.action == "Sprint") then

			elseif(inputData.action == "Crouch") then

			elseif(inputData.action == "Menu") then

			elseif(inputData.action == "Action 1") then

			elseif(inputData.action == "Action 2") then

			elseif(inputData.action == "Action 3") then

			elseif(inputData.action == "Action 4") then

	        end 
	elseif(inputData.inputType == "MouseButtonPress") then
		print(inputData.action)
	elseif(inputData.inputType == "MouseButtonRelease") then

	elseif(inputData.inputType == "MouseMotion") then

	elseif(inputData.inputType == "MouseWheel") then

	end
end


	
