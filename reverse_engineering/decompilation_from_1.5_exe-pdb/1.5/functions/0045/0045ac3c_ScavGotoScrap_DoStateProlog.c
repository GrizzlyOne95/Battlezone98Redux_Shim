/*
 * Entry: 0045ac3c
 * Name: ScavGotoScrap::DoStateProlog
 * Namespace: ScavGotoScrap
 * Signature: bool DoStateProlog(ScavGotoScrap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavGotoScrap::DoStateProlog(ScavGotoScrap *this)

{
  bool bVar1;
  undefined1 uVar2;
  GameObject *pGVar3;
  float *pfVar4;
  float fVar5;
  VECTOR_3D local_10;
  
  pGVar3 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar3;
  if (pGVar3 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return false;
  }
  pfVar4 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
  local_10.x = *pfVar4;
  local_10.y = pfVar4[1];
  local_10.z = pfVar4[2];
  pfVar4 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  fVar5 = (pfVar4[2] - local_10.z) * (pfVar4[2] - local_10.z) +
          (*pfVar4 - local_10.x) * (*pfVar4 - local_10.x);
  if (*(float *)&this->field_0x124 == 0.0) {
    if (fVar5 < 2500.0) {
      fVar5 = Get_TimeLocal();
      *(float *)&this->field_0x124 = fVar5 + 30.0;
    }
  }
  else if (((fVar5 < 225.0) && (bVar1 = OnBlocked(&local_10), bVar1)) ||
          (fVar5 = Get_TimeLocal(), *(float *)&this->field_0x124 < fVar5)) {
    *(undefined4 *)&this->field_0x158 = 0;
    uVar2 = (**(code **)(*(int *)this + 0x38))();
    return (bool)uVar2;
  }
  bVar1 = GoNear::DoStateProlog((GoNear *)this);
  return bVar1;
}
