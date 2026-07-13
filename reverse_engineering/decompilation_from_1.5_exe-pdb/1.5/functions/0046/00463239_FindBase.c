/*
 * Entry: 00463239
 * Name: FindBase
 * Namespace: Global
 * Signature: GameObject * FindBase(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl FindBase(GameObject *param_1)

{
  Team *this;
  float fVar1;
  int in_EAX;
  float *pfVar2;
  GameObject *pGVar3;
  float *pfVar4;
  GameObject *pGVar5;
  float local_c;
  int local_8;
  
  this = *(Team **)(in_EAX + 0x170);
  pfVar2 = (float *)(**(code **)(*(int *)(in_EAX + 0x20) + 0xc))();
  pGVar3 = Team::GetSlot(this,1);
  if (((pGVar3 == (GameObject *)0x0) &&
      (pGVar3 = Team::GetSlot(this,2), pGVar3 == (GameObject *)0x0)) &&
     (pGVar3 = Team::GetSlot(this,3), pGVar3 == (GameObject *)0x0)) {
    local_c = 3.4028235e+38;
  }
  else {
    pfVar4 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
    local_c = (pfVar2[2] - pfVar4[2]) * (pfVar2[2] - pfVar4[2]) +
              (*pfVar2 - *pfVar4) * (*pfVar2 - *pfVar4);
  }
  local_8 = 0x4b;
  do {
    pGVar5 = Team::GetSlot(this,local_8);
    if (pGVar5 != (GameObject *)0x0) {
      pfVar4 = (float *)(**(code **)(pGVar5->_padding_ + 0xc))();
      fVar1 = (pfVar2[2] - pfVar4[2]) * (pfVar2[2] - pfVar4[2]) +
              (*pfVar2 - *pfVar4) * (*pfVar2 - *pfVar4);
      if (fVar1 < local_c) {
        pGVar3 = pGVar5;
        local_c = fVar1;
      }
    }
    local_8 = local_8 + 1;
  } while (local_8 < 0x50);
  return pGVar3;
}
