/*
 * Entry: 0053a523
 * Name: SprayBombClass::~SprayBombClass
 * Namespace: SprayBombClass
 * Signature: void ~SprayBombClass(SprayBombClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SprayBombClass::~SprayBombClass(SprayBombClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)this);
  return;
}
