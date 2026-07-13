/*
 * Entry: 0053a54a
 * Name: SprayBomb::~SprayBomb
 * Namespace: SprayBomb
 * Signature: void ~SprayBomb(SprayBomb * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SprayBomb::~SprayBomb(SprayBomb *this)

{
  *(undefined ***)this = &_vftable_;
  Grenade::~Grenade((Grenade *)this);
  return;
}
