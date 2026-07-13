/*
 * Entry: 00530ee8
 * Name: LauncherClass::~LauncherClass
 * Namespace: LauncherClass
 * Signature: void ~LauncherClass(LauncherClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LauncherClass::~LauncherClass(LauncherClass *this)

{
  this->_padding_ = (int)&_vftable_;
  operator_delete__(this->targetReticle);
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
