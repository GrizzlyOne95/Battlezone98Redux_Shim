/*
 * Entry: 00401e1a
 * Name: std::_Construct<std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::_Node_*,std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::_Node_*>
 * Namespace: std
 * Signature: void _Construct<std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::_Node_*,std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::_Node_*>(_Node * * param_1, _Node * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Construct<std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::_Node_*,std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::_Node_*>
          (_Node **param_1,_Node **param_2)

{
  if (param_1 != (_Node **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
