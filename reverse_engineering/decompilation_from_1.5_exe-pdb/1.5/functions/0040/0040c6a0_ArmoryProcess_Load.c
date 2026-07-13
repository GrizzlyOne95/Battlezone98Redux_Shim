/*
 * Entry: 0040c6a0
 * Name: ArmoryProcess::Load
 * Namespace: ArmoryProcess
 * Signature: bool Load(ArmoryProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ArmoryProcess::Load(ArmoryProcess *this,_iobuf *param_1)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  bVar1 = ::in(param_1,(int *)&this->curState,4);
  if ((((((bVar1) && (bVar1 = ::in(param_1,(int *)&this->nextState,4), bVar1)) &&
        (bVar1 = in_ptr(param_1,&this->craft,4,"craft",this), bVar1)) &&
       ((bVar1 = ::in(param_1,&this->release,1), bVar1 &&
        (bVar1 = in_ptr(param_1,&this->where,4,"where",this), bVar1)))) &&
      ((bVar1 = ::in(param_1,&this->whoHandle,4), bVar1 &&
       ((bVar1 = in_ptr(param_1,&this->task,4,"task",this), bVar1 &&
        (bVar1 = ::in(param_1,(long64 *)&local_c,8), bVar1)))))) &&
     ((bVar1 = ::in(param_1,&this->pos,0xc), bVar1 &&
      ((bVar1 = ::in(param_1,&this->isInTransition,1), bVar1 &&
       (bVar1 = ::in(param_1,&this->wasInTransition,1), bVar1)))))) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (local_c == 0 && local_8 == 0) {
    this->classtobuild = (GameObjectClass *)0x0;
  }
  else {
    pGVar2 = GameObjectClass::Find(CONCAT44(local_8,local_c));
    this->classtobuild = pGVar2;
  }
  this->target = (GameObject *)0x0;
  if ((bVar1) && (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
