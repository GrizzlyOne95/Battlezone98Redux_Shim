/*
 * Entry: 0049c2e3
 * Name: HealthPowerupClass::BuildClass
 * Namespace: HealthPowerupClass
 * Signature: GameObjectClass * BuildClass(HealthPowerupClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall HealthPowerupClass::BuildClass(HealthPowerupClass *this,long64 param_1)

{
  HealthPowerupClass *pHVar1;
  undefined4 unaff_ESI;
  
  pHVar1 = operator_new(0x178);
  if (pHVar1 == (HealthPowerupClass *)0x0) {
    pHVar1 = (HealthPowerupClass *)0x0;
  }
  else {
    pHVar1 = HealthPowerupClass(pHVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pHVar1;
}
