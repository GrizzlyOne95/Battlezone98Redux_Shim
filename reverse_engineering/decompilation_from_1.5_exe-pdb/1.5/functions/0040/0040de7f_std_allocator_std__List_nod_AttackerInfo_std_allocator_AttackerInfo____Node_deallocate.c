/*
 * Entry: 0040de7f
 * Name: std::allocator<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node>::deallocate
 * Namespace: std::allocator<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node>
 * Signature: void deallocate(allocator<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node> * this, _Node * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node>::deallocate
          (allocator<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node> *this,
          _Node *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
