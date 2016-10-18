/*
	Testing this shit out to see if i can get this to work
*/

#include <iostream>
#include <cstring>
#include "Leap.h"

using namespace Leap;

// inherting from the Listener Class
class MusicByTouchListener : public Listener{
	public:
		virtual void onInit(const Controller&);
		virtual void onConnect(const Controller&);
		virtual void onDisconnect(const Controller&);
		virtual void onExit(const Controller&);
		virtual void onFrame(const Controller&);
		virtual void onFocusGained(const Controller&);
		virtual void onFocusLost(const Controller&);
		virtual void onDeviceChange(const Controller&);
		virtual void onServiceConnect(const Controller&);
		virtual void onServiceDisconnect(const Controller&);
	private:
};

const std::string fingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string boneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };
const std::string stateNames[] = { "STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END" };

// creating bodies for the virtual functions in SampleListener
void MusicByTouchListener::onInit(const Controller& controller){
	std::cout << "Initialized" << std::endl;
}

// for now i'm just gonna add a bunch of fake functions that print stuff out
void MusicByTouchListener::onConnect(const Controller& controller){
	std::cout << "Connected" << std::endl;
	
	// making sure to enable gesture reading
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void MusicByTouchListener::onDisconnect(const Controller& controller) {
	std::cout << "Disconnecting" << std::endl;
}

void MusicByTouchListener::onExit(const Controller& controller) {
	std::cout << "Exiting" << std::endl;
}

void MusicByTouchListener::onFrame(const Controller& controller) {
	// ouputting frame info at each frame capture
	const Frame frame = controller.frame();
	std::cout << "Frame id: " << frame.id() << std::endl;
}

void MusicByTouchListener::onFocusGained(const Controller& controller) {
	std::cout << "Focusing" << std::endl;
}

void MusicByTouchListener::onFocusLost(const Controller& controller) {
	std::cout << "Losing Focus" << std::endl;
}

void MusicByTouchListener::onDeviceChange(const Controller& controller) {
	std::cout << "Changing Devices" << std::endl;
}

void MusicByTouchListener::onServiceConnect(const Controller& controller) {
	std::cout << "Connecting to Service" << std::endl;
}

void MusicByTouchListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Disconnecting from Service" << std::endl;
}

int main(int argc, char** argv){
	// Creating the sample listener and controller
	MusicByTouchListener list;
	Controller controller;

	// connecting the listener to the controller
	controller.addListener(list);

	// i don't know what this is doing
	// seems like its some commandline argument thing
	if (argc > 1 && strcmp(argv[1], "--bg") == 0) {
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
	}

	// press enter to quit the program
	std::cin.get();

	// remove the sample listener to free up the controller
	controller.removeListener(list);
	return 0;
}