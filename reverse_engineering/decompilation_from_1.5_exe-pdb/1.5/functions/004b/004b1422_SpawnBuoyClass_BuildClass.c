/*
 * Entry: 004b1422
 * Name: SpawnBuoyClass::BuildClass
 * Namespace: SpawnBuoyClass
 * Signature: GameObjectClass * BuildClass(SpawnBuoyClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall SpawnBuoyClass::BuildClass(SpawnBuoyClass *this,long64 param_1)

{
  SpawnBuoyClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x160);
  if (pSVar1 == (SpawnBuoyClass *)0x0) {
    pSVar1 = (SpawnBuoyClass *)0x0;
  }
  else {
    pSVar1 = SpawnBuoyClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
