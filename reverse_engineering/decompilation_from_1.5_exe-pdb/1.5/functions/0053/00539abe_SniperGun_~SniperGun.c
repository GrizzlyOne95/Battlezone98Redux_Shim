/*
 * Entry: 00539abe
 * Name: SniperGun::~SniperGun
 * Namespace: SniperGun
 * Signature: void ~SniperGun(SniperGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperGun::~SniperGun(SniperGun *this)

{
  *(undefined ***)this = &_vftable_;
  Cannon::~Cannon((Cannon *)this);
  return;
}
