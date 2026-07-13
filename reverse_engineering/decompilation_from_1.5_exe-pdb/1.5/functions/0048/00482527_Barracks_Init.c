/*
 * Entry: 00482527
 * Name: Barracks::Init
 * Namespace: Barracks
 * Signature: void Init(Barracks * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Barracks::Init(Barracks *this,int param_1)

{
  Building::Init((Building *)this,param_1);
  Team::AddMaxPilot((Team *)this->_padding_,*(long *)(this->_padding_ + 0x160));
  Team::AddPilot((Team *)this->_padding_,*(long *)(this->_padding_ + 0x160));
  return;
}
