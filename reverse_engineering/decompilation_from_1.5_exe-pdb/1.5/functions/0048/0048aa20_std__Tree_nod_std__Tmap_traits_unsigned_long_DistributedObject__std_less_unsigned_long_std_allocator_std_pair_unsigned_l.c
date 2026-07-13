/*
 * Entry: 0048aa20
 * Name: std::_Tree_nod<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::_Node::_Node
 * Namespace: std::_Tree_nod<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::_Node
 * Signature: _Node * _Node(_Node * this, _Node * param_1, _Node * param_2, _Node * param_3, pair<unsigned_long_const_,DistributedObject_*> * param_4, char param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree_nod<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::_Node::_Node(_Node *this,_Node *param_1,_Node *param_2,_Node *param_3,
              pair<unsigned_long_const_,DistributedObject_*> *param_4,char param_5)

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
