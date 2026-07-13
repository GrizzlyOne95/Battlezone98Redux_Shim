/*
 * Entry: 0048e967
 * Name: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>
 * Namespace: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
 * Signature: void insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>(list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_> * this, _Const_iterator<1> param_1, _Const_iterator<1> param_2, _Const_iterator<1> param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
::
insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>
          (list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
           *this,_Const_iterator<1> param_1,_Const_iterator<1> param_2,_Const_iterator<1> param_3)

{
  _Insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>
            (this,param_1,param_2,param_3,param_3._Ptr._0_1_);
  return;
}
