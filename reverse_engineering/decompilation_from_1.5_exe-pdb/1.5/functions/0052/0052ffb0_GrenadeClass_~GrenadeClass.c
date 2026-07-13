/*
 * Entry: 0052ffb0
 * Name: GrenadeClass::~GrenadeClass
 * Namespace: GrenadeClass
 * Signature: void ~GrenadeClass(GrenadeClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GrenadeClass::~GrenadeClass(GrenadeClass *this)

{
  *(undefined ***)this = &_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  return;
}
