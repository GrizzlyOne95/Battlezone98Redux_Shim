/*
 * Entry: 0053083f
 * Name: LauncherInterface::~LauncherInterface
 * Namespace: LauncherInterface
 * Signature: void ~LauncherInterface(LauncherInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LauncherInterface::~LauncherInterface(LauncherInterface *this)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
