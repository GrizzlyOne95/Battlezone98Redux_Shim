/*
 * Entry: 004af730
 * Name: ScrapClass::~ScrapClass
 * Namespace: ScrapClass
 * Signature: void ~ScrapClass(ScrapClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapClass::~ScrapClass(ScrapClass *this)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
