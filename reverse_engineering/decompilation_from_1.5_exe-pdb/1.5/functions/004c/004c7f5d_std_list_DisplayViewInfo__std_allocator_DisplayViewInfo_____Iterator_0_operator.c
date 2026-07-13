/*
 * Entry: 004c7f5d
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>::operator*
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>
 * Signature: DisplayViewInfo * * operator*(_Iterator<0> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DisplayViewInfo ** __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>::operator*
          (_Iterator<0> *this)

{
  return (DisplayViewInfo **)(*(int *)&this->field_0x4 + 8);
}
