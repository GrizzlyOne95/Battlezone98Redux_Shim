/*
 * Entry: 004b968e
 * Name: WingmanClass::Build
 * Namespace: WingmanClass
 * Signature: GameObject * Build(WingmanClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall WingmanClass::Build(WingmanClass *this,_OBJ76 *param_1)

{
  Wingman *pWVar1;
  
  pWVar1 = GameObject::operator_new(0x2c0);
  if (pWVar1 == (Wingman *)0x0) {
    pWVar1 = (Wingman *)0x0;
  }
  else {
    pWVar1 = Wingman::Wingman(pWVar1,param_1,this);
  }
  return (GameObject *)pWVar1;
}
