/*
 * Entry: 004678ad
 * Name: TurretTankProcess::InitSubAttack
 * Namespace: TurretTankProcess
 * Signature: void InitSubAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitSubAttack(TurretTankProcess *this)

{
  GameObject *pGVar1;
  TurretBlastAttack *pTVar2;
  float fVar3;
  
  (**(code **)(*(int *)this->_padding_ + 0x5c))();
  pGVar1 = GameObjectHandle::GetObj(this->_padding_);
  pTVar2 = operator_new(0x138);
  if (pTVar2 == (TurretBlastAttack *)0x0) {
    pTVar2 = (TurretBlastAttack *)0x0;
  }
  else {
    pTVar2 = TurretBlastAttack::TurretBlastAttack(pTVar2,(Craft *)this->_padding_,pGVar1);
  }
  this->_padding_ = (int)pTVar2;
  fVar3 = Get_Time();
  this->nextAttackTime = fVar3 + 3.0;
  return;
}
