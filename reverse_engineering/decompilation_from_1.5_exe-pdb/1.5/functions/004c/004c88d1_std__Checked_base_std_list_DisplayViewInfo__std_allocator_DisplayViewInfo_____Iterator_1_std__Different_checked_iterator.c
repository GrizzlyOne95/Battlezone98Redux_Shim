/*
 * Entry: 004c88d1
 * Name: std::_Checked_base<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::_Different_checked_iterator_base_type_tag>
 * Namespace: std
 * Signature: _Iterator<0> _Checked_base<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::_Different_checked_iterator_base_type_tag>(_Iterator<1> * param_1, _Different_checked_iterator_base_type_tag param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<0> __cdecl
std::
_Checked_base<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::_Different_checked_iterator_base_type_tag>
          (_Iterator<1> *param_1,_Different_checked_iterator_base_type_tag param_2)

{
  _Iterator<0> _Var1;
  _Iterator<0> _Var2;
  undefined4 unaff_retaddr;
  undefined3 in_stack_00000009;
  
  _Var1 = list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
          _Checked_iterator_base(_param_2);
  _Var2._4_4_ = _Var1._4_4_;
  _Var2._0_4_ = unaff_retaddr;
  return _Var2;
}
