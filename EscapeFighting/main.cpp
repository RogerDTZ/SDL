#include "App.h"

int main(int argc, char *argv[]) {
	App *game = new App("Escape Fighting", 1024, 768);
	game->SwitchScene(new TestScene());
	game->Main();
	return 0;
}
