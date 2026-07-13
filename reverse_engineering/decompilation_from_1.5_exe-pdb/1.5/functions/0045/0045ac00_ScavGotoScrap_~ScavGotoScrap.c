/*
 * Entry: 0045ac00
 * Name: ScavGotoScrap::~ScavGotoScrap
 * Namespace: ScavGotoScrap
 * Signature: void ~ScavGotoScrap(ScavGotoScrap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavGotoScrap::~ScavGotoScrap(ScavGotoScrap *this)

{
  byte bVar1;
  GameObject *pGVar2;
  
  *(undefined ***)this = &_vftable_;
  pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  if (pGVar2 != (GameObject *)0x0) {
    bVar1 = (**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 4))();
    pGVar2->locked = pGVar2->locked & ~(1 << (bVar1 & 0x1f));
  }
  GotoTask::~GotoTask((GotoTask *)this);
  return;
}
