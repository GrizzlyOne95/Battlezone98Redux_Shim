/*
 * Entry: 004aa7a1
 * Name: Producer::Init
 * Namespace: Producer
 * Signature: void Init(Producer * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::Init(Producer *this,int param_1)

{
  int *piVar1;
  
  Craft::Init((Craft *)this,param_1);
  piVar1 = &this->_padding_;
  Team::AddMaxScrap((Team *)this->_padding_,*(long *)(*piVar1 + 0x3d0));
  Team::AddMaxPilot((Team *)this->_padding_,*(long *)(*piVar1 + 0x3d4));
  Team::AddPilot((Team *)this->_padding_,*(long *)(*piVar1 + 0x3d4));
  return;
}
