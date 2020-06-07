
-- Update function that is called every physics update, may happen multiple times a frame
Update = function(deltaTime) 
	 local player = GameObject.getPlayer();
	 local gameObj_charData = GameObject.to_character(player);
	 local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	 local playerCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(player.physBody));
	 local camera = getCamera();
	 local position = playerRigidBody:GetPosition();


	 if(gameObj_charData:status_get("FreeCam") == 0) then
		  camera.Position = position;
	 else 
		playerRigidBody:SetSleeping(true);
	end
	
	movePlayer(deltaTime);

	 if(gameObj_charData:status_get("FreeCam") == 0) then

		if(gameObj_charData:status_get("UseDynamics") == 0) then
			updatePlayerHeight();
		 end
		 if(gameObj_charData:status_get("UseDynamics") == 1) then
			catchPlayer();
		 end
	 end
	
end

-- Attaches the player back to the terrain if they have hit the terrain again after jumping
catchPlayer = function() 

	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local currentPos = playerRigidBody:GetPosition();
	local height = getHeightAt(currentPos.x, currentPos.z);
	local gameObj_charData = GameObject.to_character(player);

	if(gameObj_charData:status_get("Sliding") == 0) then
		if(height + 2 > currentPos.y) then
			gameObj_charData:status_assign("UseDynamics", 0)
		end
	end

end

--Creates a projectile with the given position and force, takes vector as parameters
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

--Creates a static object at the given position
createStatic = function (position)
	physicsManager = PhysicsManager:GetInstance();
	dynamicsWorld = physManager:GetDynamicsWorld();
	collisionWorld = physManager:GetCollisionWorld();
	gameObj_id = GameObject.create(GameObject.Types.Static());
	gameObj_raw = GameObject.get(gameObj_id);
	gameObj_raw.model = resources.getModel("res/model/vikings/SM_Env_Tree_Pine_Large_01.fbx");
	dynamicsWorld:GetRigidBody(gameObj_raw.physBody):SetPosition(position);
	rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
	rigidBody:AddCollisionShape(shapeFactory:GetShape(0), vector(0,0,0), quaternion(1,0,0,0), 5);

end

--Sets the players height to that of the terrain
updatePlayerHeight = function()
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local currentPos = playerRigidBody:GetPosition();
	local height = getHeightAt(currentPos.x, currentPos.z);
	currentPos.y = height + 1;
	playerRigidBody:SetPosition(currentPos);

end

-- Moves the player in a given direction, multiplies this by deltatime
movePlayerTo = function(direction, deltaTime) 

	local movementMult = 0.1;
	local camera = getCamera();
	local cameraFrontVector = camera.FrontVector;
	local cameraRightVector = camera:GetRightVector();
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local currentPos = playerRigidBody:GetPosition();
	local playerCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(player.physBody));


	local move = math.vectorMultiplyScalar(direction, deltaTime );
	move = math.normaliseVector(move);
	move = math.vectorMultiplyScalar(move, movementMult );
	local pos = math.vectorAdd(move, currentPos);
	playerRigidBody:SetPosition(pos);
end

--Moves the player based on current type of set movement
movePlayer = function(deltaTime)
	local camera = getCamera();
	local gameObj_charData = GameObject.to_character(player);
	local cameraFrontVector = camera.FrontVector;
	local cameraRightVector = camera:GetRightVector();
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local currentPos = playerRigidBody:GetPosition();
	local playerCollisionBody = getReactCollisionBody(collisionWorld:GetCollisionBody(player.physBody));
	local movementMult = 1000;

	if(gameObj_charData:status_get("FreeCam") == 0) then
		if(gameObj_charData:status_get("UseDynamics") == 1) then
			playerRigidBody:SetSleeping(false);

			if(	gameObj_charData:status_get("MoveForward") == 1) then 
				local force = math.vectorMultiplyScalar(cameraFrontVector, movementMult );
				local force = math.vectorMultiplyScalar(force, deltaTime );
				playerRigidBody:ApplyForceToCentre(force);
			end
			if(	gameObj_charData:status_get("MoveBackward") == 1) then 
				local force = math.vectorMultiplyScalar(cameraFrontVector, -movementMult );
				local force = math.vectorMultiplyScalar(force, deltaTime );
				playerRigidBody:ApplyForceToCentre(force);	
						
			end
			if(	gameObj_charData:status_get("MoveLeft") == 1) then 
				local force = math.vectorMultiplyScalar(cameraRightVector, -movementMult );
				local force = math.vectorMultiplyScalar(force, deltaTime );
				playerRigidBody:ApplyForceToCentre(force);
			end
			if(	gameObj_charData:status_get("MoveRight") == 1) then 
				local force = math.vectorMultiplyScalar(cameraRightVector, movementMult );
				local force = math.vectorMultiplyScalar(force, deltaTime );
				playerRigidBody:ApplyForceToCentre(force);
			end
		elseif(gameObj_charData:status_get("UseDynamics") == 0) then
			playerRigidBody:SetSleeping(true);
			local frontVec = vector(cameraFrontVector.x, 0, cameraFrontVector.z);
			local rightVec = vector(cameraRightVector.x, 0, cameraRightVector.z);
		
			if(	gameObj_charData:status_get("MoveForward") == 1) then 
				movePlayerTo(frontVec, deltaTime);
			end
			if(	gameObj_charData:status_get("MoveBackward") == 1) then 
				local direction = math.vectorMultiplyScalar(frontVec, -1);
				movePlayerTo(direction, deltaTime);
			end
			if(	gameObj_charData:status_get("MoveLeft") == 1) then 
				local direction = math.vectorMultiplyScalar(rightVec, -1);
				movePlayerTo(direction, deltaTime);
			end
			if(	gameObj_charData:status_get("MoveRight") == 1) then 
				movePlayerTo(rightVec, deltaTime);
			end
		
		end
	end
	if(gameObj_charData:status_get("FreeCam") == 1) then
		local MoveForward = gameObj_charData:status_get("MoveForward") == 1;
		local MoveBackward = gameObj_charData:status_get("MoveBackward") == 1;
		local MoveLeft = gameObj_charData:status_get("MoveLeft") == 1;
		local MoveRight = gameObj_charData:status_get("MoveRight") == 1;
		camera:ProcessKeyboard(MoveForward, MoveBackward, MoveLeft, MoveRight, deltaTime);
	end

