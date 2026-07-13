/*
 * Entry: 00408a3e
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Key
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: GameObject * * _Key(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Key(_Node *param_1)

{
  return &(param_1->_Myval).first;
}
