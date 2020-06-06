
Update = function(deltaTime) 
	-- local player = GameObject.getPlayer();
	 --local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	 local camera = getCamera();
	-- local position = playerRigidBody:GetPosition();
	 --camera.Position = position;
	--movePlayer(deltaTime);
end


createProjectile = function (position, force)
	physicsManager = PhysicsManager:GetInstance();
	dynamicsWorld = physManager:GetDynamicsWorld();
	collisionWorld = physManager:GetCollisionWorld();
	gameObj_id = GameObject.create(GameObject.Types.NPC());
	gameObj_raw = GameObject.get(gameObj_id);
	gameObj_raw.model = resources.getModel("res/model/ball.fbx");
	dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
	rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
	rigidBody:AddCollisionShape(shapeFactory:GetShape(0), vector(0,0,0), quaternion(1,0,0,0), 5);
	rigidBody:ApplyForceToCentre(math.vectorMultiplyScalar(force, 80000));
end

movePlayer = function(deltaTime)
	local camera = getCamera();
	local gameObj_charData = GameObject.to_character(player);
	local cameraFrontVector = camera.FrontVector;
	local cameraRightVector = camera:GetRightVector();
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local playerCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(player.physBody));
	local movementMult = 1000;

	if(gameObj_charData:status_get("UseDynamics") == 1) then
		if(	gameObj_charData:status_get("MoveForward") == 1) then 
			local force = math.vectorMultiplyScalar(cameraFrontVector, movementMult );
			--local force = math.vectorMultiplyScalar(force, deltaTime );
			playerRigidBody:ApplyForceToCentre(force);
		end
		if(	gameObj_charData:status_get("MoveBackward") == 1) then 
			local force = math.vectorMultiplyScalar(cameraFrontVector, -movementMult );
			--local force = math.vectorMultiplyScalar(force, deltaTime );
			playerRigidBody:ApplyForceToCentre(force);	
						
		end
		if(	gameObj_charData:status_get("MoveLeft") == 1) then 
			local force = math.vectorMultiplyScalar(cameraRightVector, -movementMult );
			--local force = math.vectorMultiplyScalar(force, deltaTime );
			playerRigidBody:ApplyForceToCentre(force);
		end
		if(	gameObj_charData:status_get("MoveRight") == 1) then 
			local force = math.vectorMultiplyScalar(cameraRightVector, movementMult );
			--local force = math.vectorMultiplyScalar(force, deltaTime );
			playerRigidBody:ApplyForceToCentre(force);
		end
	elseif(gameObj_charData:status_get("UseDynamics") == 0) then
		if(	gameObj_charData:status_get("MoveForward")) then 
	
		end
		if(	gameObj_charData:status_get("MoveBackward")) then 
	
		end
		if(	gameObj_charData:status_get("MoveLeft")) then 
	
		end
		if(	gameObj_charData:status_get("MoveRight")) then 
	
		end
	end

end


handleInput = function(inputData, deltaTime)

	local camera = getCamera();
	local player = GameObject.getPlayer();
--[[
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local gameObj_charData = GameObject.to_character(player);
	
	local cameraFrontVector = camera.FrontVector;
	local cameraRightVector = camera:GetRightVector();
	
	local movementMult = 1000;
	
	if(inputData.inputType == "KeyRelease") then
			if(inputData.action == "Jump") then

			elseif(inputData.action == "Move Forward") then
				gameObj_charData:status_assign("MoveForward", 0);
			elseif(inputData.action == "Move Backward") then
				gameObj_charData:status_assign("MoveBackward", 0);
			elseif(inputData.action == "Move Left") then
				gameObj_charData:status_assign("MoveLeft", 0);
			elseif(inputData.action == "Move Right") then
				gameObj_charData:status_assign("MoveRight", 0);
			elseif(inputData.action == "Escape") then
				toggleGUIWindow("menu");
			elseif(inputData.action == "Sprint") then

			elseif(inputData.action == "Crouch") then

			elseif(inputData.action == "Action 1") then
				camera:ProcessKeyboard(true, false, false, false, deltaTime);
			elseif(inputData.action == "Action 2") then
				toggleWireframe();
			elseif(inputData.action == "Action 3") then
				toggleGUIWindow("instructions");
			elseif(inputData.action == "Action 4") then
				toggleGUIWindow("exit");
	        end 
	elseif(inputData.inputType == "KeyPress") then
			if(inputData.action == "Jump") then
				
			elseif(inputData.action == "Escape") then

			elseif(inputData.action == "Move Forward") then
			
				gameObj_charData:status_assign("MoveForward", 1);
			elseif(inputData.action == "Move Backward") then
				gameObj_charData:status_assign("MoveBackward", 1);
			elseif(inputData.action == "Move Left") then
				gameObj_charData:status_assign("MoveLeft", 1);
			elseif(inputData.action == "Move Right") then
				gameObj_charData:status_assign("MoveRight", 1);
			elseif(inputData.action == "Sprint") then

			elseif(inputData.action == "Crouch") then

			elseif(inputData.action == "Menu") then

			elseif(inputData.action == "Action 1") then

			elseif(inputData.action == "Action 2") then

			elseif(inputData.action == "Action 3") then

			elseif(inputData.action == "Action 4") then

			
	        end 
	elseif(inputData.inputType == "MouseButtonPress") then
		if(inputData.action == "Mouse Left") then

		elseif(inputData.action == "Mouse Middle") then

		elseif(inputData.action == "Mouse Right") then

		end
	elseif(inputData.inputType == "MouseButtonRelease") then
		if(inputData.action == "Mouse Left") then
			
		elseif(inputData.action == "Mouse Middle") then

		elseif(inputData.action == "Mouse Right") then
		
		end
		
	elseif(inputData.inputType == "MouseMotion") then
		camera:ProcessMouseMovement(inputData.relativeMouseMotion.x, inputData.relativeMouseMotion.y, 1);
	elseif(inputData.inputType == "MouseWheel") then

	end
	--]]
end


	
