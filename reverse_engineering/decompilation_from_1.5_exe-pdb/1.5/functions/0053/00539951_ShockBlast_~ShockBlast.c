/*
 * Entry: 00539951
 * Name: ShockBlast::~ShockBlast
 * Namespace: ShockBlast
 * Signature: void ~ShockBlast(ShockBlast * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShockBlast::~ShockBlast(ShockBlast *this)

{
  *(undefined ***)this = &_vftable_;
  Explosion::~Explosion((Explosion *)this);
  return;
}
