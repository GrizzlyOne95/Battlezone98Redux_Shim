/*
 * Entry: 00411867
 * Name: FactoryProcess::`scalar_deleting_destructor'
 * Namespace: FactoryProcess
 * Signature: void * `scalar_deleting_destructor'(FactoryProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FactoryProcess::_scalar_deleting_destructor_(FactoryProcess *this,uint param_1)

{
  RecyclerProcess::~RecyclerProcess((RecyclerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
