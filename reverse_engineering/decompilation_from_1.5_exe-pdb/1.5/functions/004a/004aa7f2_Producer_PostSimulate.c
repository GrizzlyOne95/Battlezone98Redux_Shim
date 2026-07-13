/*
 * Entry: 004aa7f2
 * Name: Producer::PostSimulate
 * Namespace: Producer
 * Signature: void PostSimulate(Producer * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::PostSimulate(Producer *this,float param_1)

{
  if (this->_padding_ == 0) {
    HoverCraft::PostSimulate((HoverCraft *)this,param_1);
  }
  else {
    Craft::PostSimulate((Craft *)this,param_1);
  }
  return;
}
