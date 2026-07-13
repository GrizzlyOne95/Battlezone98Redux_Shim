/*
 * Entry: 004c8347
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::_Checked_iterator_base
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>
 * Signature: _Iterator<0> _Checked_iterator_base(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<0> __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
_Checked_iterator_base(_Iterator<1> *this)

{
  undefined4 *puVar1;
  _Iterator<0> _Var2;
  undefined4 *in_stack_00000004;
  
  if (*(undefined4 **)this == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = (undefined4 *)**(undefined4 **)this;
  }
  in_stack_00000004[1] = *(undefined4 *)&this->field_0x4;
  *in_stack_00000004 = *puVar1;
  _Var2._4_4_ = puVar1;
  _Var2._0_4_ = in_stack_00000004;
  return _Var2;
}
