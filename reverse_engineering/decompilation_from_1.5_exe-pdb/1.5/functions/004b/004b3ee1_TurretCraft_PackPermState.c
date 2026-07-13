/*
 * Entry: 004b3ee1
 * Name: TurretCraft::PackPermState
 * Namespace: TurretCraft
 * Signature: void PackPermState(TurretCraft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::PackPermState(TurretCraft *this,void *param_1,uint *param_2)

{
  *param_2 = *param_2 + 4;
  *(int *)param_1 = this->_padding_;
  return;
}
