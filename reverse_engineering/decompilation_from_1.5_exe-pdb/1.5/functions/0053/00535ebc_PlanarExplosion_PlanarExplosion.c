/*
 * Entry: 00535ebc
 * Name: PlanarExplosion::PlanarExplosion
 * Namespace: PlanarExplosion
 * Signature: PlanarExplosion * PlanarExplosion(PlanarExplosion * this, _OBJ76 * param_1, PlanarExplosionClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlanarExplosion * __thiscall
PlanarExplosion::PlanarExplosion
          (PlanarExplosion *this,_OBJ76 *param_1,PlanarExplosionClass *param_2)

{
  Explosion::Explosion((Explosion *)this,param_1,(ExplosionClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  this->velocRadial =
       ((*(float *)&param_2->field_0x50 - *(float *)&param_2->field_0x3c) *
       *(float *)&param_2->field_0x38) / (float)*(int *)&param_2->field_0x34;
  return this;
}
