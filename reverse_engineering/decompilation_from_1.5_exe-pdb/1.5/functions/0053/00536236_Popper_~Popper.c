/*
 * Entry: 00536236
 * Name: Popper::~Popper
 * Namespace: Popper
 * Signature: void ~Popper(Popper * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Popper::~Popper(Popper *this)

{
  *(undefined ***)this = &_vftable_;
  Grenade::~Grenade((Grenade *)this);
  return;
}
