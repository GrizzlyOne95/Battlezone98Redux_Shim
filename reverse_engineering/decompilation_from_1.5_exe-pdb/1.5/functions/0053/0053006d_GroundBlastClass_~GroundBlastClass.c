/*
 * Entry: 0053006d
 * Name: GroundBlastClass::~GroundBlastClass
 * Namespace: GroundBlastClass
 * Signature: void ~GroundBlastClass(GroundBlastClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GroundBlastClass::~GroundBlastClass(GroundBlastClass *this)

{
  *(undefined ***)this = &_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  return;
}
