#include "cameraFocusHandler.h"

cameraFocusHandler::cameraFocusHandler(int _resW, int _resH)
{
	screenWidth = _resW;
	screenHeight = _resH;
	currentNPC = 0;
	currentPlayer = 0;
}

cameraFocusHandler::~cameraFocusHandler()
{

}

void cameraFocusHandler::setFocus(CNPC *_sprite)
{
	currentNPC = _sprite;
	followTag = VIEW_CNPC;
}

void cameraFocusHandler::setFocus(Player *_sprite)
{
	currentPlayer = _sprite;
	followTag = VIEW_PLAYER;
}

void cameraFocusHandler::setPath(float ex, float ey, float nx, float ny, float speed)
{
	XYCoOrdinates.first = ex;
	XYCoOrdinates.second = ey;
	XYTarget.first = nx;
	XYTarget.second = ny;
	pathSpeed = speed;
	lastMoveTime = 0;
	followTag = VIEW_PATH;
}

void cameraFocusHandler::setPath(float ex, float ey, float nx, float ny)
{
	XYCoOrdinates.first = ex;
	XYCoOrdinates.second = ey;
	XYTarget.first = nx;
	XYTarget.second = ny;
	pathSpeed = 1;
	lastMoveTime = 0;
	followTag = VIEW_PATH;
}

void cameraFocusHandler::setFocus(float _x, float _y)
{
	XYCoOrdinates.first = _x;
	XYCoOrdinates.second = _y;
	followTag = VIEW_XY;
}

void cameraFocusHandler::setFocus(int _x, int _y)
{
	XYCoOrdinates.first = (float) _x;
	XYCoOrdinates.second = (float) _y;
	followTag = VIEW_XY;
}

void cameraFocusHandler::updateFocus()
{
	static float difference_x1x2 = 0.0; // Difference between x1 and x2
	static float difference_y1y2 = 0.0; // Difference between y1 and y2
	static float x_step = 0.0; // How much to increment the x axis position each run
	static float y_step = 0.0; // How much to increment the y axis position each run
	static float trajectory_angleA; // Trajectory angle to the x-axis (tan-1(o/a))

	switch (followTag) {
		case (VIEW_CNPC):
			XYCoOrdinates.first = (float)currentNPC->x_pos-(screenWidth/2);
			XYCoOrdinates.second = (float)currentNPC->y_pos-(screenHeight/2);
		break;

		case (VIEW_PLAYER):
			XYCoOrdinates.first = (float)currentPlayer->x_pos-(screenWidth/2);
			XYCoOrdinates.second = (float)currentPlayer->y_pos-(screenHeight/2);
		break;

		case (VIEW_PATH):
			if (SDL_GetTicks()+1000 >= lastMoveTime && followTag == VIEW_PATH) {
				// We only want to run the step calculations in the first run of the path
				if (!_inPath) {
					std::cout << "cameraFocusHandler::updateFocus : " <<
					          "Entering path from (" << XYCoOrdinates.first <<
					          ", " << XYCoOrdinates.second << ") to (" <<
					          XYTarget.first << ", " << XYTarget.second <<
					          ") " << std::endl;

					// Get the change in displacement between x1y1 to x2y2
					difference_x1x2 = (XYTarget.first - XYCoOrdinates.first);
					difference_y1y2 = (XYTarget.second - XYCoOrdinates.second);

					// Convert the change values to positives;
					if (difference_x1x2 < 0)
						difference_x1x2 *= -1;
					if (difference_y1y2 < 0)
						difference_y1y2 *= -1;

					// Calculate the angle of the trajectory from the x-axis
					trajectory_angleA = atan(difference_y1y2 / difference_x1x2);
					trajectory_angleA *= (360/(2*3.141)); // Convert to degrees from rads

					// Calculate the x component of the trajectory
					x_step = pathSpeed * cos(trajectory_angleA * (3.14159265/180));

					// Calculate the y component of the trajectory
					y_step = pathSpeed * sin(trajectory_angleA * (3.14159265/180));

					std::cout << "cameraFocusHandler::updateFocus : " <<
					          "Trajectory angle from the x-axis: " << trajectory_angleA <<
					          std::endl;

					std::cout << "cameraFocusHandler::updateFocus : " <<
					          ": Trajectoy x component: " << x_step <<
					          std::endl;

					std::cout << "cameraFocusHandler::updateFocus : " <<
					          ": Trajectoy y component: " << y_step <<
					          std::endl;

					std::cout << "cameraFocusHandler::updateFocus : X1-X2 = " <<
					          difference_x1x2 << ", Y1-Y2=" << difference_y1y2 << std::endl;


					_inPath = true;
				}

				if (XYTarget.first > XYCoOrdinates.first)
					XYCoOrdinates.first += x_step;
				else if (XYTarget.first < XYTarget.first)
					XYCoOrdinates.first -= x_step;

				if (XYTarget.second > XYCoOrdinates.second)
					XYCoOrdinates.second += y_step;
				else if (XYTarget.second < XYCoOrdinates.second)
					XYCoOrdinates.second -= y_step;

				lastMoveTime = SDL_GetTicks();
			}

			/*
			Check if we are inside a acceptable range
			of XYTarget. -/+ 0.9 is acceptable.
			*/
			if ((+XYCoOrdinates.first < (+(XYTarget.first + x_step) + 0.9) &&
			        +XYCoOrdinates.first > (+(XYTarget.first - x_step) - 0.9)) &&
			        (+XYCoOrdinates.second < (+(XYTarget.second + y_step) + 0.9) &&
			         +XYCoOrdinates.second > (+(XYTarget.second - y_step) - 0.9))) {
				XYCoOrdinates.first = XYTarget.first;
				XYCoOrdinates.second = XYTarget.second;
				followTag = VIEW_XY;
				_inPath = false;
				std::cout << "cameraFocusHandler::updateFocus : " <<
				          "Path complete" << std::endl;
			}


		break;

		default:
			// Nothing needs to be done.
		break;
	}

	/*
	    My earlier version changed the focus directly, but It seemed like it might
	   be a less intuitive design than I had initially imagined. But this is where the
	   code would be.
	*/
}

bool cameraFocusHandler::inPath(void)
{
	return _inPath;
}

float cameraFocusHandler::getX(void)
{
	return XYCoOrdinates.first;
}

float cameraFocusHandler::getY(void)
{
	return XYCoOrdinates.second;
}
