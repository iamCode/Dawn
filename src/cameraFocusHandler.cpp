/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#include "cameraFocusHandler.h"

cameraFocusHandler::cameraFocusHandler()
{
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
	_inPath = true;
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
	_inPath = true;
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
	static float trajectory_angleA = 0.0; // Trajectory angle to the x-axis (tan-1(o/a))
	static bool  calculationsDone = false; // Remeber if the calculation have been done
	std::stringstream ss;

	switch (followTag) {
		case (VIEW_CNPC):
			XYCoOrdinates.first = (float)currentNPC->x_pos-(Configuration::screenWidth/2);
			XYCoOrdinates.second = (float)currentNPC->y_pos-(Configuration::screenHeight/2);
		break;

		case (VIEW_PLAYER):
			XYCoOrdinates.first = (float)currentPlayer->x_pos-(Configuration::screenWidth/2);
			XYCoOrdinates.second = (float)currentPlayer->y_pos-(Configuration::screenHeight/2);
		break;

		case (VIEW_PATH):
			if (SDL_GetTicks()+1000 >= lastMoveTime) {
				// We only want to run the step calculations in the first run of the path
				if (!calculationsDone) {
					ss << "cameraFocusHandler::updateFocus : " <<
					          "Entering path from (" << XYCoOrdinates.first <<
					          ", " << XYCoOrdinates.second << ") to (" <<
					          XYTarget.first << ", " << XYTarget.second <<
					          ") ";
					dawn_debug_info(ss.str());
					ss.str("");

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

					dawn_debug_info ("cameraFocusHandler::updateFocus : "
					          "Trajectory angle from the x-axis: %f", trajectory_angleA);

					dawn_debug_info ("cameraFocusHandler::updateFocus : "
					          "Trajectoy x component=%f", x_step);

					dawn_debug_info ("cameraFocusHandler::updateFocus : "
					          "Trajectoy y component=%f", y_step);

					dawn_debug_info ("cameraFocusHandler::updateFocus : X1-X2 = %f "
					           ", Y1-Y2 = %f", difference_x1x2, difference_y1y2);

					calculationsDone = true;
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
				calculationsDone = false;
				dawn_debug_info("cameraFocusHandler::updateFocus : "
				          "Path complete");
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
