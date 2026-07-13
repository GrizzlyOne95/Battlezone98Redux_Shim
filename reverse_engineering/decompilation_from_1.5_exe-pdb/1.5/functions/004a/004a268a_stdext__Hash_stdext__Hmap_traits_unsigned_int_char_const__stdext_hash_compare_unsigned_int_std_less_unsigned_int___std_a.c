/*
 * Entry: 004a268a
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::end
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
 * Signature: _Const_iterator<1> end(_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
::end(_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
      *this)

{
  _Node *extraout_EDX;
  _Const_iterator<1> _Var1;
  _Const_iterator<1> *in_stack_00000004;
  
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(in_stack_00000004,(this->_List)._Myhead,&this->_List);
  _Var1._Ptr = extraout_EDX;
  _Var1._padding_ = (int)in_stack_00000004;
  return _Var1;
}
