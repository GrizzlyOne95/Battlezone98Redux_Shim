/*
 * Entry: 0041040f
 * Name: BuildGoto::~BuildGoto
 * Namespace: BuildGoto
 * Signature: void ~BuildGoto(BuildGoto * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BuildGoto::~BuildGoto(BuildGoto *this)

{
  bool bVar1;
  
  this->_padding_ = (int)&_vftable_;
  bVar1 = Producer::IsBusy((Producer *)this->_padding_);
  if (bVar1) {
    Producer::CancelBuild((Producer *)this->_padding_);
  }
  GotoTask::~GotoTask((GotoTask *)this);
  return;
}
