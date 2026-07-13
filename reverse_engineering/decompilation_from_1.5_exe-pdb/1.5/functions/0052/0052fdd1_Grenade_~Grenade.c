/*
 * Entry: 0052fdd1
 * Name: Grenade::~Grenade
 * Namespace: Grenade
 * Signature: void ~Grenade(Grenade * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Grenade::~Grenade(Grenade *this)

{
  *(undefined ***)this = &_vftable_;
  Rocket::~Rocket((Rocket *)this);
  return;
}
