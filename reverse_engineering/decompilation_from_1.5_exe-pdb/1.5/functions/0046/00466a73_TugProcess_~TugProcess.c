/*
 * Entry: 00466a73
 * Name: TugProcess::~TugProcess
 * Namespace: TugProcess
 * Signature: void ~TugProcess(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::~TugProcess(TugProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
