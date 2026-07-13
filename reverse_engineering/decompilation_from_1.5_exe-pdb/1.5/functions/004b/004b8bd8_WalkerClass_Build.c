/*
 * Entry: 004b8bd8
 * Name: WalkerClass::Build
 * Namespace: WalkerClass
 * Signature: GameObject * Build(WalkerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall WalkerClass::Build(WalkerClass *this,_OBJ76 *param_1)

{
  Walker *pWVar1;
  
  pWVar1 = GameObject::operator_new(0x298);
  if (pWVar1 == (Walker *)0x0) {
    pWVar1 = (Walker *)0x0;
  }
  else {
    pWVar1 = Walker::Walker(pWVar1,param_1,this);
  }
  return (GameObject *)pWVar1;
}
