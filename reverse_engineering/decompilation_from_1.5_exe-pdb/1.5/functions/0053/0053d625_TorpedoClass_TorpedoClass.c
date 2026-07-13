/*
 * Entry: 0053d625
 * Name: TorpedoClass::TorpedoClass
 * Namespace: TorpedoClass
 * Signature: TorpedoClass * TorpedoClass(TorpedoClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TorpedoClass * __thiscall TorpedoClass::TorpedoClass(TorpedoClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  this->setAltitude = 1.0;
  this->_padding_ = 0;
  this->alphaTrack = 20.0;
  this->soundThrust[4] = '\0';
  this->soundThrust[5] = '\0';
  this->soundThrust[6] = '\0';
  this->soundThrust[7] = '\0';
  this->soundThrust[0] = '\0';
  this->soundThrust[1] = '\0';
  this->alphaDamp = 5.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x544f5250;
  this->velocForward = 25.0;
  this->_padding_ = (int)"torpedo";
  this->accelThrust = 10.0;
  this->omegaTurn = 1.0;
  this->alphaSteer = 5.0;
  this->lifeSpan = 60.0;
  this->xplBlast = (ExplosionClass *)0x0;
  return this;
}
