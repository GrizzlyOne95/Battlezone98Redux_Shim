/*
 * Entry: 004b0717
 * Name: ScrapSilo::Cleanup
 * Namespace: ScrapSilo
 * Signature: void Cleanup(ScrapSilo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapSilo::Cleanup(ScrapSilo *this)

{
  int iVar1;
  
  Team::AddMaxScrap((Team *)this->_padding_,-*(int *)(this->_padding_ + 0x160));
  iVar1 = this->dropoff;
  if (-1 < iVar1) {
    ScrapDropoff_Get(iVar1);
    this->dropoff = -1;
  }
  Building::Cleanup((Building *)this);
  return;
}
