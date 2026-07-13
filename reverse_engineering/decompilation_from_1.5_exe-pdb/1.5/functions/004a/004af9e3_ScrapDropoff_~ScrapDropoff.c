/*
 * Entry: 004af9e3
 * Name: ScrapDropoff::~ScrapDropoff
 * Namespace: ScrapDropoff
 * Signature: void ~ScrapDropoff(ScrapDropoff * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapDropoff::~ScrapDropoff(ScrapDropoff *this)

{
  DropoffInfo *pDVar1;
  uint uVar2;
  
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  pDVar1 = dropoffList;
  uVar2 = 0;
  do {
    if (pDVar1->dropObj == this) {
      pDVar1->dropObj = (ScrapDropoff *)0x0;
      break;
    }
    uVar2 = uVar2 + 8;
    pDVar1 = pDVar1 + 1;
  } while (uVar2 < 0xa0);
  PowerUp::~PowerUp((PowerUp *)this);
  return;
}
