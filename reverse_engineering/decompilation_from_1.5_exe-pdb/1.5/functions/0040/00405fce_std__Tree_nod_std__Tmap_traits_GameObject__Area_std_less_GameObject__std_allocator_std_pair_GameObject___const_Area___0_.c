/*
 * Entry: 00405fce
 * Name: std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node::_Node
 * Namespace: std::_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Node
 * Signature: _Node * _Node(_Node * this, _Node * param_1, _Node * param_2, _Node * param_3, pair<GameObject_*_const,Area> * param_4, char param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree_nod<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Node::_Node(_Node *this,_Node *param_1,_Node *param_2,_Node *param_3,
              pair<GameObject_*_const,Area> *param_4,char param_5)

{
  int iVar1;
  pair<GameObject_*_const,Area> *ppVar2;
  
  this->_Left = param_1;
  this->_Parent = param_2;
  this->_Right = param_3;
  ppVar2 = &this->_Myval;
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    ppVar2->first = param_4->first;
    param_4 = (pair<GameObject_*_const,Area> *)&param_4->second;
    ppVar2 = (pair<GameObject_*_const,Area> *)&ppVar2->second;
  }
  this->_Color = param_5;
  this->_Isnil = '\0';
  return this;
}
