/*
 * Entry: 0047e78e
 * Name: APCClass::Build
 * Namespace: APCClass
 * Signature: GameObject * Build(APCClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall APCClass::Build(APCClass *this,_OBJ76 *param_1)

{
  APC *pAVar1;
  
  pAVar1 = GameObject::operator_new(0x2d0);
  if (pAVar1 == (APC *)0x0) {
    pAVar1 = (APC *)0x0;
  }
  else {
    pAVar1 = APC::APC(pAVar1,param_1,this);
  }
  return (GameObject *)pAVar1;
}
