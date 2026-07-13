/*
 * Entry: 004ae5d4
 * Name: Scanner::~Scanner
 * Namespace: Scanner
 * Signature: void ~Scanner(Scanner * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scanner::~Scanner(Scanner *this)

{
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var1;
  _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var2;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var3;
  _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var4;
  undefined1 local_28 [8];
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> local_20;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> local_18;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> local_10;
  Scanner *local_8;
  
  local_8 = this;
  std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            (&local_20,scannerList._Mylast,(_Container_base_aux *)&scannerList);
  std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            (&local_10,scannerList._Mylast,(_Container_base_aux *)&scannerList);
  std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            (&local_18,scannerList._Myfirst,(_Container_base_aux *)&scannerList);
  _Var4._4_4_ = local_18._padding_;
  _Var4._0_4_ = local_28;
  _Var2._4_4_ = local_10._padding_;
  _Var2._0_4_ = local_18._Myptr;
  _Var4 = std::remove<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>
                    (_Var4,_Var2,local_10._Myptr);
  _Var1._Myptr = (Scanner **)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_20;
  _Var3._Myptr = (Scanner **)local_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<Scanner_*,std::allocator<Scanner_*>_>::erase(&scannerList,_Var1,_Var3);
  return;
}
