#include "CCharacter.h"
#include <cmath>

class cameraFocusHandler {
	private:
		enum focusState { NEUTRAL, VIEW_PLAYER, VIEW_CNPC, VIEW_PATH, VIEW_XY }; /* Focus states */

		std::pair<float, float> XYCoOrdinates; // Current XY Location
		focusState followTag; // what we are currently following
		/* Path variables */
		float lastMoveTime; // Last move, to enforce the move velocity in the VIEW_PATH state
		float pathSpeed; // How fast to move the focus in VIEW_PATH state
		
		std::pair<float, float> XYTarget; // Target XY location when we are in the VIEW_PATH state
		bool debug; // Should debug data be shown?
		
		CNPC *currentNPC; // NPC to lock onto in VIEW_CNPC state
		Player *currentPlayer; // Player to lock onto in VIEW_PLAYER state
		
	public:
		cameraFocusHandler();
		~cameraFocusHandler();
		
		void setFocus(CNPC *sprite); // Follow Specified CNPC
		void setFocus(Player *sprite); // Follow Specified Player
		void setFocus(int _x, int _y); // Focus on a specified area
		void setFocus(float _x, float _y);
		void setPath(float ex, float ey, float nx, float ny, float speed); // Move from 'ex', 'ey' to 'nx', 'ny' at a velocity of 'speed'	
		void setPath(float ex, float ey, float nx, float ny); // Move from 'ex', 'ey' to 'nx', 'ny' at the default
	
		float getX(void);
		float getY(void);

		/* update the focus (the best place to run this is the loop where you update the display and do event
			processing but just before the framerate management). */
		void updateFocus();
};
