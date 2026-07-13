/*
 * Entry: 005307c9
 * Name: Launcher::Trigger
 * Namespace: Launcher
 * Signature: void Trigger(Launcher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Launcher::Trigger(Launcher *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
