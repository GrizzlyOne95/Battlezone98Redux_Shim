/*
 * Entry: 005305d5
 * Name: ImageMissileClass::Build
 * Namespace: ImageMissileClass
 * Signature: Ordnance * Build(ImageMissileClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall ImageMissileClass::Build(ImageMissileClass *this,_OBJ76 *param_1)

{
  ImageMissile *pIVar1;
  
  pIVar1 = operator_new(0xf0);
  if (pIVar1 == (ImageMissile *)0x0) {
    pIVar1 = (ImageMissile *)0x0;
  }
  else {
    pIVar1 = ImageMissile::ImageMissile(pIVar1,param_1,this);
  }
  return (Ordnance *)pIVar1;
}
