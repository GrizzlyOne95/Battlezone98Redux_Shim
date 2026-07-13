/*
 * Entry: 004aa487
 * Name: PowerUpClass::BuildClass
 * Namespace: PowerUpClass
 * Signature: GameObjectClass * BuildClass(PowerUpClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall PowerUpClass::BuildClass(PowerUpClass *this,long64 param_1)

{
  PowerUpClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0x170);
  if (pPVar1 == (PowerUpClass *)0x0) {
    pPVar1 = (PowerUpClass *)0x0;
  }
  else {
    pPVar1 = PowerUpClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pPVar1;
}
