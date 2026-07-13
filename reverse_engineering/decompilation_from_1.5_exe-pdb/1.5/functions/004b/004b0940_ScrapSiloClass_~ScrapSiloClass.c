/*
 * Entry: 004b0940
 * Name: ScrapSiloClass::~ScrapSiloClass
 * Namespace: ScrapSiloClass
 * Signature: void ~ScrapSiloClass(ScrapSiloClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapSiloClass::~ScrapSiloClass(ScrapSiloClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
