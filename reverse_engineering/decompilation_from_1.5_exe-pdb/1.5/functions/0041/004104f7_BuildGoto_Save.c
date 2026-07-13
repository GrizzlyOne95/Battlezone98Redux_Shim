/*
 * Entry: 004104f7
 * Name: BuildGoto::Save
 * Namespace: BuildGoto
 * Signature: bool Save(BuildGoto * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall BuildGoto::Save(BuildGoto *this,_iobuf *param_1)

{
  GameObjectClass *pGVar1;
  bool bVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  pGVar1 = this->buildClass;
  if (pGVar1 != (GameObjectClass *)0x0) {
    local_c = (undefined4)pGVar1->cfg;
    local_8 = *(undefined4 *)((int)&pGVar1->cfg + 4);
  }
  bVar2 = ::out(param_1,&this->buildStage,4,"buildStage");
  if ((((bVar2) && (bVar2 = ::out(param_1,(long64 *)&local_c,8,"buildCfg"), bVar2)) &&
      (bVar2 = ::out(param_1,&this->buildDistSq,4,"buildDistSq"), bVar2)) &&
     (bVar2 = GotoTask::Save((GotoTask *)this,param_1), bVar2)) {
    return true;
  }
  return false;
}
