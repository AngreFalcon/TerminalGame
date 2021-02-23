#include "globals.h"

const bool DEBUG = true; //used to enable verbose logging to terminal; eventually this value may be initialized via a settings file

//window buffer width and height must be at least 1 greater than window width and height or resizing will fail
//buffer height is 10x larger than window height to allow the console to retain some output history
const short int WINDOWWIDTH = 100; //eventually this value may be initialized via a settings file
const short int WINDOWHEIGHT = 35; //eventually this value may be initialized via a settings file
const short int BUFFERWIDTH = WINDOWWIDTH + 1; //these values will not be modifiable via any user settings due to their tendency to cause errors when set to an improper value
const short int BUFFERHEIGHT = WINDOWHEIGHT * 10; //these values will not be modifiable via any user settings due to their tendency to cause errors when set to an improper value

Assets *assetData;
Player *playerCharacter;

