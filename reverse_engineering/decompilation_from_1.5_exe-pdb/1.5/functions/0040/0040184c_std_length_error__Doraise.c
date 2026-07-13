/*
 * Entry: 0040184c
 * Name: std::length_error::_Doraise
 * Namespace: std::length_error
 * Signature: void _Doraise(length_error * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall std::length_error::_Doraise(length_error *this)

{
  std::_Throw((exception *)this);
  return;
}
