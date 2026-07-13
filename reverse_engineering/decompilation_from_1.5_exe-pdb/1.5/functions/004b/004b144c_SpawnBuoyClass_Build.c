/*
 * Entry: 004b144c
 * Name: SpawnBuoyClass::Build
 * Namespace: SpawnBuoyClass
 * Signature: GameObject * Build(SpawnBuoyClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall SpawnBuoyClass::Build(SpawnBuoyClass *this,_OBJ76 *param_1)

{
  SpawnBuoy *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x238);
  if (pSVar1 == (SpawnBuoy *)0x0) {
    pSVar1 = (SpawnBuoy *)0x0;
  }
  else {
    pSVar1 = SpawnBuoy::SpawnBuoy(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
