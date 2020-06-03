Update = function(deltaTime) 
	player = GameObject.get(2);
	playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	camera = getCamera();
	position = playerRigidBody:GetPosition();
	camera.Position = position;
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


handleInput = function(inputData, deltaTime)

	camera = getCamera();
	physicsManager = PhysicsManager:GetInstance();
	dynamicsWorld = physManager:GetDynamicsWorld();
	collisionWorld = physManager:GetCollisionWorld();
	player = GameObject.get(2);
	playerRigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(player.physBody));
	
	cameraFrontVector = camera.FrontVector;
	cameraRightVector = camera:GetRightVector();
	
	movementMult = 1000;
	
	if(inputData.inputType == "KeyRelease") then
			if(inputData.action == "Jump") then

			elseif(inputData.action == "Move Forward") then

			elseif(inputData.action == "Move Backward") then

			elseif(inputData.action == "Move Left") then

			elseif(inputData.action == "Move Right") then

			elseif(inputData.action == "Escape") then
				toggleGUIWindow("menu");
			elseif(inputData.action == "Sprint") then
				gameObj_raw = GameObject.get(20);
				rigidBody = getReactRigidBody(dynamicsWorld:GetRigidBody(gameObj_raw.physBody));
				force = vector(0,5000,0);
				rigidBody:ApplyForceToCentre(force);
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

				force = vector(0,1000,0);
				rigidBody:ApplyForceToCentre(force);
				
			elseif(inputData.action == "Escape") then

			elseif(inputData.action == "Move Forward") then
				force = math.vectorMultiplyScalar(cameraFrontVector, movementMult );
				rigidBody:ApplyForceToCentre(force);
			elseif(inputData.action == "Move Backward") then
				force = math.vectorMultiplyScalar(cameraFrontVector, -movementMult );
				rigidBody:ApplyForceToCentre(force);
			elseif(inputData.action == "Move Left") then
				force = math.vectorMultiplyScalar(cameraRightVector, -movementMult );
				rigidBody:ApplyForceToCentre(force);
			elseif(inputData.action == "Move Right") then
				force = math.vectorMultiplyScalar(cameraRightVector, movementMult );
				rigidBody:ApplyForceToCentre(force);
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
			--[[for i=0,1,1 do
			createProjectile(getCamera().Position, getCamera().FrontVector);
			end
			]]--
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
end


	
