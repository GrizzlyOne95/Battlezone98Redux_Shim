/*
 * Entry: 00530800
 * Name: LauncherInterface::LauncherInterface
 * Namespace: LauncherInterface
 * Signature: LauncherInterface * LauncherInterface(LauncherInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LauncherInterface * __thiscall LauncherInterface::LauncherInterface(LauncherInterface *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,5);
  DisplayInterface::AddView((DisplayInterface *)this,2,5);
  DisplayInterface::AddView((DisplayInterface *)this,1,5);
  this->state[0] = 0;
  this->state[1] = 0;
  this->state[2] = 0;
  this->state[3] = 0;
  this->state[4] = 0;
  return this;
}
