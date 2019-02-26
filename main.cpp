/*
 * main.cpp
 *
 * This is the main executable file.
 * Creates a game object and then executes it.
 */

#include "game.h"
#include <time.h> // For srand().

/* Main function.
 *
 */
int main() {
    srand(time(NULL));

    bool start{true};
    while(start == true) {
        Game gameObj;
        gameObj.run_game(start);
    }

    return 0;
}
