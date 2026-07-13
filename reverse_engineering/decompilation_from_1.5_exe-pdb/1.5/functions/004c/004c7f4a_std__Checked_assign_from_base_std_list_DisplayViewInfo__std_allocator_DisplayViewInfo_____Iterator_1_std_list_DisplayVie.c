/*
 * Entry: 004c7f4a
 * Name: std::_Checked_assign_from_base<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>_>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>_>(_Iterator<1> * param_1, _Iterator<0> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>_>
          (_Iterator<1> *param_1,_Iterator<0> *param_2)

{
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
  _Checked_iterator_assign_from_base(param_1,*(_Iterator<0> *)param_2);
  return;
}
