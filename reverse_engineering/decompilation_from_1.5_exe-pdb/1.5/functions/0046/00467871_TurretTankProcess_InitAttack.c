/*
 * Entry: 00467871
 * Name: TurretTankProcess::InitAttack
 * Namespace: TurretTankProcess
 * Signature: void InitAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitAttack(TurretTankProcess *this)

{
  GameObject *pGVar1;
  TurretAttack *pTVar2;
  
  (**(code **)(*(int *)this->_padding_ + 0x5c))();
  pGVar1 = GameObjectHandle::GetObj(this->_padding_);
  pTVar2 = operator_new(0x140);
  if (pTVar2 == (TurretAttack *)0x0) {
    pTVar2 = (TurretAttack *)0x0;
  }
  else {
    pTVar2 = TurretAttack::TurretAttack(pTVar2,(Craft *)this->_padding_,pGVar1);
  }
  this->_padding_ = (int)pTVar2;
  return;
}
