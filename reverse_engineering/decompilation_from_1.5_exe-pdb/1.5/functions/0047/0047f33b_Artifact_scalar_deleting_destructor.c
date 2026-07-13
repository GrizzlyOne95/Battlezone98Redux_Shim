/*
 * Entry: 0047f33b
 * Name: Artifact::`scalar_deleting_destructor'
 * Namespace: Artifact
 * Signature: void * `scalar_deleting_destructor'(Artifact * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Artifact::_scalar_deleting_destructor_(Artifact *this,uint param_1)

{
  ~Artifact(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
