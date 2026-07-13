/*
 * Entry: 004acd5f
 * Name: Recycler::Cleanup
 * Namespace: Recycler
 * Signature: void Cleanup(Recycler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Recycler::Cleanup(Recycler *this)

{
  int iVar1;
  
  iVar1 = this->scrapDropoff;
  if (-1 < iVar1) {
    ScrapDropoff_Get(iVar1);
    this->scrapDropoff = -1;
  }
  Producer::Cleanup((Producer *)this);
  return;
}
