/*
 * Entry: 004c817d
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>::_Iterator<0>
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>
 * Signature: _Iterator<0> * _Iterator<0>(_Iterator<0> * this, _Node * param_1, list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<0> * __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>::_Iterator<0>
          (_Iterator<0> *this,_Node *param_1,
          list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *param_2)

{
  *(undefined4 *)this = 0;
  *(_Node **)&this->field_0x4 = param_1;
  *(int *)this = param_2->_padding_;
  return this;
}
