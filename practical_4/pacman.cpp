using namespace std;
using namespace sf;


void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
  Renderer::queue(&text);
  Scene::render();
}

void MenuScene::load() {
//Set up the text element here!
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	
	Scene::update(dt);
}