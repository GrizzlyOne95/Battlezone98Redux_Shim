/*
 * Entry: 004c7f64
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>::operator++
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>
 * Signature: _Iterator<0> * operator++(_Iterator<0> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<0> * __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>::operator++
          (_Iterator<0> *this)

{
  *(undefined4 *)&this->field_0x4 = **(undefined4 **)&this->field_0x4;
  return this;
}