end

-- Called every time that there is an input from the user, goes through all input cases and does the appropriate action
handleInput = function(inputData, deltaTime)

	local camera = getCamera();
	local player = GameObject.getPlayer();

	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local gameObj_charData = GameObject.to_character(player);
	
	local cameraFrontVector = camera.FrontVector;
	local cameraRightVector = camera:GetRightVector();

	--Keyboard button release
	if(inputData.inputType == "KeyRelease") then
			if(inputData.action == "Jump") then
				gameObj_charData:status_assign("Sliding",0);
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
				if(gameObj_charData:status_get("FreeCam") == 0) then
					gameObj_charData:status_assign("FreeCam",1);
							
				elseif(gameObj_charData:status_get("FreeCam") == 1) then
					gameObj_charData:status_assign("FreeCam",0);
				end
			elseif(inputData.action == "Action 1") then

			elseif(inputData.action == "Action 2") then
				toggleWireframe();
			elseif(inputData.action == "Action 3") then
				toggleGUIWindow("instructions");
			elseif(inputData.action == "Action 4") then
				toggleGUIWindow("exit");
	        end 
	--Keyboard button press
	elseif(inputData.inputType == "KeyPress") then
			if(inputData.action == "Jump") then
				if(gameObj_charData:status_get("UseDynamics") == 0) then
					gameObj_charData:status_assign("UseDynamics",1);
					playerRigidBody:SetSleeping(false);
					local scalar = 6000;
					force = vector(0,scalar,0);
					playerRigidBody:ApplyForceToCentre(force);

					local frontVec = vector(cameraFrontVector.x, 0, cameraFrontVector.z);
					local rightVec = vector(cameraRightVector.x, 0, cameraRightVector.z);
		
					if(	gameObj_charData:status_get("MoveForward") == 1) then 
						local direction = math.vectorMultiplyScalar(frontVec, scalar);
						playerRigidBody:ApplyForceToCentre(direction);
					end
					if(	gameObj_charData:status_get("MoveBackward") == 1) then 
						local direction = math.vectorMultiplyScalar(frontVec, -scalar);
						playerRigidBody:ApplyForceToCentre(direction);
					end
					if(	gameObj_charData:status_get("MoveLeft") == 1) then 
						local direction = math.vectorMultiplyScalar(rightVec, -scalar);
						playerRigidBody:ApplyForceToCentre(direction);
					end
					if(	gameObj_charData:status_get("MoveRight") == 1) then 
						local direction = math.vectorMultiplyScalar(rightVec, scalar);
						playerRigidBody:ApplyForceToCentre(direction);
					end
				end				
				if(gameObj_charData:status_get("UseDynamics") == 1) then
					gameObj_charData:status_assign("Sliding",1);
				end
				
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
	--Mous button press
	elseif(inputData.inputType == "MouseButtonPress") then
		if(inputData.action == "Mouse Left") then

			createProjectile(math.vectorAdd(playerRigidBody:GetPosition(), math.vectorMultiplyScalar(cameraFrontVector, 5)), cameraFrontVector);
		elseif(inputData.action == "Mouse Middle") then

		elseif(inputData.action == "Mouse Right") then
			createStatic(math.vectorAdd(playerRigidBody:GetPosition(), math.vectorMultiplyScalar(cameraFrontVector, 5)));
		end
	--Mouse Button Release
	elseif(inputData.inputType == "MouseButtonRelease") then
		if(inputData.action == "Mouse Left") then
			
		elseif(inputData.action == "Mouse Middle") then

		elseif(inputData.action == "Mouse Right") then
		
		end
	-- Mouse movement
	elseif(inputData.inputType == "MouseMotion") then
		camera:ProcessMouseMovement(inputData.relativeMouseMotion.x, inputData.relativeMouseMotion.y, 1);
	--Mouse wheel movement
	elseif(inputData.inputType == "MouseWheel") then

	end
	
end


	
