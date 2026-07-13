/*
 * Entry: 00537514
 * Name: RadarLauncherClass::BuildClass
 * Namespace: RadarLauncherClass
 * Signature: WeaponClass * BuildClass(RadarLauncherClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall RadarLauncherClass::BuildClass(RadarLauncherClass *this,long64 param_1)

{
  RadarLauncherClass *pRVar1;
  undefined4 unaff_ESI;
  
  pRVar1 = operator_new(0xc0);
  if (pRVar1 == (RadarLauncherClass *)0x0) {
    pRVar1 = (RadarLauncherClass *)0x0;
  }
  else {
    pRVar1 = RadarLauncherClass(pRVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pRVar1;
}
