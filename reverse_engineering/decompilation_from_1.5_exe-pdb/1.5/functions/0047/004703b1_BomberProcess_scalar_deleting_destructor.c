/*
 * Entry: 004703b1
 * Name: BomberProcess::`scalar_deleting_destructor'
 * Namespace: BomberProcess
 * Signature: void * `scalar_deleting_destructor'(BomberProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BomberProcess::_scalar_deleting_destructor_(BomberProcess *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
