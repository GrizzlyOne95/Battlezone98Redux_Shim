/*
 * Entry: 004587e6
 * Name: Range::~Range
 * Namespace: Range
 * Signature: void ~Range(Range * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Range::~Range(Range *this)

{
  operator_delete__(this->objects);
  operator_delete__(this->firstObject);
  return;
}
