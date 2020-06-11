
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

	 UpdateOxygen();
	 checkCollisions();
	
end

-- Attaches the player back to the terrain if they have hit the terrain again after jumping
catchPlayer = function() 

	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	local currentPos = playerRigidBody:GetPosition();
	local height = getHeightAt(currentPos.x, currentPos.z);
	local gameObj_charData = GameObject.to_character(player);

	if(gameObj_charData:status_get("Sliding") == 0) then
		if(height + 1.3 > currentPos.y) then
			gameObj_charData:status_assign("UseDynamics", 0)
		end
	end

end

checkCollisions = function()
		local id_list = GameObject.listNPCs();
		damage = BulletCharData:status_get("Damage");
		for iterator, npcID in pairs(id_list) do
			local npcObject = GameObject.get(npcID);

			local charData = GameObject.to_character(npcObject);

			if(charData:status_has("Projectile") == false) then
				if(collisionWorld:TestOverlap(BulletObject.physBody, npcObject.physBody)== true) then
					local npcObjectHealth = charData:status_get("Health");
					charData:status_assign("Health", npcObjectHealth - damage);
					print("NPC ID:" .. npcID .. " Old Health: " .. npcObjectHealth .. " New Health: " .. charData:status_get("Health"))
					BulletRigidBody:SetPosition(vector(0,0,0));
				end
			end

		end

end

--Creates a projectile with the given position and force, takes vector as parameters
createProjectile = function (position, force)
	physicsManager = PhysicsManager:GetInstance();
	dynamicsWorld = physManager:GetDynamicsWorld();
	collisionWorld = physManager:GetCollisionWorld();
	gameObj_raw = GameObject.get(BulletID);
	gameobj_char = GameObject.to_character(gameObj_raw);
	rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
	rigidBody:SetSleeping(true);
	rigidBody:SetPosition(position);
	rigidBody:SetOrientation(quaternion(1,0,0,0));


	rigidBody:ApplyForceToCentre(math.vectorMultiplyScalar(force, 50000));
end

useJetpack = function(deltaTime)
	local gameObj_charData = GameObject.to_character(player);
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));

	jetpackThrust = vector(0,15000,0);
	jetpackThrust = math.vectorMultiplyScalar(jetpackThrust, deltaTime);

	jetpackAmount = gameObj_charData:status_get("Jetpack");

	if(jetpackAmount > 0)	then
		playerRigidBody:ApplyForceToCentre(jetpackThrust);
	end	
	gameObj_charData:status_assign("Jetpack", jetpackAmount - 1);
	if(jetpackAmount < 1)	then
		gameObj_charData:status_assign("Jetpack", 0);
	end

end

--Creates a static object at the given position
createStatic = function (position)
	physicsManager = PhysicsManager:GetInstance();
	dynamicsWorld = physManager:GetDynamicsWorld();
	collisionWorld = physManager:GetCollisionWorld();
	gameObj_id = GameObject.create(GameObject.Types.Static());
	gameObj_raw = GameObject.get(gameObj_id);
	gameObj_raw.model = resources.getModel("res/model/ball.fbx");
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
	playerCollisionBody:SetPosition(pos);

	if(collisionWorld:TestOverlap(BoundingWallID, player.physBody) == true) then
		playerRigidBody:SetPosition(currentPos);
	 else
		playerRigidBody:SetPosition(pos);
	 end
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
			if(gameObj_charData:status_get("UsingJetpack") == 1) then
				useJetpack(deltaTime)
			end

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

			if(gameObj_charData:status_get("Jetpack") < 500) then
				gameObj_charData:status_assign("Jetpack", gameObj_charData:status_get("Jetpack") + 1)
			end
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

				if(gameObj_charData:status_get("UseDynamics") == 0 or playerRigidBody:GetPosition().y < 105) then
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
				gameObj_charData:status_assign("UsingJetpack", 1);
			--createStatic(math.vectorAdd(playerRigidBody:GetPosition(), math.vectorMultiplyScalar(cameraFrontVector, 5)));
		end
	--Mouse Button Release
	elseif(inputData.inputType == "MouseButtonRelease") then
		if(inputData.action == "Mouse Left") then
			
		elseif(inputData.action == "Mouse Middle") then

		elseif(inputData.action == "Mouse Right") then
				gameObj_charData:status_assign("UsingJetpack", 0);
		end
	-- Mouse movement
	elseif(inputData.inputType == "MouseMotion") then
		camera:ProcessMouseMovement(inputData.relativeMouseMotion.x, inputData.relativeMouseMotion.y, 1);
	--Mouse wheel movement
	elseif(inputData.inputType == "MouseWheel") then

	end
	
end

UpdateOxygen = function()
	local gameObj_charData = GameObject.to_character(player);
	local oxygenLevel = gameObj_charData:status_get("Oxygen");
	local playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	if(playerRigidBody:GetPosition().y < 105) then
		gameObj_charData:status_assign("Oxygen", oxygenLevel - 1);
	else
		gameObj_charData:status_assign("Oxygen", 1000);
	end
	if (gameObj_charData:status_get("Oxygen") < 1) then
		local health = gameObj_charData:status_get("Health");
		gameObj_charData:status_assign("Health", health - 0.1);
		gameObj_charData:status_assign("Oxygen", 0);
	
	end
end

GUI = function() 
	local windowSize = GUIFunctions.GetWindowSize();
	local gameObj_charData = GameObject.to_character(player);
	local oxygenLevel = gameObj_charData:status_get("Oxygen");
	local jetpackLevel = gameObj_charData:status_get("Jetpack");
	local Health = gameObj_charData:status_get("Health");


	--Oxygen
	if(oxygenLevel < 1000) then
		GUIFunctions.SetNextWindowPos(windowSize.x/2 - 150,windowSize.y - 50, true);

		GUIFunctions.BeginWindow("Oxygen");
		GUIFunctions.SetFontSize(3);
		GUIFunctions.Text("Oxygen: " .. oxygenLevel)
		GUIFunctions.EndWindow();
	end
	--Jetpack
			GUIFunctions.SetNextWindowPos(0,windowSize.y - 50, true);
	GUIFunctions.BeginWindow("Jetpack");
	GUIFunctions.SetFontSize(3);
	GUIFunctions.Text("Jetpack: " .. jetpackLevel)
	GUIFunctions.EndWindow();


	--Health
	GUIFunctions.SetNextWindowPos(windowSize.x - 300 ,windowSize.y - 50, true);
	GUIFunctions.BeginWindow("Health");
	GUIFunctions.SetFontSize(3);
	if(Health < 0 ) then
		Health = 0;
	end
	GUIFunctions.Text("Health: " .. Health)
	GUIFunctions.EndWindow();


	--Death
	if(Health == 0) then
		GUIFunctions.SetNextWindowPos(windowSize.x/2 - 180,windowSize.y/2 - 50, true);
		GUIFunctions.BeginWindow("DEAD");
		GUIFunctions.SetFontSize(6);

		GUIFunctions.Text("YOU DEAD");
		GUIFunctions.EndWindow();
	end
end
	
