/*
 * Entry: 004c80fd
 * Name: std::_Find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,IsMyView>
 * Namespace: std
 * Signature: _Iterator<0> _Find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,IsMyView>(_Iterator<0> param_1, _Iterator<0> param_2, IsMyView param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<0> __cdecl
std::
_Find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,IsMyView>
          (_Iterator<0> param_1,_Iterator<0> param_2,IsMyView param_3)

{
  int in_stack_00000018;
  
  while (((DisplayInterface *)param_2._0_4_ != param_3.me &&
         (*(int *)(((DisplayInterface *)(param_2._0_4_ + 8))->_padding_ + 4) != in_stack_00000018)))
  {
    param_2._0_4_ = ((DisplayInterface *)param_2._0_4_)->_padding_;
  }
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(undefined4 *)(param_1._0_4_ + 4) = param_2._0_4_;
  return param_1;
}
