/*
 * Entry: 00508c50
 * Name: Mapgrid_Goal::`scalar_deleting_destructor'
 * Namespace: Mapgrid_Goal
 * Signature: void * `scalar_deleting_destructor'(Mapgrid_Goal * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Mapgrid_Goal::_scalar_deleting_destructor_(Mapgrid_Goal *this,uint param_1)

{
  ~Mapgrid_Goal(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
