#include "ExampleGame.h"
#include "DemoActor.h"


ExampleGame::ExampleGame() : SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), bulletsManager_(this), fightersManager_(this, &bulletsManager_),
	astroidsManager_(this), collisionManager_(this, &bulletsManager_, &astroidsManager_, &fightersManager_), gameManager_(this), soundManager_(this)
{
	initGame();
	exit_ = false;

}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {
	// hide cursor
	SDL_ShowCursor(0);
	collisionManager_.registerObserver(&gameManager_);
	astroidsManager_.registerObserver(&gameManager_);
	gameManager_.registerObserver(&bulletsManager_);
	gameManager_.registerObserver(&astroidsManager_);
	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&soundManager_);

	actors_.push_back(&bulletsManager_);
	actors_.push_back(&fightersManager_);
	actors_.push_back(&astroidsManager_);
	actors_.push_back(&collisionManager_);
	actors_.push_back(&gameManager_);
}

void ExampleGame::closeGame() {

}

void ExampleGame::start() {
	exit_ = false;
	/*while (!exit_) {
		Uint32 startTime = SDL_GetTicks();*/
		//handleInput(startTime);
		//update(startTime);

	//	// check for collision of ball with paddles
	//	if (Collisions::collides(ball_, leftPaddle_)
	//			|| Collisions::collides(ball_, rightPaddle_)) {
	//		Vector2D v = ball_->getVelocity();
	//		v.setX(-v.getX());
	//		ball_->setVelocity(v * 1.2);
	//		getResources()->getSoundEffect(Resources::Paddle_Hit)->play(0);
	//	}

	//	// check if the back exit from sides
	//	if (ball_->getPosition().getX() <= 0) {
	//		rightScore_++;
	//		running_ = false;
	//		ball_->setVelocity(Vector2D(0, 0));
	//		ball_->setPosition(
	//				Vector2D(getWindowWidth() / 2 - 6,
	//						getWindowHeight() / 2 - 6));

	//	} else if (ball_->getPosition().getX() - ball_->getWidth()
	//			>= getWindowWidth()) {
	//		leftScore_++;
	//		running_ = false;
	//		ball_->setPosition(
	//				Vector2D(getWindowWidth() / 2 - 6,
	//						getWindowHeight() / 2 - 6));
	//		ball_->setVelocity(Vector2D(0, 0));
	//	}
	//	render(startTime);
	//	Uint32 frameTime = SDL_GetTicks() - startTime;
	//	if (frameTime < 10)
	//		SDL_Delay(10 - frameTime);
	//}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	//while (SDL_PollEvent(&event)) {
	//	if (event.type == SDL_KEYDOWN) {

	//		// if any key pressed while not running, we choose a random velocity of the ball
	//		if (!running_) {
	//			running_ = true;
	//			int dx = 1 - 2 * (rand() % 2); // 1 or -1
	//			int dy = 1 - 2 * (rand() % 2); // 1 or -1
	//			Vector2D v(dx * ((rand() % 5) + 2), dy * ((rand() % 5) + 2));
	//			v.normalize();
	//			ball_->setVelocity(v * 2);

	//			// rest the score if the game is over
	//			if (leftScore_ == 5 || rightScore_ == 5) {
	//				leftScore_ = 0;
	//				rightScore_ = 0;
	//			}
	//		}

	//		switch (event.key.keysym.sym) {
	//		case SDLK_ESCAPE:
	//			exit_ = true;
	//			break;
	//			// Pressing f to toggle fullscreen.
	//		case SDLK_f:
	//			int flags = SDL_GetWindowFlags(window_);
	//			if (flags & SDL_WINDOW_FULLSCREEN) {
	//				SDL_SetWindowFullscreen(window_, 0);
	//			} else {
	//				SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
	//			}
	//			break;
	//		}
	//	}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	//}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	// draw score
	//Texture score(getRenderer(),
	//		std::to_string(leftScore_) + " - " + std::to_string(rightScore_),
	//		*(getResources()->getFont(Resources::ARIAL24)),
	//		{ COLOR(0x111122ff) });
	//score.render(getRenderer(), getWindowWidth() / 2 - score.getWidth() / 2,
	//		10);

	//// press any key message when game is not running
	//if (!running_) {
	//	Texture* hitanykey = getResources()->getTextTexture(
	//			Resources::PresAnyKey);
	//	hitanykey->render(getRenderer(),
	//			getWindowWidth() / 2 - hitanykey->getWidth() / 2,
	//			getWindowHeight() - hitanykey->getHeight() - 50);
	//}

	//// game over message when game is over
	//if (leftScore_ == 5 || rightScore_ == 5) {
	//	Texture* gameOver = getResources()->getTextTexture(Resources::GameOver);
	//	gameOver->render(getRenderer(),
	//			getWindowWidth() / 2 - gameOver->getWidth() / 2,
	//			getWindowHeight() - gameOver->getHeight() - 150);
	//}

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

