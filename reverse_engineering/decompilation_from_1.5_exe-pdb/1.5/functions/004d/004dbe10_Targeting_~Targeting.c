/*
 * Entry: 004dbe10
 * Name: Targeting::~Targeting
 * Namespace: Targeting
 * Signature: void ~Targeting(Targeting * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Targeting::~Targeting(Targeting *this)

{
  *(undefined ***)this = &_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
