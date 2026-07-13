/*
 * Entry: 00461dbe
 * Name: std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node::_Node
 * Namespace: std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node
 * Signature: _Node * _Node(_Node * this, _Node * param_1, _Node * param_2, _Node * param_3, OpenNode * param_4, char param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::_Node::_Node(_Node *this,_Node *param_1,_Node *param_2,_Node *param_3,OpenNode *param_4,
              char param_5)

{
  this->_Left = param_1;
  this->_Parent = param_2;
  this->_Right = param_3;
  (this->_Myval).m_Node = param_4->m_Node;
  (this->_Myval).g = param_4->g;
  (this->_Myval).h = param_4->h;
  this->_Color = param_5;
  this->_Isnil = '\0';
  return this;
}
