/*
 * Entry: 0048f659
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::erase
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
 * Signature: uint erase(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_> * this, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
::erase(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
        *this,ulong *param_1)

{
  _Iterator<1> _Var1;
  _Const_iterator<1> _Var2;
  _Iterator<1> _Var3;
  _Const_iterator<1> _Var4;
  _Node *local_14;
  int local_10;
  _Node *local_c [2];
  
  equal_range(this,(pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>_>
                    *)&local_14,param_1);
  param_1 = (ulong *)0x0;
  _Var1._4_4_ = local_10;
  _Var1._0_4_ = local_14;
  _Var3._4_4_ = local_c[1];
  _Var3._0_4_ = local_c[0];
  std::
  _Distance<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,unsigned_int>
            (_Var1,_Var3,(uint *)&param_1);
  _Var2._Ptr = local_14;
  _Var2._padding_ = (int)local_c;
  _Var4._Ptr = local_c[0];
  _Var4._padding_ = local_10;
  erase(this,_Var2,_Var4);
  return (uint)param_1;
}
