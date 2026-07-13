/*
 * Entry: 00539935
 * Name: ShockBlast::ShockBlast
 * Namespace: ShockBlast
 * Signature: ShockBlast * ShockBlast(ShockBlast * this, _OBJ76 * param_1, ShockBlastClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShockBlast * __thiscall
ShockBlast::ShockBlast(ShockBlast *this,_OBJ76 *param_1,ShockBlastClass *param_2)

{
  Explosion::Explosion((Explosion *)this,param_1,(ExplosionClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
