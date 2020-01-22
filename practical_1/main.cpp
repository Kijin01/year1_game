#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

Vector2f ballVelocity;
bool server = false;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];
Font font;
Text text;

int player1score = 0;
int player2score = 0;

void Load() {
	// Set size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	

	// Load font-face from res dir
	font.loadFromFile("H:\OpenSans_Bold.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
	
}

void Reset() {
	// reset paddle position
	paddles[0].setPosition(paddleSize.x - 8, gameHeight / 2);
	paddles[1].setPosition(10 + gameWidth - paddleSize.x, gameHeight / 2);
	// reset Ball Position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	//Update Score Text
	text.setString(to_string(player1score)+" : "+to_string(player2score));
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
}

void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	ball.move(ballVelocity * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	
	
	if (by > gameHeight) { //bottom wall
	  // bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		//ball.move(0, -10);
	}
	else if (by < 0) { //top wall
   // top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		//ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		// right wall
		player1score++;
		Reset();
	}
	else if (bx < 0) {
		// left wall
		player2score++;
		Reset();
	}
	else if (
		//ball is inline or behind paddle
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// bounce off left paddle
		ballVelocity.x *= -1.0f;
		
	}
	else if (bx > paddles[1].getPosition().x - (paddleSize.x * 0.5) - 5 &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
		// bounce off right paddle
		ballVelocity.x *= -1.0f;
		
	}
	
	//if below bottom
	else if (paddles[0].getPosition().y + (paddleSize.y * 0.5) > gameHeight) {
		paddles[0].setPosition(paddleSize.x - 8, gameHeight - (paddleSize.y * 0.5));
	}
	//if over top
	else if (paddles[0].getPosition().y - (paddleSize.y * 0.5) < 0) {
		paddles[0].setPosition(paddleSize.x - 8, 0 + (paddleSize.y * 0.5));
	}
	//if below bottom
	else if (paddles[1].getPosition().y + (paddleSize.y * 0.5) > gameHeight) {
		paddles[1].setPosition(10 + gameWidth - paddleSize.x, gameHeight - (paddleSize.y * 0.5));
	}
	//if over top
	else if (paddles[1].getPosition().y - (paddleSize.y * 0.5) < 0) {
		paddles[1].setPosition(10 + gameWidth - paddleSize.x, 0 + (paddleSize.y * 0.5));
	}

	
	
	

	
	
	



	// handle paddle movement
	float direction1 = 0.0f;
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction1--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction1++;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		direction2++;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction2--;
	}
	paddles[0].move(0, direction1 * paddleSpeed * dt);
	paddles[1].move(0, direction2 * paddleSpeed * dt);
}

void Render(RenderWindow& window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	Reset();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}