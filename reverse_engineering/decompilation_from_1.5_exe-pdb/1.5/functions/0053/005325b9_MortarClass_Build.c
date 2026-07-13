/*
 * Entry: 005325b9
 * Name: MortarClass::Build
 * Namespace: MortarClass
 * Signature: Weapon * Build(MortarClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall MortarClass::Build(MortarClass *this,_OBJ76 *param_1)

{
  Mortar *pMVar1;
  
  pMVar1 = operator_new(0xb8);
  if (pMVar1 == (Mortar *)0x0) {
    pMVar1 = (Mortar *)0x0;
  }
  else {
    pMVar1 = Mortar::Mortar(pMVar1,param_1,this);
  }
  return (Weapon *)pMVar1;
}
