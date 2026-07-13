/*
 * Entry: 005300bb
 * Name: GroundBlast::~GroundBlast
 * Namespace: GroundBlast
 * Signature: void ~GroundBlast(GroundBlast * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GroundBlast::~GroundBlast(GroundBlast *this)

{
  *(undefined ***)this = &_vftable_;
  Explosion::~Explosion((Explosion *)this);
  return;
}
