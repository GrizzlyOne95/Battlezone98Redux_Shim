/*
 * Entry: 00456a40
 * Name: PathSpawn::`scalar_deleting_destructor'
 * Namespace: PathSpawn
 * Signature: void * `scalar_deleting_destructor'(PathSpawn * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PathSpawn::_scalar_deleting_destructor_(PathSpawn *this,uint param_1)

{
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
