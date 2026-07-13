/*
 * Entry: 0052e7d8
 * Name: ExplosionClass::~ExplosionClass
 * Namespace: ExplosionClass
 * Signature: void ~ExplosionClass(ExplosionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExplosionClass::~ExplosionClass(ExplosionClass *this)

{
  this->_padding_ = (int)&_vftable_;
  remove_obj(this->freeObj,".\\fun3d\\ExplosionClass.cpp");
  return;
}
