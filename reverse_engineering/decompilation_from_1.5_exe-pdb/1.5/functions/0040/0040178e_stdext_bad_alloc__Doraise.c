/*
 * Entry: 0040178e
 * Name: stdext::bad_alloc::_Doraise
 * Namespace: stdext::bad_alloc
 * Signature: void _Doraise(bad_alloc * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall stdext::bad_alloc::_Doraise(bad_alloc *this)

{
  std::_Throw((exception *)this);
  return;
}
