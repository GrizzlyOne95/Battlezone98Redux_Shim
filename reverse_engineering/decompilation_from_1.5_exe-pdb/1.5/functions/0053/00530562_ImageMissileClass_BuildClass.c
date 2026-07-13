/*
 * Entry: 00530562
 * Name: ImageMissileClass::BuildClass
 * Namespace: ImageMissileClass
 * Signature: OrdnanceClass * BuildClass(ImageMissileClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall ImageMissileClass::BuildClass(ImageMissileClass *this,long64 param_1)

{
  ImageMissileClass *pIVar1;
  undefined4 unaff_ESI;
  
  pIVar1 = operator_new(0xb8);
  if (pIVar1 == (ImageMissileClass *)0x0) {
    pIVar1 = (ImageMissileClass *)0x0;
  }
  else {
    pIVar1 = ImageMissileClass(pIVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pIVar1;
}
