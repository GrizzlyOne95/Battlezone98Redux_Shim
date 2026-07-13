/*
 * Entry: 004a5332
 * Name: Person::Load
 * Namespace: Person
 * Signature: bool Load(Person * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Person::Load(Person *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = ::in(param_1,&this->nextScream,4);
  bVar2 = false;
  if (bVar1) {
    bVar2 = Craft::Load((Craft *)this,param_1);
  }
  return bVar2;
}
