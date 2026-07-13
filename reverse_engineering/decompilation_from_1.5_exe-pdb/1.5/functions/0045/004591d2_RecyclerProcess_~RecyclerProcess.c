/*
 * Entry: 004591d2
 * Name: RecyclerProcess::~RecyclerProcess
 * Namespace: RecyclerProcess
 * Signature: void ~RecyclerProcess(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::~RecyclerProcess(RecyclerProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
