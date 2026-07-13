/*
 * Entry: 00489a90
 * Name: CraftClass::Build
 * Namespace: CraftClass
 * Signature: GameObject * Build(CraftClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall CraftClass::Build(CraftClass *this,_OBJ76 *param_1)

{
  Craft *pCVar1;
  
  pCVar1 = GameObject::operator_new(0x268);
  if (pCVar1 == (Craft *)0x0) {
    pCVar1 = (Craft *)0x0;
  }
  else {
    pCVar1 = Craft::Craft(pCVar1,param_1,this);
  }
  return (GameObject *)pCVar1;
}
