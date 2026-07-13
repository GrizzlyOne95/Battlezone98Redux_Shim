/*
 * Entry: 005304fc
 * Name: ImageMissileClass::ImageMissileClass
 * Namespace: ImageMissileClass
 * Signature: ImageMissileClass * ImageMissileClass(ImageMissileClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageMissileClass * __thiscall ImageMissileClass::ImageMissileClass(ImageMissileClass *this)

{
  MissileClass::MissileClass((MissileClass *)this);
  *(undefined4 *)&this->field_0xb0 = 0x3f800000;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x494d474d;
  *(undefined4 *)&this->field_0xb4 = 0x42c80000;
  *(char **)&this->field_0x10 = "imagemissile";
  *(undefined4 *)&this->field_0x48 = 10;
  return this;
}
