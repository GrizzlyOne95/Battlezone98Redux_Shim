/*
 * Entry: 004b0ab8
 * Name: std::allocator<std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Node>::deallocate
 * Namespace: std::allocator<std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Node>
 * Signature: void deallocate(allocator<std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Node> * this, _Node * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Node>::deallocate
          (allocator<std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Node> *this,
          _Node *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
