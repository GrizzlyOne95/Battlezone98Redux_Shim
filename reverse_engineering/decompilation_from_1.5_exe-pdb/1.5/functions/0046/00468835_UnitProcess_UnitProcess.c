/*
 * Entry: 00468835
 * Name: UnitProcess::UnitProcess
 * Namespace: UnitProcess
 * Signature: UnitProcess * UnitProcess(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnitProcess * __thiscall UnitProcess::UnitProcess(UnitProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->curState = NO_STATE;
  this->me = (Craft *)0x0;
  this->task = (AiTask *)0x0;
  this->where = (AiPath *)0x0;
  this->release = false;
  this->whoHandle = 0;
  this->saveState = NO_STATE;
  this->saveWho = 0;
  this->isInTransition = false;
  this->skipSay = false;
  this->whatClass = (GameObjectClass *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->nextState = WAIT;
  this->exact = true;
  this->independence = 1;
  this->wasInTransition = true;
  return this;
}
