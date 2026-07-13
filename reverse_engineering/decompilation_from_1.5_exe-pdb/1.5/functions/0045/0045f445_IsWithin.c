/*
 * Entry: 0045f445
 * Name: IsWithin
 * Namespace: Global
 * Signature: bool IsWithin(int param_1, int param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsWithin(int param_1,int param_2,float param_3)

{
  GameObject *pGVar1;
  GameObject *pGVar2;
  float *pfVar3;
  float *pfVar4;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  pGVar2 = GameObjectHandle::GetObj(param_2);
  if ((pGVar1 != (GameObject *)0x0) && (pGVar2 != (GameObject *)0x0)) {
    pfVar3 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
    pfVar4 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
    if ((pfVar4[2] - pfVar3[2]) * (pfVar4[2] - pfVar3[2]) +
        (*pfVar4 - *pfVar3) * (*pfVar4 - *pfVar3) < param_3 * param_3) {
      return true;
    }
    return false;
  }
  return false;
}
