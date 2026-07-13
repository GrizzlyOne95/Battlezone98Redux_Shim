/*
 * Entry: 004c7cca
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::_Checked_iterator_assign_from_base
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>
 * Signature: void _Checked_iterator_assign_from_base(_Iterator<1> * this, _Iterator<0> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
_Checked_iterator_assign_from_base(_Iterator<1> *this,_Iterator<0> param_1)

{
  if (*(int *)this != param_1._0_4_) {
    _invalid_parameter_noinfo();
  }
  *(undefined4 *)&this->field_0x4 = param_1._4_4_;
  return;
}
