/*
 * Entry: 0045ee48
 * Name: IsDamaged
 * Namespace: Global
 * Signature: bool IsDamaged(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsDamaged(int param_1,float param_2)

{
  GameObject *pGVar1;
  float10 fVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    fVar2 = (float10)(**(code **)(pGVar1->_padding_ + 0x1c))();
    if (fVar2 < (float10)param_2) {
      return true;
    }
  }
  return false;
}
