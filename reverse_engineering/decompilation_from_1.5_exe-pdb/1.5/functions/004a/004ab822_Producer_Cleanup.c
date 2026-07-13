/*
 * Entry: 004ab822
 * Name: Producer::Cleanup
 * Namespace: Producer
 * Signature: void Cleanup(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::Cleanup(Producer *this)

{
  bool bVar1;
  
  bVar1 = IsBusy(this);
  if (bVar1) {
    CancelBuild(this);
  }
  Team::AddMaxScrap((Team *)this->_padding_,-*(int *)(this->_padding_ + 0x3d0));
  Team::AddMaxPilot((Team *)this->_padding_,-*(int *)(this->_padding_ + 0x3d4));
  Craft::Cleanup((Craft *)this);
  return;
}
