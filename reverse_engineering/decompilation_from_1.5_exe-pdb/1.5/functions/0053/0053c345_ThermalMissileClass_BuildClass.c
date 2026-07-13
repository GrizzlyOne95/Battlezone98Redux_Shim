/*
 * Entry: 0053c345
 * Name: ThermalMissileClass::BuildClass
 * Namespace: ThermalMissileClass
 * Signature: OrdnanceClass * BuildClass(ThermalMissileClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall ThermalMissileClass::BuildClass(ThermalMissileClass *this,long64 param_1)

{
  ThermalMissileClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0xc0);
  if (pTVar1 == (ThermalMissileClass *)0x0) {
    pTVar1 = (ThermalMissileClass *)0x0;
  }
  else {
    pTVar1 = ThermalMissileClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pTVar1;
}
