/*
 * Entry: 00532398
 * Name: Mortar::~Mortar
 * Namespace: Mortar
 * Signature: void ~Mortar(Mortar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mortar::~Mortar(Mortar *this)

{
  *(undefined ***)this = &_vftable_;
  Cannon::~Cannon((Cannon *)this);
  return;
}
