/*
 * Entry: 0049efc7
 * Name: HoverCraftClass::HoverCraftClass
 * Namespace: HoverCraftClass
 * Signature: HoverCraftClass * HoverCraftClass(HoverCraftClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HoverCraftClass * __thiscall HoverCraftClass::HoverCraftClass(HoverCraftClass *this)

{
  CraftClass::CraftClass((CraftClass *)this);
  this->setAltitude = 1.0;
  this->accelDragStop = 4.0;
  this->accelDragFull = 1.0;
  this->_padding_ = (int)&_vftable_;
  this->alphaTrack = 0.01;
  this->_padding_ = 0x484f5652;
  this->_padding_ = (int)"hover";
  this->pitchPitch = 3.0;
  this->alphaDamp = 10.0;
  this->pitchThrust = 0.3;
  this->rollStrafe = 0.1;
  this->rollSteer = 0.1;
  this->rollStrafRotator[0] = 0.1;
  this->velocForward = 20.0;
  this->velocReverse = 10.0;
  this->velocStrafe = 15.0;
  this->accelThrust = 25.0;
  this->accelBrake = 75.0;
  this->omegaSpin = 4.0;
  this->omegaTurn = 1.5;
  this->alphaSteer = 5.0;
  this->accelJump = 0.1;
  this->rollStrafRotator[1] = 0.4;
  this->rollSteerFin[0] = 0.2;
  this->rollSteerFin[1] = 0.2;
  this->pitchSteerNacelle[0] = 0.2;
  this->soundThrust[0] = -0x33;
  this->soundThrust[1] = -0x34;
  this->soundThrust[2] = 'L';
  this->soundThrust[3] = '>';
  this->pitchThrotNacelle[0] = 0.1;
  this->pitchThrotNacelle[1] = 0.4;
  this->pitchSteerNacelle[1] = 0.4;
  strncpy(this->soundThrust + 4,"engthrst.wav",0x10);
  strncpy(this->soundTurbo + 4,"engrev.wav",0x10);
  strncpy(this->soundFly + 4,"amb_wind.wav",0x10);
  strncpy(this->soundDeploy + 4,"trdeploy.wav",0x10);
  strncpy(this->soundUndeploy + 4,"trundepl.wav",0x10);
  return this;
}
