/*
 * Entry: 00457ab4
 * Name: PersonProcess::DoWait
 * Namespace: PersonProcess
 * Signature: void DoWait(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::DoWait(PersonProcess *this)

{
  byte bVar1;
  GameObject *pGVar2;
  Craft *pCVar3;
  AiTask *pAVar4;
  GameObject *unaff_EBX;
  GameObject *unaff_ESI;
  PersonProcess *local_8;
  
  local_8 = this;
  if (this->_padding_ != 0) {
    if (this->getIn == false) {
      local_8 = (PersonProcess *)0x461c4000;
      pGVar2 = GameObjectHandle::GetObj(*(int *)(this->_padding_ + 0x224));
      pCVar3 = (Craft *)GetEmptyVehicle((GameObject *)this->_padding_,(float *)&local_8,pGVar2);
      if (pCVar3 != (Craft *)0x0) {
        this->getIn = true;
        if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
          (*(code *)**(undefined4 **)this->_padding_)(1);
        }
        bVar1 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
        pCVar3->_padding_ = pCVar3->_padding_ | 1 << (bVar1 & 0x1f);
        pAVar4 = ChooseTask(pCVar3,unaff_EBX);
        this->_padding_ = (int)pAVar4;
      }
    }
    pGVar2 = FindBase(unaff_ESI);
    this->base = pGVar2;
    if (pGVar2 != (GameObject *)0x0) {
      this->_padding_ = 0x10;
    }
  }
  UnitProcess::DoWait((UnitProcess *)this);
  return;
}
