#include "App.h"
#include "TestScene.h"

int main(int argc, char *argv[]) {
	App *game = new App("Escape Fighting", 1366, 768);
	game->SwitchScene(new TestScene());
	game->Main();
	return 0;
}
