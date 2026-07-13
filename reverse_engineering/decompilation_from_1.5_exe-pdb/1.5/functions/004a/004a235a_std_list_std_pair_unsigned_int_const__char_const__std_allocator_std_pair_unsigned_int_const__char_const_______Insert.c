/*
 * Entry: 004a235a
 * Name: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Insert
 * Namespace: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
 * Signature: void _Insert(list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_> * this, _Const_iterator<1> param_1, pair<unsigned_int_const_,char_const_*> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
::_Insert(list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
          *this,_Const_iterator<1> param_1,pair<unsigned_int_const_,char_const_*> *param_2)

{
  _Node *p_Var1;
  
  p_Var1 = _Buynode(this,param_1._Ptr,(param_1._Ptr)->_Prev,param_2);
  _Incsize(this,1);
  (param_1._Ptr)->_Prev = p_Var1;
  p_Var1->_Prev->_Next = p_Var1;
  return;
}
