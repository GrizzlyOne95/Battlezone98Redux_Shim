/*
 * Entry: 004ab6eb
 * Name: Producer::Save
 * Namespace: Producer
 * Signature: bool Save(Producer * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::Save(Producer *this,_iobuf *param_1)

{
  GameObjectClass *pGVar1;
  bool bVar2;
  Geizer *pGVar3;
  Producer *local_c;
  Producer *local_8;
  
  local_c = this;
  local_8 = this;
  pGVar3 = (Geizer *)GameObjectHandle::GetObj(this->powerHandle);
  this->powerSource = pGVar3;
  pGVar1 = this->buildClass;
  if (pGVar1 == (GameObjectClass *)0x0) {
    local_c = (Producer *)0x0;
    local_8 = (Producer *)0x0;
  }
  else {
    local_c = *(Producer **)&pGVar1->cfg;
    local_8 = *(Producer **)((int)&pGVar1->cfg + 4);
  }
  bVar2 = ::out(param_1,(float *)(this->_padding_ + 0x3c0),4,"timeDeploy");
  if (((((bVar2) &&
        (bVar2 = ::out(param_1,(float *)(this->_padding_ + 0x3c4),4,"timeUndeploy"), bVar2)) &&
       (bVar2 = out_ptr(param_1,&this->powerSource,4,"undefptr"), bVar2)) &&
      ((bVar2 = ::out(param_1,&this->_padding_,4,"state"), bVar2 &&
       (bVar2 = ::out(param_1,&this->delayTimer,4,"delayTimer"), bVar2)))) &&
     ((bVar2 = ::out(param_1,&this->nextRepair,4,"nextRepair"), bVar2 &&
      ((bVar2 = ::out(param_1,(long64 *)&local_c,8,"buildClass"), bVar2 &&
       (bVar2 = ::out(param_1,&this->buildDoneTime,4,"buildDoneTime"), bVar2)))))) {
    bVar2 = HoverCraft::Save((HoverCraft *)this,param_1);
    return bVar2;
  }
  return false;
}
