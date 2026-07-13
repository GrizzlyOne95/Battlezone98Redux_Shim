/*
 * Entry: 004609d4
 * Name: ExpandingArray<_loaded_aip>::~ExpandingArray<_loaded_aip>
 * Namespace: ExpandingArray<_loaded_aip>
 * Signature: void ~ExpandingArray<_loaded_aip>(ExpandingArray<_loaded_aip> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ExpandingArray<_loaded_aip>::~ExpandingArray<_loaded_aip>(ExpandingArray<_loaded_aip> *this)

{
  if (this->array != (_loaded_aip *)0x0) {
    operator_delete__(this->array);
  }
  this->array = (_loaded_aip *)0x0;
  this->size = 0;
  return;
}
