/*
 * Entry: 00410434
 * Name: BuildGoto::Load
 * Namespace: BuildGoto
 * Signature: bool Load(BuildGoto * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall BuildGoto::Load(BuildGoto *this,_iobuf *param_1)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  bVar1 = ::in(param_1,&this->buildStage,4);
  if (((bVar1) && (bVar1 = ::in(param_1,(long64 *)&local_c,8), bVar1)) &&
     (bVar1 = ::in(param_1,&this->buildDistSq,4), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (local_c == 0 && local_8 == 0) {
    this->buildClass = (GameObjectClass *)0x0;
  }
  else {
    pGVar2 = GameObjectClass::Find(CONCAT44(local_8,local_c));
    this->buildClass = pGVar2;
  }
  if ((bVar1) && (bVar1 = GotoTask::Load((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
