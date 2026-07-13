/*
 * Entry: 004af022
 * Name: ScavengerClass::Build
 * Namespace: ScavengerClass
 * Signature: GameObject * Build(ScavengerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ScavengerClass::Build(ScavengerClass *this,_OBJ76 *param_1)

{
  Scavenger *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x2d8);
  if (pSVar1 == (Scavenger *)0x0) {
    pSVar1 = (Scavenger *)0x0;
  }
  else {
    pSVar1 = Scavenger::Scavenger(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
