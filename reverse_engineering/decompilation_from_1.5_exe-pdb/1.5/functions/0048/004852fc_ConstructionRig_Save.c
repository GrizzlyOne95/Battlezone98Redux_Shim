/*
 * Entry: 004852fc
 * Name: ConstructionRig::Save
 * Namespace: ConstructionRig
 * Signature: bool Save(ConstructionRig * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ConstructionRig::Save(ConstructionRig *this,_iobuf *param_1)

{
  GameObjectClass *pGVar1;
  bool bVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  pGVar1 = this->dropClass;
  if (pGVar1 != (GameObjectClass *)0x0) {
    local_c = (undefined4)pGVar1->cfg;
    local_8 = *(undefined4 *)((int)&pGVar1->cfg + 4);
  }
  bVar2 = ::out(param_1,&this->dropMat,0x40,"dropMat");
  if (((bVar2) && (bVar2 = ::out(param_1,(long64 *)&local_c,8,"dropClass"), bVar2)) &&
     (bVar2 = Producer::Save((Producer *)this,param_1), bVar2)) {
    return true;
  }
  return false;
}
