/*
 * Entry: 0045e1be
 * Name: ExpandingArray<_loaded_aip>::Clear
 * Namespace: ExpandingArray<_loaded_aip>
 * Signature: void Clear(ExpandingArray<_loaded_aip> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExpandingArray<_loaded_aip>::Clear(ExpandingArray<_loaded_aip> *this)

{
  if (this->array != (_loaded_aip *)0x0) {
    operator_delete__(this->array);
  }
  this->array = (_loaded_aip *)0x0;
  this->size = 0;
  return;
}
