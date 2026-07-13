/*
 * Entry: 0052d3ec
 * Name: DayWreckerClass::`scalar_deleting_destructor'
 * Namespace: DayWreckerClass
 * Signature: void * `scalar_deleting_destructor'(DayWreckerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall DayWreckerClass::_scalar_deleting_destructor_(DayWreckerClass *this,uint param_1)

{
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
