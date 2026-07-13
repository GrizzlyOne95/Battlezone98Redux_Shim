/*
 * Entry: 0052b589
 * Name: BounceBomb::~BounceBomb
 * Namespace: BounceBomb
 * Signature: void ~BounceBomb(BounceBomb * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BounceBomb::~BounceBomb(BounceBomb *this)

{
  *(undefined ***)this = &_vftable_;
  Grenade::~Grenade((Grenade *)this);
  return;
}
