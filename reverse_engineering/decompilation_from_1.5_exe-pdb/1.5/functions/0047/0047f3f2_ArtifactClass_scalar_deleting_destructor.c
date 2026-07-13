/*
 * Entry: 0047f3f2
 * Name: ArtifactClass::`scalar_deleting_destructor'
 * Namespace: ArtifactClass
 * Signature: void * `scalar_deleting_destructor'(ArtifactClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ArtifactClass::_scalar_deleting_destructor_(ArtifactClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
