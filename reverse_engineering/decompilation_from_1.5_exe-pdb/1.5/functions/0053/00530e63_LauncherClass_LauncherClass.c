/*
 * Entry: 00530e63
 * Name: LauncherClass::LauncherClass
 * Namespace: LauncherClass
 * Signature: LauncherClass * LauncherClass(LauncherClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LauncherClass * __thiscall LauncherClass::LauncherClass(LauncherClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x4c4e4348;
  this->_padding_ = (int)"launcher";
  strncpy((char *)&this->_padding_,"wrock.wav",0x10);
  this->lockRange = 0.0;
  this->shotDelay = 1.0;
  this->lockedReticle = this->_padding_;
  this->lockingReticle = this->_padding_;
  this->lockDelay = 5.0;
  this->ammoCost = 0;
  this->coneAngle = 1.5707964;
  this->lockedSound[0] = '\0';
  this->lockingSound[0] = '\0';
  this->targetCount = 0;
  this->targetReticle = (int *)0x0;
  return this;
}
