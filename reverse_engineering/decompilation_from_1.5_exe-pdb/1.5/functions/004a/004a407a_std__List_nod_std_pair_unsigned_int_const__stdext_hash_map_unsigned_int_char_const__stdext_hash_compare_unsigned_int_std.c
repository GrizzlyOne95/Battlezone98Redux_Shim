/*
 * Entry: 004a407a
 * Name: std::_List_nod<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>::_Node::`scalar_deleting_destructor'
 * Namespace: std::_List_nod<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>::_Node
 * Signature: void * `scalar_deleting_destructor'(_Node * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
std::
_List_nod<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>
::_Node::_scalar_deleting_destructor_(_Node *this,uint param_1)

{
  stdext::
  _Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
  ::
  ~_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
            ((_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
              *)&(this->_Myval).second);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
