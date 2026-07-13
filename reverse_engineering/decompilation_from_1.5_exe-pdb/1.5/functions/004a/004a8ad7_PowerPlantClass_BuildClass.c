/*
 * Entry: 004a8ad7
 * Name: PowerPlantClass::BuildClass
 * Namespace: PowerPlantClass
 * Signature: GameObjectClass * BuildClass(PowerPlantClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall PowerPlantClass::BuildClass(PowerPlantClass *this,long64 param_1)

{
  PowerPlantClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0x168);
  if (pPVar1 == (PowerPlantClass *)0x0) {
    pPVar1 = (PowerPlantClass *)0x0;
  }
  else {
    pPVar1 = PowerPlantClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pPVar1;
}
