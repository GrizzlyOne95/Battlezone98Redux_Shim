/*
 * Entry: 00532fe5
 * Name: std::_Tree_nod<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::_Node::_Node
 * Namespace: std::_Tree_nod<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::_Node
 * Signature: _Node * _Node(_Node * this, _Node * param_1, _Node * param_2, _Node * param_3, pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * param_4, char param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree_nod<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::_Node::_Node(_Node *this,_Node *param_1,_Node *param_2,_Node *param_3,
              pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *param_4,char param_5
              )

{
  this->_Left = param_1;
  this->_Parent = param_2;
  this->_Right = param_3;
  (this->_Myval).first = param_4->first;
  (this->_Myval).second = param_4->second;
  this->_Color = param_5;
  this->_Isnil = '\0';
  return this;
}
