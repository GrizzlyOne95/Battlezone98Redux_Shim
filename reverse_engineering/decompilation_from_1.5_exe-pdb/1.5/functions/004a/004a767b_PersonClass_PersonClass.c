/*
 * Entry: 004a767b
 * Name: PersonClass::PersonClass
 * Namespace: PersonClass
 * Signature: PersonClass * PersonClass(PersonClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonClass * __thiscall PersonClass::PersonClass(PersonClass *this)

{
  CraftClass::CraftClass((CraftClass *)this);
  this->parameters[0].alphaDamp = 5.0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->parameters[0].alphaTrack = 10.0;
  this->parameters[0].pitchPitch = 0.2;
  this->parameters[0].pitchThrust = 0.1;
  this->parameters[0].rollStrafe = 0.1;
  this->_padding_ = (int)&_vftable_;
  this->parameters[0].velocForward = 0.0;
  this->_padding_ = 0x50455253;
  this->parameters[0].velocReverse = 0.0;
  this->_padding_ = (int)"person";
  this->parameters[0].velocStrafe = 0.0;
  this->_padding_ = 4;
  this->_padding_ = 1;
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
  this->parameters[1].velocJump = 5.0;
  this->parameters[2].alphaTrack = 5.0;
  this->parameters[2].pitchPitch = 0.35;
  this->parameters[2].pitchThrust = 0.15;
  this->parameters[2].rollStrafe = 0.15;
  this->parameters[2].velocForward = 15.0;
  this->parameters[2].velocReverse = 10.0;
  this->parameters[2].velocStrafe = 10.0;
  this->parameters[2].accelThrust = 5.0;
  this->parameters[2].omegaSpin = 2.0;
  this->parameters[2].omegaTurn = 1.5;
  this->parameters[2].alphaSteer = 2.0;
  this->parameters[2].velocJump = 0.0;
  strncpy(this->painSound[0],"pain1.wav",0x10);
  strncpy(this->painSound[1],"pain2.wav",0x10);
  strncpy(this->painSound[2],"pain3.wav",0x10);
  strncpy(this->painSound[3],"pain4.wav",0x10);
  strncpy(this->painSound[4],"pain5.wav",0x10);
  strncpy(this->painSound[5],"pain6.wav",0x10);
  strncpy(this->burnSound[0],"lburn1.wav",0x10);
  strncpy(this->burnSound[1],"lburn2.wav",0x10);
  strncpy(this->dieSound[0],"death1.wav",0x10);
  strncpy(this->dieSound[1],"death2.wav",0x10);
  strncpy(this->dieSound[2],"death3.wav",0x10);
  strncpy(this->dieSound[3],"death4.wav",0x10);
  strncpy(this->dieSound[4],"death5.wav",0x10);
  strncpy(this->crushSound,"squish.wav",0x10);
  strncpy(this->jumpSound,"jump.wav",0x10);
  strncpy(this->landSound,"land.wav",0x10);
  strncpy(this->stepSound,"step.wav",0x10);
  this->animRate = 1.0;
  return this;
}
