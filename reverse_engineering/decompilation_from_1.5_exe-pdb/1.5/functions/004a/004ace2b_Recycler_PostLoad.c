/*
 * Entry: 004ace2b
 * Name: Recycler::PostLoad
 * Namespace: Recycler
 * Signature: bool PostLoad(Recycler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Recycler::PostLoad(Recycler *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ScrapDropoff_Find(this->dropObj);
  this->scrapDropoff = iVar2;
  if (-1 < iVar2) {
    ScrapDropoff_Get(iVar2);
    this->scrapDropoff = -1;
  }
  bVar1 = Producer::PostLoad((Producer *)this);
  return bVar1;
}
