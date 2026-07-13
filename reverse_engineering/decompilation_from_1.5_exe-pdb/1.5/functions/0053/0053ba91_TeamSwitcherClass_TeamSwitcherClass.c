/*
 * Entry: 0053ba91
 * Name: TeamSwitcherClass::TeamSwitcherClass
 * Namespace: TeamSwitcherClass
 * Signature: TeamSwitcherClass * TeamSwitcherClass(TeamSwitcherClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TeamSwitcherClass * __thiscall TeamSwitcherClass::TeamSwitcherClass(TeamSwitcherClass *this)

{
  RocketClass::RocketClass((RocketClass *)this);
  this->switchTime = 10.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x544d5357;
  this->_padding_ = (int)"switcher";
  return this;
}
