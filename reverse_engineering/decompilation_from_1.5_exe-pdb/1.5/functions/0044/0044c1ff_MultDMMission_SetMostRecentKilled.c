/*
 * Entry: 0044c1ff
 * Name: MultDMMission::SetMostRecentKilled
 * Namespace: MultDMMission
 * Signature: void SetMostRecentKilled(MultDMMission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultDMMission::SetMostRecentKilled(MultDMMission *this,int param_1)

{
  GameObject *pGVar1;
  float *pfVar2;
  
  if (this->killed != param_1) {
    this->recently_killed = true;
    pGVar1 = GameObjectHandle::GetObj(param_1);
    if (pGVar1 != (GameObject *)0x0) {
      pfVar2 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
      (this->pos).x = *pfVar2;
      (this->pos).y = pfVar2[1];
      (this->pos).z = pfVar2[2];
    }
    this->killed = param_1;
  }
  return;
}
