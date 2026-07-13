/*
 * Entry: 004c9945
 * Name: EditTerrain::`scalar_deleting_destructor'
 * Namespace: EditTerrain
 * Signature: void * `scalar_deleting_destructor'(EditTerrain * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall EditTerrain::_scalar_deleting_destructor_(EditTerrain *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
