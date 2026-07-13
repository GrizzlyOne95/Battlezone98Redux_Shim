/*
 * Entry: 004a2f53
 * Name: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Splice
 * Namespace: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
 * Signature: void _Splice(list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_> * this, _Const_iterator<1> param_1, list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_> * param_2, _Const_iterator<1> param_3, _Const_iterator<1> param_4, uint param_5, bool param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
::_Splice(list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
          *this,_Const_iterator<1> param_1,
         list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
         *param_2,_Const_iterator<1> param_3,_Const_iterator<1> param_4,uint param_5,bool param_6)

{
  _Node *p_Var1;
  
  if (this != param_2) {
    _Incsize(this,param_5);
    param_2->_Mysize = param_2->_Mysize - param_5;
  }
  (param_3._Ptr)->_Prev->_Next = param_4._Ptr;
  (param_4._Ptr)->_Prev->_Next = param_1._Ptr;
  (param_1._Ptr)->_Prev->_Next = param_3._Ptr;
  p_Var1 = (param_1._Ptr)->_Prev;
  (param_1._Ptr)->_Prev = (param_4._Ptr)->_Prev;
  (param_4._Ptr)->_Prev = (param_3._Ptr)->_Prev;
  (param_3._Ptr)->_Prev = p_Var1;
  return;
}
