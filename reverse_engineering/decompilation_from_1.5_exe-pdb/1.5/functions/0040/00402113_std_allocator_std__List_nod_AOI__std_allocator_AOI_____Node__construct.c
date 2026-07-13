/*
 * Entry: 00402113
 * Name: std::allocator<std::_List_nod<AOI_*,std::allocator<AOI_*>_>::_Node_*>::construct
 * Namespace: std::allocator<std::_List_nod<AOI_*,std::allocator<AOI_*>_>::_Node_*>
 * Signature: void construct(allocator<std::_List_nod<AOI_*,std::allocator<AOI_*>_>::_Node_*> * this, _Node * * param_1, _Node * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::_List_nod<AOI_*,std::allocator<AOI_*>_>::_Node_*>::construct
          (allocator<std::_List_nod<AOI_*,std::allocator<AOI_*>_>::_Node_*> *this,_Node **param_1,
          _Node **param_2)

{
  if (param_1 != (_Node **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
