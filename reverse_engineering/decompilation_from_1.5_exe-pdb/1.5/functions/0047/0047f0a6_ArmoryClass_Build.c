/*
 * Entry: 0047f0a6
 * Name: ArmoryClass::Build
 * Namespace: ArmoryClass
 * Signature: GameObject * Build(ArmoryClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ArmoryClass::Build(ArmoryClass *this,_OBJ76 *param_1)

{
  Armory *pAVar1;
  
  pAVar1 = GameObject::operator_new(0x330);
  if (pAVar1 == (Armory *)0x0) {
    pAVar1 = (Armory *)0x0;
  }
  else {
    pAVar1 = Armory::Armory(pAVar1,param_1,this);
  }
  return (GameObject *)pAVar1;
}
