/*
 * Entry: 0044d284
 * Name: MultSTMission::SetMostRecentKilled
 * Namespace: MultSTMission
 * Signature: void SetMostRecentKilled(MultSTMission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultSTMission::SetMostRecentKilled(MultSTMission *this,int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  float *pfVar3;
  
  if ((this->killed != param_1) &&
     (pGVar1 = GameObjectHandle::GetObj(param_1), pGVar1 != (GameObject *)0x0)) {
    iVar2 = (**(code **)pGVar1->_padding_)();
    if (*(int *)(iVar2 + 0x20) == 0x50455253) {
      this->recently_killed = true;
      pfVar3 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
      (this->pos).x = *pfVar3;
      (this->pos).y = pfVar3[1];
      (this->pos).z = pfVar3[2];
      this->killed = param_1;
    }
  }
  return;
}
