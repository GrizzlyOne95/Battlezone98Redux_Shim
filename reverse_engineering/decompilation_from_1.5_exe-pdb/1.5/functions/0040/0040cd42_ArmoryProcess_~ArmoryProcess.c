/*
 * Entry: 0040cd42
 * Name: ArmoryProcess::~ArmoryProcess
 * Namespace: ArmoryProcess
 * Signature: void ~ArmoryProcess(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::~ArmoryProcess(ArmoryProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
