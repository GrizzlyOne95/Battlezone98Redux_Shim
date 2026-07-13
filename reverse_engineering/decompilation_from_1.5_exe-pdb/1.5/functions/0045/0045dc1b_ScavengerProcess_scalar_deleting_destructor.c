/*
 * Entry: 0045dc1b
 * Name: ScavengerProcess::`scalar_deleting_destructor'
 * Namespace: ScavengerProcess
 * Signature: void * `scalar_deleting_destructor'(ScavengerProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ScavengerProcess::_scalar_deleting_destructor_(ScavengerProcess *this,uint param_1)

{
  ~ScavengerProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
