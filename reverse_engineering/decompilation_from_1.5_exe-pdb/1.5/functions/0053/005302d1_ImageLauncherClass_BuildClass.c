/*
 * Entry: 005302d1
 * Name: ImageLauncherClass::BuildClass
 * Namespace: ImageLauncherClass
 * Signature: WeaponClass * BuildClass(ImageLauncherClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall ImageLauncherClass::BuildClass(ImageLauncherClass *this,long64 param_1)

{
  ImageLauncherClass *pIVar1;
  undefined4 unaff_ESI;
  
  pIVar1 = operator_new(0xc0);
  if (pIVar1 == (ImageLauncherClass *)0x0) {
    pIVar1 = (ImageLauncherClass *)0x0;
  }
  else {
    pIVar1 = ImageLauncherClass(pIVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pIVar1;
}
