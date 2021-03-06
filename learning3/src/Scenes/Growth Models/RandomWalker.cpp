#include "RandomWalker.h"

RandomWalker::RandomWalker(float x, float y, float z, float walk, float stick, float colorInterpol) {

	position.set(x, y, z);
	randomWalk = walk; 
	radius = ofRandom(1,3);
	sticky = stick;
	ci = colorInterpol;
}

RandomWalker::RandomWalker(string spawn, float walk, float stick, float colorInterpol, bool is3D) {

	randomWalk = walk;
	radius = ofRandom(1, 3);
	sticky = stick;
	ci = colorInterpol;

	float w = ofGetWidth();
	float h = ofGetHeight();

	if (!is3D)
	{
		if (spawn == "walls")
		{
			int wall = (int)ofRandom(1, 5);
			switch (wall) {
			case 1: // NORTH
				position.x = ofRandom(-w / 2, w / 2);
				position.y = h / 2;
				position.z = 0;
				break;
			case 2: // EAST
				position.x = w / 2;
				position.y = ofRandom(-h / 2, h / 2);
				position.z = 0;
				break;
			case 3: // SOUTH
				position.x = ofRandom(-w / 2, w / 2);
				position.y = -h / 2;
				position.z = 0;
				break;
			case 4: // WEST
				position.x = -w / 2;
				position.y = ofRandom(-h / 2, h / 2);
				position.z = 0;
				break;
			default:
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-h / 2, h / 2);
				position.z = 0;
			}
		}
		else if (spawn == "random")
		{
			position.x = ofRandom(-w / 2, w / 2);
			position.y = ofRandom(-h / 2, h / 2);
			position.z = 0;
		}
	}
	else // its 3D !
	{
		if (spawn == "walls")
		{
			int wall = (int)ofRandom(1, 7);
			switch (wall) {
			case 1: // FRONT
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-w / 2, w / 2);
				position.z = w / 2;
				break;
			case 2: // BACK
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-w / 2, w / 2);
				position.z = - w / 2;
				break;
			case 3: // TOP
				position.x = ofRandom(-w / 2, w / 2);
				position.y = w / 2;
				position.z = ofRandom(-w / 2, w / 2);
				break;
			case 4: // BOTTOM
				position.x = ofRandom(-w / 2, w / 2);
				position.y = - w / 2;
				position.z = ofRandom(-w / 2, w / 2);
				break;
			case 5: // LEFT
				position.x = -w / 2;
				position.y = ofRandom(-w / 2, w / 2);
				position.z = ofRandom(-w / 2, w / 2);
				break;
			case 6: // RIGHT
				position.x = w / 2;
				position.y = ofRandom(-w / 2, w / 2);
				position.z = ofRandom(-w / 2, w / 2);
				break;
			default:
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-w / 2, w / 2);
				position.z = ofRandom(-w / 2, w / 2);
			}
		}
		else if (spawn == "random")
		{
			position.x = ofRandom(-w / 2, w / 2);
			position.y = ofRandom(-w / 2, w / 2);
			position.z = ofRandom(-w / 2, w / 2);
		}
	}
}


void RandomWalker::update() {
	walk();
	position += velocity;

	// Clamp Values to world space
	position.x = ofClamp(position.x, -ofGetWidth() / 2, ofGetWidth() / 2);
	position.y = ofClamp(position.y, -ofGetWidth() / 2, ofGetWidth() / 2);

	velocity.set(0, 0, 0);
}

void RandomWalker::debugDraw()
{
	ofSetColor(255, 0, 0, 255);
	ofDrawCircle(position.x, position.y, radius);
	ofSetColor(255, 255, 255, 255);
}

void RandomWalker::applyForce(ofVec3f force) {
	velocity += force;
}

void RandomWalker::walk() {
	velocity.x += ofRandom(-randomWalk, randomWalk);
	velocity.y += ofRandom(-randomWalk, randomWalk);
}






