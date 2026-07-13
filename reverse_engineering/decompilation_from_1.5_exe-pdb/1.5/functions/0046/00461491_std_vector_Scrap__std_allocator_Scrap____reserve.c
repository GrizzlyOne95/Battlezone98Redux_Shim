/*
 * Entry: 00461491
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::reserve
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void reserve(vector<Scrap_*,std::allocator<Scrap_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::reserve
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,uint param_1)

{
  Scrap **ppSVar1;
  Scrap **ppSVar2;
  _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var3;
  _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var4;
  uint uVar5;
  Scrap **ppSVar6;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_14;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_c;
  
  if (param_1 < 0x40000000) {
    uVar5 = capacity(this);
    if (uVar5 < param_1) {
      ppSVar6 = _Allocate<Scrap_*>(param_1,(Scrap **)0x0);
      _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
      _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
                (&local_c,this->_Mylast,(_Container_base_aux *)this);
      _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
      _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
                (&local_14,this->_Myfirst,(_Container_base_aux *)this);
      _Var3._4_4_ = local_14._Myptr;
      _Var3._0_4_ = local_14._padding_;
      _Var4._4_4_ = local_c._Myptr;
      _Var4._0_4_ = local_c._padding_;
      _Umove<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>_>(this,_Var3,_Var4,ppSVar6);
      ppSVar1 = this->_Myfirst;
      ppSVar2 = this->_Mylast;
      if (ppSVar1 != (Scrap **)0x0) {
        operator_delete(ppSVar1);
      }
      this->_Myend = ppSVar6 + param_1;
      this->_Myfirst = ppSVar6;
      this->_Mylast = ppSVar6 + ((int)ppSVar2 - (int)ppSVar1 >> 2);
    }
  }
  else {
    _Xlen();
  }
  return;
}
