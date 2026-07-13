/*
 * Entry: 00452160
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::clear
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void clear(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::clear(vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  Strip **ppSVar1;
  Strip **ppSVar2;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var3;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var4;
  undefined1 local_8 [8];
  
  if (this->_Mylast < this->_Myfirst) {
    _invalid_parameter_noinfo();
  }
  ppSVar1 = this->_Myfirst;
  ppSVar2 = (Strip **)this->_padding_;
  if (this->_Mylast < ppSVar1) {
    _invalid_parameter_noinfo();
  }
  _Var3._Myptr = (Strip **)this->_padding_;
  _Var3._padding_ = (int)local_8;
  _Var4._Myptr = ppSVar2;
  _Var4._padding_ = (int)ppSVar1;
  erase(this,_Var3,_Var4);
  return;
}
