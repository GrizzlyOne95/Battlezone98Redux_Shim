/*
 * Entry: 00485cac
 * Name: ConstructionRigClass::Build
 * Namespace: ConstructionRigClass
 * Signature: GameObject * Build(ConstructionRigClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ConstructionRigClass::Build(ConstructionRigClass *this,_OBJ76 *param_1)

{
  ConstructionRig *pCVar1;
  
  pCVar1 = GameObject::operator_new(0x368);
  if (pCVar1 == (ConstructionRig *)0x0) {
    pCVar1 = (ConstructionRig *)0x0;
  }
  else {
    pCVar1 = ConstructionRig::ConstructionRig(pCVar1,param_1,this);
  }
  return (GameObject *)pCVar1;
}
