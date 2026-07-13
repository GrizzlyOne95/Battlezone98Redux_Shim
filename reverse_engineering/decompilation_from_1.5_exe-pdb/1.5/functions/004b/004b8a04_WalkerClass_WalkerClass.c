/*
 * Entry: 004b8a04
 * Name: WalkerClass::WalkerClass
 * Namespace: WalkerClass
 * Signature: WalkerClass * WalkerClass(WalkerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WalkerClass * __thiscall WalkerClass::WalkerClass(WalkerClass *this)

{
  CraftClass::CraftClass((CraftClass *)this);
  this->parameters[0].alphaDamp = 5.0;
  this->parameters[0].alphaTrack = 10.0;
  this->parameters[0].pitchPitch = 0.2;
  this->_padding_ = (int)&_vftable_;
  this->parameters[0].pitchThrust = 0.1;
  this->_padding_ = 0x57414c4b;
  this->parameters[0].rollStrafe = 0.1;
  this->_padding_ = (int)"walker";
  this->_padding_ = 5;
  this->parameters[0].velocForward = 0.0;
  this->_padding_ = 0xe;
  this->parameters[0].velocReverse = 0.0;
  this->parameters[0].velocStrafe = 0.0;
  this->parameters[0].accelThrust = 20.0;
  this->parameters[0].omegaSpin = 0.5;
  this->parameters[0].omegaTurn = 0.5;
  this->parameters[0].alphaSteer = 5.0;
  this->parameters[0].velocJump = 0.0;
  this->parameters[1].alphaDamp = 8.0;
  this->parameters[1].alphaTrack = 15.0;
  this->parameters[1].pitchPitch = 0.25;
  this->parameters[1].pitchThrust = 0.1;
  this->parameters[1].rollStrafe = 0.1;
  this->parameters[1].velocForward = 4.0;
  this->parameters[1].velocReverse = 3.0;
  this->parameters[1].velocStrafe = 3.0;
  this->parameters[1].omegaSpin = 3.0;
  this->parameters[1].accelThrust = 20.0;
  this->parameters[1].omegaTurn = 2.0;
  this->parameters[2].alphaDamp = 2.0;
  this->parameters[1].alphaSteer = 5.0;
  this->parameters[2].alphaTrack = 5.0;
  this->parameters[1].velocJump = 10.0;
  this->parameters[2].pitchPitch = 0.5;
  this->parameters[2].pitchThrust = 0.2;
  this->parameters[2].rollStrafe = 0.2;
  this->parameters[2].velocForward = 15.0;
  this->parameters[2].velocReverse = 10.0;
  this->parameters[2].velocStrafe = 10.0;
  this->parameters[2].accelThrust = 0.5;
  this->parameters[2].omegaSpin = 2.0;
  this->parameters[2].omegaTurn = 1.5;
  this->parameters[2].alphaSteer = 0.5;
  this->parameters[2].velocJump = 0.0;
  strncpy(this->jumpSound,"jump.wav",0x10);
  strncpy(this->landSound,"land.wav",0x10);
  strncpy(this->stepSound,"step.wav",0x10);
  this->animRate = 1.0;
  return this;
}
