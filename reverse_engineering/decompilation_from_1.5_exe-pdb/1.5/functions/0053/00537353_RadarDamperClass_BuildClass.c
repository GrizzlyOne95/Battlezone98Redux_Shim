/*
 * Entry: 00537353
 * Name: RadarDamperClass::BuildClass
 * Namespace: RadarDamperClass
 * Signature: WeaponClass * BuildClass(RadarDamperClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall RadarDamperClass::BuildClass(RadarDamperClass *this,long64 param_1)

{
  RadarDamperClass *pRVar1;
  undefined4 unaff_ESI;
  
  pRVar1 = operator_new(0xa8);
  if (pRVar1 == (RadarDamperClass *)0x0) {
    pRVar1 = (RadarDamperClass *)0x0;
  }
  else {
    pRVar1 = RadarDamperClass(pRVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pRVar1;
}
