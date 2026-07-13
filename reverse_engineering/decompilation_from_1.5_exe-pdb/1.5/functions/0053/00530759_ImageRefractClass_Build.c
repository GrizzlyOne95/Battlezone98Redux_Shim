/*
 * Entry: 00530759
 * Name: ImageRefractClass::Build
 * Namespace: ImageRefractClass
 * Signature: Weapon * Build(ImageRefractClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall ImageRefractClass::Build(ImageRefractClass *this,_OBJ76 *param_1)

{
  ImageRefract *pIVar1;
  
  pIVar1 = operator_new(0xc0);
  if (pIVar1 == (ImageRefract *)0x0) {
    pIVar1 = (ImageRefract *)0x0;
  }
  else {
    pIVar1 = ImageRefract::ImageRefract(pIVar1,param_1,this);
  }
  return (Weapon *)pIVar1;
}
