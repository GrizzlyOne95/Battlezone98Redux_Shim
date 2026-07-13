/*
 * Entry: 00539903
 * Name: ShockBlastClass::~ShockBlastClass
 * Namespace: ShockBlastClass
 * Signature: void ~ShockBlastClass(ShockBlastClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShockBlastClass::~ShockBlastClass(ShockBlastClass *this)

{
  *(undefined ***)this = &_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  return;
}
