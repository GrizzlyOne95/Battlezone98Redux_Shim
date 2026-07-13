/*
 * Entry: 005317c3
 * Name: MagnetMineClass::Build
 * Namespace: MagnetMineClass
 * Signature: GameObject * Build(MagnetMineClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall MagnetMineClass::Build(MagnetMineClass *this,_OBJ76 *param_1)

{
  MagnetMine *pMVar1;
  
  pMVar1 = GameObject::operator_new(0x238);
  if (pMVar1 == (MagnetMine *)0x0) {
    pMVar1 = (MagnetMine *)0x0;
  }
  else {
    pMVar1 = MagnetMine::MagnetMine(pMVar1,param_1,this);
  }
  return (GameObject *)pMVar1;
}
