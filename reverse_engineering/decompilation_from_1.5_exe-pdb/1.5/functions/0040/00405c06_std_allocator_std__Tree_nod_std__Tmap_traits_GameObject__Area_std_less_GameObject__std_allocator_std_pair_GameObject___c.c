/*
 * Entry: 00405c06
 * Name: std::allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>::deallocate
 * Namespace: std::allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
 * Signature: void deallocate(allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node> * this, _Node * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
::deallocate(allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
             *this,_Node *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
