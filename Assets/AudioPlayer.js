#pragma strict

var leftDrum : AudioClip;
var play : boolean;
var timer : float;
var time : float;

function Start () {
	play = true;
	timer = 0.0;
}

function Update () {
	timer += Time.deltaTime;
	if(timer >= time && !play){
		play = true;
	}
}

function OnTriggerEnter () {
	if(play){
		GetComponent.<AudioSource>().PlayOneShot(leftDrum);
		play = false;
		timer = 0.0;

	}
}