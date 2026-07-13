/*
 * Entry: 0053009f
 * Name: GroundBlast::GroundBlast
 * Namespace: GroundBlast
 * Signature: GroundBlast * GroundBlast(GroundBlast * this, _OBJ76 * param_1, GroundBlastClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GroundBlast * __thiscall
GroundBlast::GroundBlast(GroundBlast *this,_OBJ76 *param_1,GroundBlastClass *param_2)

{
  Explosion::Explosion((Explosion *)this,param_1,(ExplosionClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
