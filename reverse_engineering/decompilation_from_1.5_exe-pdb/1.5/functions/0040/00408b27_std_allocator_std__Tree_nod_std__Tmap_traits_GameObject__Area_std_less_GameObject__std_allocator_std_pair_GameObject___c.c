/*
 * Entry: 00408b27
 * Name: std::allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>::allocate
 * Namespace: std::allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
 * Signature: _Node * allocate(allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
::allocate(allocator<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
           *this,uint param_1)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
                     (param_1,(_Node *)0x0);
  return p_Var1;
}
