/*
 * Entry: 0040c631
 * Name: ArmoryProcess::ArmoryProcess
 * Namespace: ArmoryProcess
 * Signature: ArmoryProcess * ArmoryProcess(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArmoryProcess * __thiscall ArmoryProcess::ArmoryProcess(ArmoryProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->curState = START;
  this->craft = (Armory *)0x0;
  this->where = (AiPath *)0x0;
  this->release = false;
  this->whoHandle = 0;
  this->task = (AiTask *)0x0;
  this->classtobuild = (GameObjectClass *)0x0;
  this->target = (GameObject *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->nextState = WAIT;
  this->wasInTransition = true;
  return this;
}
