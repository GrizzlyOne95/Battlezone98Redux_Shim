/*
 * Entry: 004b06f0
 * Name: ScrapSilo::Init
 * Namespace: ScrapSilo
 * Signature: void Init(ScrapSilo * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapSilo::Init(ScrapSilo *this,int param_1)

{
  Building::Init((Building *)this,param_1);
  Team::AddMaxScrap((Team *)this->_padding_,*(long *)(this->_padding_ + 0x160));
  return;
}
