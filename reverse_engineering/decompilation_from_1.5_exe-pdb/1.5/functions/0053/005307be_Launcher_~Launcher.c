/*
 * Entry: 005307be
 * Name: Launcher::~Launcher
 * Namespace: Launcher
 * Signature: void ~Launcher(Launcher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Launcher::~Launcher(Launcher *this)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  return;
}
