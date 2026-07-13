/*
 * Entry: 00458c75
 * Name: RecyclerProcess::Save
 * Namespace: RecyclerProcess
 * Signature: bool Save(RecyclerProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerProcess::Save(RecyclerProcess *this,_iobuf *param_1)

{
  GameObjectClass *pGVar1;
  bool bVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  pGVar1 = this->classtobuild;
  if (pGVar1 != (GameObjectClass *)0x0) {
    local_c = (undefined4)pGVar1->cfg;
    local_8 = *(undefined4 *)((int)&pGVar1->cfg + 4);
  }
  bVar2 = ::out(param_1,&this->curState,4,"curState");
  if ((((((bVar2) && (bVar2 = ::out(param_1,&this->nextState,4,"nextState"), bVar2)) &&
        (bVar2 = out_ptr(param_1,&this->craft,4,"craft"), bVar2)) &&
       ((bVar2 = ::out(param_1,&this->release,1,"release"), bVar2 &&
        (bVar2 = out_ptr(param_1,&this->where,4,"where"), bVar2)))) &&
      ((bVar2 = ::out(param_1,&this->whoHandle,4,"whoHandle"), bVar2 &&
       ((bVar2 = ::out(param_1,&this->lastHit,4,"lastHit"), bVar2 &&
        (bVar2 = out_ptr(param_1,&this->task,4,"task"), bVar2)))))) &&
     ((bVar2 = ::out(param_1,(long64 *)&local_c,8,"classtobuild"), bVar2 &&
      (bVar2 = AiProcess::Save((AiProcess *)this,param_1), bVar2)))) {
    return true;
  }
  return false;
}
