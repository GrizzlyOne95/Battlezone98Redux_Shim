/*
 * Entry: 00498533
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::reserve
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: void reserve(vector<GameObject_*,std::allocator<GameObject_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::reserve
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,uint param_1)

{
  GameObject **ppGVar1;
  GameObject **ppGVar2;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var3;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var4;
  uint uVar5;
  GameObject **ppGVar6;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  if (param_1 < 0x40000000) {
    uVar5 = capacity(this);
    if (uVar5 < param_1) {
      ppGVar6 = _Allocate<GameObject_*>(param_1,(GameObject **)0x0);
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_c,this->_Mylast,(_Container_base_aux *)this);
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_14,this->_Myfirst,(_Container_base_aux *)this);
      _Var3._4_4_ = local_14._Myptr;
      _Var3._0_4_ = local_14._padding_;
      _Var4._4_4_ = local_c._Myptr;
      _Var4._0_4_ = local_c._padding_;
      _Umove<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>_>
                (this,_Var3,_Var4,ppGVar6);
      ppGVar1 = this->_Myfirst;
      ppGVar2 = this->_Mylast;
      if (ppGVar1 != (GameObject **)0x0) {
        operator_delete(ppGVar1);
      }
      this->_Myend = ppGVar6 + param_1;
      this->_Myfirst = ppGVar6;
      this->_Mylast = ppGVar6 + ((int)ppGVar2 - (int)ppGVar1 >> 2);
    }
  }
  else {
    _Xlen();
  }
  return;
}
