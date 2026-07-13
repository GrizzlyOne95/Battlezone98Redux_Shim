/*
 * Entry: 0047ccb5
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::_Buynode
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
 * Signature: _Node * _Buynode(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::_Buynode(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_Tree_nod<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Left = (_Node *)0x0;
  }
  if (&p_Var1->_Parent != (_Node **)0x0) {
    p_Var1->_Parent = (_Node *)0x0;
  }
  if (&p_Var1->_Right != (_Node **)0x0) {
    p_Var1->_Right = (_Node *)0x0;
  }
  p_Var1->_Isnil = '\0';
  p_Var1->_Color = '\x01';
  return p_Var1;
}
