/*
 * Entry: 004aa9af
 * Name: Producer::Load
 * Namespace: Producer
 * Signature: bool Load(Producer * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::Load(Producer *this,_iobuf *param_1)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  float fVar3;
  int iVar4;
  int local_14;
  int local_10;
  float local_c;
  float local_8;
  
  bVar1 = true;
  if (version < 0x3f3) {
    bVar1 = ::in(param_1,&local_c,4);
  }
  if (version == 0x412) {
LAB_004aaa0e:
    if (bVar1 != false) goto LAB_004aaa12;
LAB_004aaa70:
    bVar1 = false;
  }
  else {
    bVar1 = ::in(param_1,&local_c,4);
    if ((!bVar1) || (bVar1 = ::in(param_1,&local_8,4), !bVar1)) {
      bVar1 = false;
      goto LAB_004aaa0e;
    }
LAB_004aaa12:
    bVar1 = in_ptr(param_1,&this->powerSource,4,"Producer",this);
    if ((((!bVar1) || (bVar1 = ::in(param_1,&this->_padding_,4), !bVar1)) ||
        (bVar1 = ::in(param_1,&this->delayTimer,4), !bVar1)) ||
       (bVar1 = ::in(param_1,&this->nextRepair,4), !bVar1)) goto LAB_004aaa70;
    bVar1 = true;
  }
  if (missionSave != false) {
    fVar3 = Get_TimeLocal();
    this->nextRepair = fVar3 + *(float *)(this->_padding_ + 0x3c8);
  }
  if (0x3ed < version) {
    if (((bVar1 == false) || (bVar1 = ::in(param_1,(long64 *)&local_14,8), !bVar1)) ||
       (bVar1 = ::in(param_1,&this->buildDoneTime,4), !bVar1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (local_14 == 0 && local_10 == 0) {
      this->buildClass = (GameObjectClass *)0x0;
    }
    else {
      pGVar2 = GameObjectClass::Find(CONCAT44(local_10,local_14));
      this->buildClass = pGVar2;
    }
    if (version < 0x403) {
      if (((bVar1 == false) || (bVar1 = ::in(param_1,(int *)&local_c,4), !bVar1)) ||
         ((bVar1 = ::in(param_1,&local_8,4), !bVar1 ||
          ((bVar1 = ::in(param_1,&local_8,4), !bVar1 ||
           (bVar1 = ::in(param_1,(int *)&local_c,4), !bVar1)))))) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
  }
  if (version < 0x3f3) {
    if (bVar1 != false) {
      bVar1 = Craft::Load((Craft *)this,param_1);
    }
  }
  else if (bVar1 != false) {
    bVar1 = HoverCraft::Load((HoverCraft *)this,param_1);
  }
  iVar4 = this->_padding_;
  if (iVar4 == 0) {
LAB_004aab9d:
    iVar4 = 1;
  }
  else {
    if (iVar4 != 1) {
      if (iVar4 != 2) {
        if (iVar4 != 3) {
          return bVar1;
        }
        goto LAB_004aab9d;
      }
      this->_padding_ = 1;
    }
    iVar4 = 0;
  }
  AnimObj_Start((void *)this->_padding_,iVar4,&this->animHandle);
  return bVar1;
}
