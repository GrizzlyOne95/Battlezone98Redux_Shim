/*
 * Entry: 00539c96
 * Name: SniperShell::~SniperShell
 * Namespace: SniperShell
 * Signature: void ~SniperShell(SniperShell * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperShell::~SniperShell(SniperShell *this)

{
  *(undefined ***)this = &_vftable_;
  Bullet::~Bullet((Bullet *)this);
  return;
}
