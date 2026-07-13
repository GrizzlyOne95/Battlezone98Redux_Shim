/*
 * Entry: 004b4a47
 * Name: TurretCraftClass::Build
 * Namespace: TurretCraftClass
 * Signature: GameObject * Build(TurretCraftClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall TurretCraftClass::Build(TurretCraftClass *this,_OBJ76 *param_1)

{
  TurretCraft *pTVar1;
  
  pTVar1 = GameObject::operator_new(0x298);
  if (pTVar1 == (TurretCraft *)0x0) {
    pTVar1 = (TurretCraft *)0x0;
  }
  else {
    pTVar1 = TurretCraft::TurretCraft(pTVar1,param_1,this);
  }
  return (GameObject *)pTVar1;
}
