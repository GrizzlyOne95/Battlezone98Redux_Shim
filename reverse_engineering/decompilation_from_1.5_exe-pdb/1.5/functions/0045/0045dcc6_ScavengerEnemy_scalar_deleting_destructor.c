/*
 * Entry: 0045dcc6
 * Name: ScavengerEnemy::`scalar_deleting_destructor'
 * Namespace: ScavengerEnemy
 * Signature: void * `scalar_deleting_destructor'(ScavengerEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScavengerEnemy::_scalar_deleting_destructor_(ScavengerEnemy *this,uint param_1)

{
  ScavengerProcess::~ScavengerProcess((ScavengerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
