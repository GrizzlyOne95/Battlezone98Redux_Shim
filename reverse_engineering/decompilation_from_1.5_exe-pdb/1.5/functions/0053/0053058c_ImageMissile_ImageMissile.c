/*
 * Entry: 0053058c
 * Name: ImageMissile::ImageMissile
 * Namespace: ImageMissile
 * Signature: ImageMissile * ImageMissile(ImageMissile * this, _OBJ76 * param_1, ImageMissileClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageMissile * __thiscall
ImageMissile::ImageMissile(ImageMissile *this,_OBJ76 *param_1,ImageMissileClass *param_2)

{
  Missile::Missile((Missile *)this,param_1,(MissileClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
