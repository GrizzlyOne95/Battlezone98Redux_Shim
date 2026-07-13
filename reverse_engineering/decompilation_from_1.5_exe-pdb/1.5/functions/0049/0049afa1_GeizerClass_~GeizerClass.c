/*
 * Entry: 0049afa1
 * Name: GeizerClass::~GeizerClass
 * Namespace: GeizerClass
 * Signature: void ~GeizerClass(GeizerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GeizerClass::~GeizerClass(GeizerClass *this)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
