/*
 * Entry: 00458b3a
 * Name: RecyclerProcess::Load
 * Namespace: RecyclerProcess
 * Signature: bool Load(RecyclerProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerProcess::Load(RecyclerProcess *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  GameObjectClass *pGVar3;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  bVar1 = ::in(param_1,&this->curState,4);
  if (((((bVar1) && (bVar1 = ::in(param_1,&this->nextState,4), bVar1)) &&
       (bVar1 = in_ptr(param_1,&this->craft,4,"craft",this), bVar1)) &&
      ((bVar1 = ::in(param_1,&this->release,1), bVar1 &&
       (bVar1 = in_ptr(param_1,&this->where,4,"where",this), bVar1)))) &&
     ((bVar1 = ::in(param_1,&this->whoHandle,4), bVar1 &&
      ((bVar1 = ::in(param_1,&this->lastHit,4), bVar1 &&
       (bVar1 = in_ptr(param_1,&this->task,4,"task",this), bVar1)))))) {
    bVar2 = ::in(param_1,(long64 *)&local_c,8);
    bVar1 = true;
    if (bVar2) goto LAB_00458c18;
  }
  bVar1 = false;
LAB_00458c18:
  if (local_c == 0 && local_8 == 0) {
    this->classtobuild = (GameObjectClass *)0x0;
  }
  else {
    pGVar3 = GameObjectClass::Find(CONCAT44(local_8,local_c));
    this->classtobuild = pGVar3;
  }
  this->target = (GameObject *)0x0;
  if ((bVar1) && (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
