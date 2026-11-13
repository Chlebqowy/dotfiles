#include <string>
struct {
	string name;
	int x-res;
	int y-res;
	int x-loc;
	int y-loc;
	float scale;	
    string transform; //same as sway, man sway-output:
    /*output <name> transform <transform> [clockwise|anticlockwise]
        Sets the background transform to the given value. Can be one of "90", "180", "270" for rotation; or "flipped", "flipped-90", "flipped-180", "flipped-270" to  apply  a  rotation  and
        flip,  or  "normal"  to apply no transform. The rotation is performed clockwise. If a single output is chosen and a rotation direction is specified (clockwise or anticlockwise) then
        the transform is added or subtracted from the current transform (this cannot be used directly in the configuration file).*/
	bool primary;
} Screen
Screen screens = [];

// todo gen sway
// todo gen import for bars
// todo gen rofi/dunst screen to open
