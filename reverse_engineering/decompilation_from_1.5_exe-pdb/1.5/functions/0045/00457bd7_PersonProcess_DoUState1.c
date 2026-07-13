/*
 * Entry: 00457bd7
 * Name: PersonProcess::DoUState1
 * Namespace: PersonProcess
 * Signature: void DoUState1(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::DoUState1(PersonProcess *this)

{
  byte bVar1;
  char cVar2;
  GameObject *pGVar3;
  Craft *pCVar4;
  AiTask *pAVar5;
  GameObject *unaff_EBX;
  PersonProcess *local_8;
  
  local_8 = this;
  if (this->getIn == false) {
    local_8 = (PersonProcess *)0x461c4000;
    pGVar3 = GameObjectHandle::GetObj(*(int *)(this->_padding_ + 0x224));
    pCVar4 = (Craft *)GetEmptyVehicle((GameObject *)this->_padding_,(float *)&local_8,pGVar3);
    if (pCVar4 != (Craft *)0x0) {
      this->getIn = true;
      if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)this->_padding_)(1);
      }
      bVar1 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
      pCVar4->_padding_ = pCVar4->_padding_ | 1 << (bVar1 & 0x1f);
      pAVar5 = ChooseTask(pCVar4,unaff_EBX);
      this->_padding_ = (int)pAVar5;
    }
  }
  cVar2 = (**(code **)(*(int *)this->_padding_ + 0x18))();
  if (cVar2 == '\0') {
    (**(code **)(*(int *)this->_padding_ + 0x1c))();
  }
  else {
    this->_padding_ = 3;
  }
  return;
}
