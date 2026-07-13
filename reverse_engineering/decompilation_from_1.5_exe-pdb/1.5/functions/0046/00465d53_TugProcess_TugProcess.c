/*
 * Entry: 00465d53
 * Name: TugProcess::TugProcess
 * Namespace: TugProcess
 * Signature: TugProcess * TugProcess(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TugProcess * __thiscall TugProcess::TugProcess(TugProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->dropoffPoint = 0.0;
  this->curState = START;
  this->craft = (Craft *)0x0;
  this->task = (AiTask *)0x0;
  this->whoHandle = 0;
  this->hitchCargo = (_OBJ76 *)0x0;
  this->hitchTug = (_OBJ76 *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->nextState = WAIT;
  return this;
}
