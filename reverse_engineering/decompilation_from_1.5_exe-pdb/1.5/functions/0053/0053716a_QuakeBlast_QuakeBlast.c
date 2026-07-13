/*
 * Entry: 0053716a
 * Name: QuakeBlast::QuakeBlast
 * Namespace: QuakeBlast
 * Signature: QuakeBlast * QuakeBlast(QuakeBlast * this, _OBJ76 * param_1, QuakeBlastClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QuakeBlast * __thiscall
QuakeBlast::QuakeBlast(QuakeBlast *this,_OBJ76 *param_1,QuakeBlastClass *param_2)

{
  Explosion::Explosion((Explosion *)this,param_1,(ExplosionClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  return this;
}
