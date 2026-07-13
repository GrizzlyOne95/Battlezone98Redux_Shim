/*
 * Entry: 004acd82
 * Name: Recycler::Simulate
 * Namespace: Recycler
 * Signature: void Simulate(Recycler * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Recycler::Simulate(Recycler *this,float param_1)

{
  int iVar1;
  
  if (this->_padding_ == 0) {
    iVar1 = this->scrapDropoff;
    if (-1 < iVar1) {
      ScrapDropoff_Get(iVar1);
      this->scrapDropoff = -1;
    }
  }
  Producer::Simulate((Producer *)this,param_1);
  return;
}
