/*
 * Entry: 0053069d
 * Name: ImageRefractClass::BuildClass
 * Namespace: ImageRefractClass
 * Signature: WeaponClass * BuildClass(ImageRefractClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall ImageRefractClass::BuildClass(ImageRefractClass *this,long64 param_1)

{
  ImageRefractClass *pIVar1;
  undefined4 unaff_ESI;
  
  pIVar1 = operator_new(0xa8);
  if (pIVar1 == (ImageRefractClass *)0x0) {
    pIVar1 = (ImageRefractClass *)0x0;
  }
  else {
    pIVar1 = ImageRefractClass(pIVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pIVar1;
}
