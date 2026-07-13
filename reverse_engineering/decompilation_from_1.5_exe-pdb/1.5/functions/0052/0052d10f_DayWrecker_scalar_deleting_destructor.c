/*
 * Entry: 0052d10f
 * Name: DayWrecker::`scalar_deleting_destructor'
 * Namespace: DayWrecker
 * Signature: void * `scalar_deleting_destructor'(DayWrecker * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall DayWrecker::_scalar_deleting_destructor_(DayWrecker *this,uint param_1)

{
  PowerUp::~PowerUp((PowerUp *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
