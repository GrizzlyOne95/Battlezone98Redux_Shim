/*
 * Entry: 00401775
 * Name: stdext::bad_alloc::bad_alloc
 * Namespace: stdext::bad_alloc
 * Signature: bad_alloc * bad_alloc(bad_alloc * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bad_alloc * __thiscall stdext::bad_alloc::bad_alloc(bad_alloc *this,char *param_1)

{
  *(char **)&this->field_0x4 = param_1;
  *(undefined ***)this = &_vftable_;
  return this;
}
