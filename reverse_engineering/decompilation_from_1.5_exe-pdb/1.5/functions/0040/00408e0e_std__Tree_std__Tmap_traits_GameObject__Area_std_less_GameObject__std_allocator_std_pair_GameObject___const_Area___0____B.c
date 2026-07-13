/*
 * Entry: 00408e0e
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Buynode
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: _Node * _Buynode(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this, _Node * param_1, _Node * param_2, _Node * param_3, pair<GameObject_*_const,Area> * param_4, char param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Buynode(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *this,_Node *param_1,_Node *param_2,_Node *param_3,pair<GameObject_*_const,Area> *param_4
          ,char param_5)

{
  _Node *this_00;
  
  this_00 = _Allocate<std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node>
                      (1,(_Node *)0x0);
  if (this_00 != (_Node *)0x0) {
    _Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
    ::_Node::_Node(this_00,param_1,param_2,param_3,param_4,param_5);
  }
  return this_00;
}
