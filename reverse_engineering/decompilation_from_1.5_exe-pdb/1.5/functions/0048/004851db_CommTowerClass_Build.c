/*
 * Entry: 004851db
 * Name: CommTowerClass::Build
 * Namespace: CommTowerClass
 * Signature: GameObject * Build(CommTowerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall CommTowerClass::Build(CommTowerClass *this,_OBJ76 *param_1)

{
  CommTower *pCVar1;
  
  pCVar1 = GameObject::operator_new(0x238);
  if (pCVar1 == (CommTower *)0x0) {
    pCVar1 = (CommTower *)0x0;
  }
  else {
    pCVar1 = CommTower::CommTower(pCVar1,param_1,this);
  }
  return (GameObject *)pCVar1;
}
