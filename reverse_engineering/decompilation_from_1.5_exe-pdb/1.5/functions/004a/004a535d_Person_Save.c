/*
 * Entry: 004a535d
 * Name: Person::Save
 * Namespace: Person
 * Signature: bool Save(Person * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Person::Save(Person *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = ::out(param_1,&this->nextScream,4,"nextScream");
  bVar2 = false;
  if (bVar1) {
    bVar2 = Craft::Save((Craft *)this,param_1);
  }
  return bVar2;
}
