/*
 * Entry: 004b088a
 * Name: ScrapSilo::PostLoad
 * Namespace: ScrapSilo
 * Signature: bool PostLoad(ScrapSilo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScrapSilo::PostLoad(ScrapSilo *this)

{
  bool bVar1;
  int iVar2;
  
  if (this->dropObj == (GameObject *)0x0) {
    this->dropoff = -1;
  }
  else {
    iVar2 = ScrapDropoff_Find(this->dropObj);
    this->dropoff = iVar2;
  }
  if (-1 < this->dropoff) {
    ScrapDropoff_Get(this->dropoff);
    this->dropoff = -1;
  }
  bVar1 = GameObject::PostLoad((GameObject *)this);
  return bVar1;
}
