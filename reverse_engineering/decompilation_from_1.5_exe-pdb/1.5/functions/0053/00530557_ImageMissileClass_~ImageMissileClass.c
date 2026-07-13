/*
 * Entry: 00530557
 * Name: ImageMissileClass::~ImageMissileClass
 * Namespace: ImageMissileClass
 * Signature: void ~ImageMissileClass(ImageMissileClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageMissileClass::~ImageMissileClass(ImageMissileClass *this)

{
  *(undefined ***)this = &_vftable_;
  MissileClass::~MissileClass((MissileClass *)this);
  return;
}
