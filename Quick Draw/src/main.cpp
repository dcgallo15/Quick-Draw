#include "../include/main.h"

enum class animationState
{
	IDLE,MOVING,JUMPING,DEAD
};

/*MAIN*/
int main(int argc, char* args[])
{
	LOG_INIT;	// NEED TO REMEMBER TO DO THIS
	LOG_INFO("Started");

	SDL_version compiled;

	SDL_VERSION(&compiled);
	LOG_INFO("SDL VERSION: {0}.{1}.{2}", compiled.major, compiled.minor, compiled.patch);
	LOG_INFO("OPENGL VERSION: {0}.{1}.{2}", SDL_GL_CONTEXT_MAJOR_VERSION, SDL_GL_CONTEXT_MINOR_VERSION, SDL_GL_CONTEXT_PROFILE_MASK);

	/*INITS*/
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		LOG_FATAL("VIDEO HAS FAILED:");
		LOG_FATAL(SDL_GetError());
	}
	if (SDL_Init(SDL_INIT_AUDIO) > 0)
	{
		LOG_FATAL("AUDIO HAS FAILED:");
		LOG_FATAL(SDL_GetError());
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		LOG_FATAL("IMAGE HAS FAILED:");
		LOG_FATAL(SDL_GetError());
	}
	if (TTF_Init() != 0)
	{
		LOG_FATAL("TTF HAS FAILED:");
		LOG_FATAL(SDL_GetError());
	}

	renderWindow window("Quick Draw",1280,720);

	Uint32 startingTick;

	Entity sandSquare(window.loadTexture("res/img/squares/sandSquare.png"), 0, 0, 32, 32);
	Entity yellowSquare(window.loadTexture("res/img/squares/yellowSquare.png"), 0, 0, 32, 32);

	float groundLevel = 720.0f-((float)yellowSquare.getH() * 4);	// if yellowSquare.getH = 32 them ground level = 592

	Player gun(window.loadTexture("res/img/gun.png"),50,50,64,64,0.5);
	Player bullet(window.loadTexture("res/img/bullet.png"), 0, 0, 16, 16,0.5);

	const SDL_Color purple = {255,255,0};

	SDL_Texture* playerIdle1 = window.loadTexture("res/img/player/playerIdle1.png");
	SDL_Texture* playerMove1 = window.loadTexture("res/img/player/playerRunning1.png");
	SDL_Texture* playerTex = window.loadTexture("res/img/player/player.png");
	Player player(playerTex, 100, groundLevel- (64), 32, 64);

	SDL_Texture* enemyTex = window.loadTexture("res/img/enemy/enemy.png");
	Enemy enemy(enemyTex, 1180, groundLevel - (64), 32, 64);

	player.setSpeed(16.0f);
	bullet.setSpeed(6.0f);

	short amountOfBullets = 10;
	std::vector<Player> bullets;
	bullets.reserve(amountOfBullets);

	bool gameRunning = true;
	bool left = false;
	bool enemyDead = false;

	SDL_Event event;

	auto fpsCap = [&startingTick](unsigned int fps)		// fpsCap lambda
	{
		startingTick = SDL_GetTicks();
		if ((1000 / fps) > SDL_GetTicks() - startingTick)
			SDL_Delay(1000 / fps - (SDL_GetTicks() - startingTick));
	};

	// Distance Gun is away from player
	short xOffset = 32;
	short yOffset = 16;

	/*Animation Stuff*/
	animationState playerState;
	playerState = animationState::IDLE;

	int animFrameCounter = 0;
	int idleFrameCounter = 0;
	int movingFrameCounter = 0;

	/*FILL CALL*/
	SDL_Texture* background = window.loadTexture("res/img/background.png");

	/*Game Loop*/
	while (gameRunning)
	{
		window.clear();
		window.fill(background);	/* if using a texture to fill put in loop
									   else dont put in loop				*/
		fpsCap(120);
		
		while (SDL_PollEvent(&event))	// polls for events
		{
			if (event.type == SDL_QUIT) { gameRunning = false; }

			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					gameRunning = false;
					break;
				case SDLK_w:
					player.setY(player.getY() + 1);
					if (player.getY() > groundLevel - (yellowSquare.getH() * 2))	// standing on ground - need to add  "and standing on platform"
						player.jump(80);
					player.setY(player.getY() + 1);
					player.follow(gun, xOffset, yOffset);
					break;
				case SDLK_s:
					player.moveDown();
					player.follow(gun, xOffset, yOffset);
					break;
				case SDLK_a:
					left = true;
					player.moveLeft();
					playerState = animationState::MOVING;
					break;
				case SDLK_d:
					left = false;
					player.moveRight();
					playerState = animationState::MOVING;
					break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) 
			{
				switch (event.button.button)	// to get what mouse button is pressed
				{
				case SDL_BUTTON_LEFT:
						bullet.setX(gun.getX());
						bullet.setY(gun.getY());
						if (amountOfBullets > 0)
						{
							bullets.push_back(bullet);
							amountOfBullets--;
						}
					break;
				}
			}
		}

		/*Rendering Ammo Count*/
		for (int i = 0; i < amountOfBullets; i++) 
		{
			bullet.setY(groundLevel + 96);
			bullet.setX(64.0f + ((float)i * 32.0f));
			window.render(bullet);
		}

		/*Rendering Side Borders*/
		for (int i = 0; i < (720 / sandSquare.getH()*sandSquare.getScalar())+1; i++) 
		{
			sandSquare.setX(1280-sandSquare.getW()*sandSquare.getScalar());
			window.render(sandSquare);
			sandSquare.setY(i * sandSquare.getW()*sandSquare.getScalar());
			sandSquare.setX(0);
			window.render(sandSquare);
		}

		/*Rendering Ground (want to add another top layer with different texture)*/
		for (int i = 0; i < (1280/yellowSquare.getW()*yellowSquare.getScalar())-2; i++) 
		{
			for (int j = 0; j < 2; j++)		// j < amount of filled underneath ground level
			{
				yellowSquare.setY(groundLevel + (yellowSquare.getW()*j));
				yellowSquare.setX((sandSquare.getW()* sandSquare.getScalar()) + (yellowSquare.getH() * i * yellowSquare.getScalar()));
				window.render(yellowSquare);
			}
		}

		/*Changing Gun Direction*/
		if (left == true and xOffset > 0)
		{
			xOffset = xOffset * -1;
		}
		else if (left == false and xOffset < 0)
		{
			xOffset = xOffset * -1;
		}

		/*Handles Bullet Logic*/
		for (unsigned int i = 0; i < bullets.size(); i++) 
		{
			if(left == true and bullets[i].getX() > player.getX())
				bullets[i].setX(bullets[i].getX() + bullets[i].getSpeed());

			else if (left == false and bullets[i].getX() > player.getX())
				bullets[i].setX(bullets[i].getX() + bullets[i].getSpeed());

			else
				bullets[i].setX(bullets[i].getX() - bullets[i].getSpeed());
			
			window.render(bullets[i]);
			if (bullets[i].collidesX(sandSquare.getW(),1280) == true or bullets[i].getX() < 0)
				bullets.erase(bullets.begin());
		}

		player.follow(gun, xOffset, yOffset);
		player.gravity(0.5f);
		player.stopJump();

		/*COLLISION LOGIC*/

		/*Handles Collision Logic For gun with Side Borders (needs improving slightly)*/
		if (gun.getX() > 1280 - (gun.getW() * gun.getScalar()) - (gun.getW() * gun.getScalar())) { gun.setX(1280 - (float)sandSquare.getW() * 2); }
		else if (gun.getX() < (gun.getW() * gun.getScalar())) { gun.setX((float)sandSquare.getW()); }

		/*Handles Collision Logic For gun with Ground*/
		if (gun.getY() > groundLevel - yellowSquare.getH()) { gun.setY(groundLevel - (gun.getH() * gun.getScalar())); }

		/*Handles Collision Logic For player with Side Borders*/
		if (player.getX() > 1280 - (sandSquare.getW() * sandSquare.getScalar()) - (player.getW() * player.getScalar())) { player.setX(1280 - (float)sandSquare.getW() * 2); }
		else if (player.getX() < (sandSquare.getW()*sandSquare.getScalar())) { player.setX((float)sandSquare.getW()); }

		/*Handles Collision Logic For player with Ground*/
		if (player.getY() > groundLevel - (yellowSquare.getH() * 2 * yellowSquare.getScalar())) { player.setY(groundLevel - (player.getH() * player.getScalar())); }
		else if (player.getY() < 0) { player.setY(groundLevel - (player.getH() * player.getScalar())); }
		
		/*Handles Collision Logic For enemy with bullets*/
		for(unsigned int i = 0;i < bullets.size();i++)
			if (enemy.collision(bullets[i]) == true) enemyDead = true;

		/*Player Animations*/
		
		/*IDLE ANIMATION*/
		if (playerState == animationState::IDLE)
		{
			idleFrameCounter++;
			if (idleFrameCounter++ > 90)
				player.setTexture(playerIdle1);
			else
				player.setTexture(playerTex);

			if (idleFrameCounter > 180)
				idleFrameCounter = 0;
		}

		/*Moving Animation*/
		if (playerState == animationState::MOVING)
		{
			movingFrameCounter++;
			if (movingFrameCounter++ > 90)
				player.setTexture(playerMove1);
			else
				player.setTexture(playerTex);

			if (movingFrameCounter > 180)
				movingFrameCounter = 0;
		}

		animFrameCounter++;
		if (animFrameCounter > 120) 
		{
			playerState = animationState::IDLE;
			animFrameCounter = 0;
		}

		if (left)
		{
			window.render(gun, NULL, NULL, SDL_FLIP_HORIZONTAL);
			window.render(player);
		}
		else 
		{
			window.render(gun);
			window.render(player, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
			
		if (enemyDead == false) window.render(enemy);

		window.display();
	}

	sandSquare.cleanUp();
	yellowSquare.cleanUp();

	player.cleanUp();
	gun.cleanUp();
	bullet.cleanUp();
	bullets.~vector();

	SDL_DestroyTexture(background);
	SDL_DestroyTexture(playerTex);
	SDL_DestroyTexture(playerIdle1);
	SDL_DestroyTexture(playerMove1);
	SDL_DestroyTexture(enemyTex);

	/*QUITS*/
	TTF_Quit();
	IMG_Quit();
	SDL_AudioQuit();
	SDL_VideoQuit();
	SDL_Quit();

	LOG_ERROR("Program Terminated!");
	std::cout << "\n" <<"PRESS THE ENTER KEY TO EXIT!";
	std::cin.get();
	return 0;
}