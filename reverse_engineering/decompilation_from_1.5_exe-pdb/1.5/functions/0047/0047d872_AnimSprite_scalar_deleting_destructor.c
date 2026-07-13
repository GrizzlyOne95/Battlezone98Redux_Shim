/*
 * Entry: 0047d872
 * Name: AnimSprite::`scalar_deleting_destructor'
 * Namespace: AnimSprite
 * Signature: void * `scalar_deleting_destructor'(AnimSprite * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AnimSprite::_scalar_deleting_destructor_(AnimSprite *this,uint param_1)

{
  ~AnimSprite(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
