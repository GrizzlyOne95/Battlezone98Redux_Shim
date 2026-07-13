/*
 * Entry: 00530537
 * Name: ImageMissileClass::ImageMissileClass
 * Namespace: ImageMissileClass
 * Signature: ImageMissileClass * ImageMissileClass(ImageMissileClass * this, ImageMissileClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageMissileClass * __thiscall
ImageMissileClass::ImageMissileClass
          (ImageMissileClass *this,ImageMissileClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  MissileClass::MissileClass
            ((MissileClass *)this,(MissileClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
