/*
 * Entry: 00458ab9
 * Name: RecyclerProcess::RecyclerProcess
 * Namespace: RecyclerProcess
 * Signature: RecyclerProcess * RecyclerProcess(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecyclerProcess * __thiscall RecyclerProcess::RecyclerProcess(RecyclerProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->lastHit = 0.0;
  this->curState = START;
  this->craft = (Recycler *)0x0;
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
