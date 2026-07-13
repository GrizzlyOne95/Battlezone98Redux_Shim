/*
 * Entry: 004b3421
 * Name: Tug::UnPackTempState
 * Namespace: Tug
 * Signature: void UnPackTempState(Tug * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tug::UnPackTempState(Tug *this,void *param_1,uint *param_2)

{
  char cVar1;
  ulong uVar2;
  ulong uVar3;
  GameObject *pGVar4;
  
  cVar1 = *(char *)((int)param_1 + 4);
  if (cVar1 == '\0') {
LAB_004b3447:
    (*(code *)(this[-1].cargo)->_padding_)();
  }
  else if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
    (*(code *)(this[-1].cargo)->_padding_)();
  }
  else if (cVar1 == '\x03') goto LAB_004b3447;
  uVar2 = *(ulong *)param_1;
  if (uVar2 == 0) {
    pGVar4 = (GameObject *)0x0;
  }
  else {
    if (this->_padding_ != 0) {
      uVar3 = DistributedObject::GetID((DistributedObject *)(this->_padding_ + 0x20));
      if (uVar3 == uVar2) goto LAB_004b347e;
    }
    pGVar4 = DistributedObject::GetGameObject(uVar2);
  }
  SetCargo((Tug *)&this[-1].cargo,pGVar4);
LAB_004b347e:
  *param_2 = *param_2 - 8;
  HoverCraft::UnPackTempState((HoverCraft *)this,(void *)((int)param_1 + 8),param_2);
  return;
}
