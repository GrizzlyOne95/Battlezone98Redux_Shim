/*
 * Entry: 00531e90
 * Name: MineClass::Build
 * Namespace: MineClass
 * Signature: GameObject * Build(MineClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall MineClass::Build(MineClass *this,_OBJ76 *param_1)

{
  Mine *pMVar1;
  
  pMVar1 = GameObject::operator_new(0x238);
  if (pMVar1 == (Mine *)0x0) {
    pMVar1 = (Mine *)0x0;
  }
  else {
    pMVar1 = Mine::Mine(pMVar1,param_1,this);
  }
  return (GameObject *)pMVar1;
}
