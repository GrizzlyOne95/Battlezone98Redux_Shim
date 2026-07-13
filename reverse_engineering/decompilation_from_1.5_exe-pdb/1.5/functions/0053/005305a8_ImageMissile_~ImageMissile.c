/*
 * Entry: 005305a8
 * Name: ImageMissile::~ImageMissile
 * Namespace: ImageMissile
 * Signature: void ~ImageMissile(ImageMissile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageMissile::~ImageMissile(ImageMissile *this)

{
  *(undefined ***)this = &_vftable_;
  Missile::~Missile((Missile *)this);
  return;
}
