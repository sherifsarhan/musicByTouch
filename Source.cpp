/*
	Testing this shit out to see if i can get this to work
*/

#include <iostream>
#include <cstring>
// looks like we absolutely need this here. oh well
#include <Windows.h>
#include <mmsystem.h>
#include "Leap.h"
#pragma comment(lib, "winmm.lib") 

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
		void playNote(const std::string hand);
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

	//gesture config settings
	controller.config().setFloat("Gesture.Swipe.MinLength", 50.0);
	controller.config().setFloat("Gesture.Swipe.MinVelocity", 20);
	controller.config().save();
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
	
	SwipeGesture swipeGesture = Gesture::invalid();
	GestureList gestures = frame.gestures();
	Gesture goodGesture;
	for (GestureList::const_iterator g1 = gestures.begin(); g1 != gestures.end(); ++g1) {
		const Gesture gesture = *g1;
		if (gesture.type() == Gesture::Type::TYPE_SWIPE) {
			swipeGesture = SwipeGesture(gesture);
			Vector swipeVector = swipeGesture.direction();
			if (swipeVector.y < 0) {
				//std::cout << swipeVector.y << std::endl;
				goodGesture = gesture;
			}
		}
	}
	HandList hands = goodGesture.hands();
	// iterates through the list and calls the object h1
	for (HandList::const_iterator h1 = hands.begin(); h1 != hands.end(); ++h1) {
		// getting the hand from the list address
		const Hand hand = *h1;
		std::string handtype;
		Vector handPosition;
		float height;
		// this means both hands can't be detected from the same gesture
		if (hand.isLeft()) {
			handtype = "Left";
			handPosition = hand.palmPosition();
			height = handPosition.y;
			playNote(handtype);
			//std::cout << height << std::endl;
		}
		else if (hand.isRight()) {
			handtype = "Right";
			handPosition = hand.palmPosition();
			height = handPosition.y;
			playNote(handtype);
			//std::cout << height << std::endl;
		}
		else {
			//PlaySound(NULL, 0, 0);
		}
	}
	
	// a bunch of random info
	/*
	// Commenting out for now while I try to only detect fingers
	std::cout << "Frame id: " << frame.id()
		<< ", timestamp: " << frame.timestamp()
		<< ", hands: " << frame.hands().count()
		<< ", extended fingers: " << frame.fingers().extended().count()
		<< ", tools: " << frame.tools().count()
		<< ", gestures: " << frame.gestures().count() << std::endl;
	
	
		
		//std::cout << std::string(4, ' ') << handtype << std::endl;
		
		// gettings the fingers
		/*const FingerList fingers = hand.fingers();
		for (FingerList::const_iterator f1 = fingers.begin(); f1 != fingers.end(); ++f1) {
			const Finger finger = *f1;
			std::string extendedFinger = "None";
			if (finger.isExtended())
			{
				extendedFinger = fingerNames[finger.type()];
				std::cout << extendedFinger;
			}
			std::cout << std::endl;
		}*/
	//}*/

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

void MusicByTouchListener::playNote(const std::string hand) {
	//PlaySound((LPCSTR)"VEC5 Jump Kicks 30.wav", NULL, SND_FILENAME);
	// | SND_ASYNC
	if(hand == "Left") sndPlaySound("left.wav", SND_FILENAME);
	else sndPlaySound("right.wav", SND_FILENAME);

}

int main(int argc, char** argv){
	using namespace std;
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
	cin.get();

	// remove the sample listener to free up the controller
	controller.removeListener(list);
	return 0;
}