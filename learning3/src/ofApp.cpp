#include "ofApp.h"

//--------------------------------------------------------------
ofApp::ofApp() {
}
ofApp::~ofApp() {
}

void ofApp::setup(){

	// Loading Things

	// Easycam Setup
	// cam.setDistance(200);
	// webcam.setup(640, 480);

	// ##### OF Settings

	//ofEnableSmoothing(); // only affects lines
	//ofSetCircleResolution(50); // only affect circles

	font.load("OpenSans-Light.ttf", 10);
	infoText.push_back("1,2,3 to select active layer");
	infoText.push_back("z,x,c,v,.. to start simulations");
	//infoText.push_back("take you somewhere nice");
	//infoText.push_back("Kaspar Ravel");

	// ##### Main GUI Setup

	overlay.setup(); 
	mainGroup.add(overlay.params);
	mainMenu.setup(mainGroup);

	// ##### Layer System
	//allocating the vector with 3 empty/basic objects
	myLayers.resize(NUMLAYERS);

	//temporary layer object that will be copied into the vector
	//Layer tempLayer;
	for (int i = 0; i < myLayers.size(); ++i)
	{
		shared_ptr<Layer> tempPtr(new Layer(i + 1));
		//tempLayer = Layer(i + 1);
		myLayers.at(i) = tempPtr;
		//setup layer
		myLayers.at(i)->setup(Scene_Default);

		//layers[i] = new Layer(i + 1);
		//layers[i]->setup(Scene_Default);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	//webcam.update();

	// # Fullscreen toggle doesn't work with keyboard f for fullscreen
	// if (fullScreenToggle) ofSetFullscreen(true); else ofSetFullscreen(false);

	// # Play Drag & Dropped Video
	//for (int v = 0; v < dropImage.size(); v++) dropVideo[v].update();

	// ##### Layer System
	// ##### update very layer

	//change to vector syntax
	for (int i = 0; i < myLayers.size(); ++i)
	{
		myLayers.at(i)->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// # Display General Info 

	ofSetColor(255);                                                                 // MAKE THIS COLOR BE THE CONTRARY OF THE BACKGROUND MENU, or always +100 - 100 somth, like relative
	
	infoText.push_back("Current FPS : " + to_string(ofGetFrameRate()));
	for (size_t i = 0; i < infoText.size(); i++)
	{
		float w = ofGetWidth() - font.stringWidth(infoText[i]) - 10;
		float h = 20 + i * (font.stringHeight(infoText[i]) + 5);
		font.drawString(infoText[i], w , h);
	}
	infoText.pop_back();

	// # Display Layer Info

	for (int i = 0; i < myLayers.size(); ++i)
	{
		string active = "";
		//change to vector syntax
		if (myLayers.at(i)->isActiveLayer()) { active = "> "; }
		string number = std::to_string(i+1);
		string text = active + "Layer " + number;
		float w = ofGetWidth() - 55;
		float h = 20 + i * ((font.stringHeight(text)) + 5);
		h += (font.stringHeight(infoText[0])) * infoText.size() + 20;
		//h += +5 + (font.stringHeight(infoText[0]) + 5)
		font.drawString(text, w, h);
	} 
	

	// ##### Main GUI Draw

	overlay.draw(); 

	// ##### Layer System
	// ##### draw every layer

	for (int i = 0; i < myLayers.size(); ++i) // draw every layer
	{
		//change to vector syntax
		myLayers.at(i)->draw();
	}

	// ##### Main GUI Draw ( wait why do I have two of these again ?)

	mainMenu.draw();

	// Set Blend Mode
	//ofEnableBlendMode(OF_BLENDMODE_ADD);

	// Translate d
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	// Webcam 
	//webcam.draw((ofGetWidth() / 2) - 360, (ofGetHeight() / 2) - 240, 360, 240);

	// EasyCam Begin
	//cam.begin();

	// ##### Examples of Drawing things in 3D space

	// Rotating tests
	//ofRotateXRad(ofDegToRad(rotate));
	//ofDrawBox(128);

	//ofDrawLine(0, 0, 50, 50);
	//ofDrawBezier(704, 64, 736, 128, 768, 160, 800, 64);
	//ofDrawBox(64, 256, 0, 64, 64, 64);
	//ofDrawPlane(100, 100, 100, 100);

	// Drag and Drop Image && Video
	//for (int i = 0; i < dropImage.size(); i++) dropImage[i].draw(0 - dropImage[i].getWidth() / 2, 0 - dropImage[i].getHeight() / 2);
	//for (int v = 0; v < dropImage.size(); v++) dropVideo[v].draw(0 - dropVideo[v].getWidth() / 2, 0 - dropVideo[v].getHeight() / 2);
	
	// EasyCam End
	//cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case ' ':
		// used for testing things

		myLayers.clear();
		myLayers.resize(3);
		for (int i = 0; i < myLayers.size(); ++i)
		{
			shared_ptr<Layer> tempPtr(new Layer(i + 1));
			//tempLayer = Layer(i + 1);
			myLayers.at(i) = tempPtr;
			//setup layer
			myLayers.at(i)->setup(Scene_Default);

			//layers[i] = new Layer(i + 1);
			//layers[i]->setup(Scene_Default);
		}

		break;
	case 'p':
	{
		//text = "taking screenshot";
		imgScreenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string filename = "screenshot_" + ofToString(screenshotCount, 5, '0') + ".png";
		imgScreenshot.save(filename);
		screenshotCount++;
		break;
	}
	case 'f':
		ofToggleFullscreen();
		fbo.allocate(ofGetWidth(), ofGetHeight());
		fbo.begin();
		ofClear(255);
		fbo.end();
		break;
		
	case 'z': startScene(Scene_DiffLine); break;
	case 'x': startScene(Scene_DLA); break;
	case 'c': startScene(Scene_Boids); break;
	case 'v': startScene(Scene_ShaderTest); break;
	case 'b': startScene(Scene_Julia2D); break;
	case 'n': startScene(Scene_SimplexTerrain); break;
	case 'm': startScene(Scene_DomainWarping); break;
	case ',': startScene(Scene_SpaceColonization); break;
	//change to vector syntax
	case '1':	myLayers.at(0)->setActiveLayer(); break;
	case '2':	myLayers.at(1)->setActiveLayer(); break;
	case '3':	myLayers.at(2)->setActiveLayer(); break;
	//case '4':	activeLayer = 4; break;
	//case '5':	activeLayer = 5; break;
	//case '6':	activeLayer = 6; break;
	//case '7':	activeLayer = 7; break;
	//case '8':	activeLayer = 8; break;
	//case '9':	activeLayer = 9; break;
	default: break;
	}
}

// ###### Start Scene and Delete Old one Before

void ofApp::startScene(SceneType Type) {
	//same es in setup()
	Layer tempLayer;

	for (int i = 0; i < myLayers.size(); ++i)
	{
		if (myLayers.at(i)->isActiveLayer())
		{			
			
			shared_ptr<Layer> tempPtr(new Layer(i + 1));
			//tempLayer = Layer(i + 1);
			myLayers.at(i) = tempPtr;
			//setup layer
			myLayers.at(i)->setup(Type);

			//layers[i] = new Layer(i + 1);
			//layers[i]->setup(Type);
			break;
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	// # Drag and Drop Sound // Images // Videos
	if (dragInfo.files.size() > 0)
	{
		dropSound.assign(dragInfo.files.size(), ofSoundPlayer());
		for (int s = 0; s < dragInfo.files.size(); s++)
		{
			dropSound[s].load(dragInfo.files[s]);
			dropSound[s].play();
			dropSound[s].setVolume(0.6);
			dropSound[s].setLoop(true);
		}
	}

	if (dragInfo.files.size() > 0)
	{
		dropImage.assign(dragInfo.files.size(), ofImage());
		for (int i = 0; i < dragInfo.files.size(); i++)
		{
			dropImage[i].load(dragInfo.files[i]);
		}
	}

	if (dragInfo.files.size() > 0)
	{
		dropVideo.assign(dragInfo.files.size(), ofVideoPlayer());
		for (int v = 0; v < dragInfo.files.size(); v++)
		{
			dropVideo[v].load(dragInfo.files[v]);
			dropVideo[v].play();
		}
	}
}