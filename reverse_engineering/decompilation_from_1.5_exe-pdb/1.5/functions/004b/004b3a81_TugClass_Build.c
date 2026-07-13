/*
 * Entry: 004b3a81
 * Name: TugClass::Build
 * Namespace: TugClass
 * Signature: GameObject * Build(TugClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall TugClass::Build(TugClass *this,_OBJ76 *param_1)

{
  Tug *pTVar1;
  
  pTVar1 = GameObject::operator_new(0x2e0);
  if (pTVar1 == (Tug *)0x0) {
    pTVar1 = (Tug *)0x0;
  }
  else {
    pTVar1 = Tug::Tug(pTVar1,param_1,this);
  }
  return (GameObject *)pTVar1;
}
