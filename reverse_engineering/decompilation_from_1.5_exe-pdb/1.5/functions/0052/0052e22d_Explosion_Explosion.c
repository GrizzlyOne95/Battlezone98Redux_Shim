/*
 * Entry: 0052e22d
 * Name: Explosion::Explosion
 * Namespace: Explosion
 * Signature: Explosion * Explosion(Explosion * this, _OBJ76 * param_1, ExplosionClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall Explosion::Explosion(Explosion *this,_OBJ76 *param_1,ExplosionClass *param_2)

{
  this->_padding_ = (int)&_vftable_;
  *(undefined4 *)&this->me = 0;
  *(undefined4 *)&(this->me).field_0x4 = 0;
  this->explosionClass = param_2;
  this->obj = param_1;
  return this;
}
