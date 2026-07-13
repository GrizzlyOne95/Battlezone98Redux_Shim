/*
 * Entry: 0041c424
 * Name: LuaMission::`scalar_deleting_destructor'
 * Namespace: LuaMission
 * Signature: void * `scalar_deleting_destructor'(LuaMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall LuaMission::_scalar_deleting_destructor_(LuaMission *this,uint param_1)

{
  ~LuaMission(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
