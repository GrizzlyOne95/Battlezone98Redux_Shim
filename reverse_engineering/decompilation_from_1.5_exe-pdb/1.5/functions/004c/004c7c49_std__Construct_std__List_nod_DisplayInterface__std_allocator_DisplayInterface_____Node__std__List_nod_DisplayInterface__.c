/*
 * Entry: 004c7c49
 * Name: std::_Construct<std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node_*,std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node_*>
 * Namespace: std
 * Signature: void _Construct<std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node_*,std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node_*>(_Node * * param_1, _Node * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Construct<std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node_*,std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node_*>
          (_Node **param_1,_Node **param_2)

{
  if (param_1 != (_Node **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
