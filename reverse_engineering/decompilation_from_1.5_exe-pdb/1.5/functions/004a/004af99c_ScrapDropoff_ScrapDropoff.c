/*
 * Entry: 004af99c
 * Name: ScrapDropoff::ScrapDropoff
 * Namespace: ScrapDropoff
 * Signature: ScrapDropoff * ScrapDropoff(ScrapDropoff * this, _OBJ76 * param_1, ScrapDropoffClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapDropoff * __thiscall
ScrapDropoff::ScrapDropoff(ScrapDropoff *this,_OBJ76 *param_1,ScrapDropoffClass *param_2)

{
  DropoffInfo *pDVar1;
  uint uVar2;
  
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  pDVar1 = dropoffList;
  uVar2 = 0;
  while ((pDVar1->dropObj != (ScrapDropoff *)0x0 || (pDVar1->refCount != 0))) {
    uVar2 = uVar2 + 8;
    pDVar1 = pDVar1 + 1;
    if (0x9f < uVar2) {
      return this;
    }
  }
  pDVar1->dropObj = this;
  return this;
}
