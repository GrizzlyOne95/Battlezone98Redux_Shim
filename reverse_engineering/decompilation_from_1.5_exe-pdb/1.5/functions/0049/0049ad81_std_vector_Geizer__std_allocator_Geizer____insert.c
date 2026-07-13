/*
 * Entry: 0049ad81
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::insert
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> insert(vector<Geizer_*,std::allocator<Geizer_*>_> * this, _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1, Geizer * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::insert
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,
          _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1,Geizer **param_2)

{
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var1;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var2;
  Geizer **in_stack_00000010;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (Geizer **)this;
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
              (&local_c,this->_Myfirst,(_Container_base_aux *)this);
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator-
              ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&param_1._Myptr,
               &local_c);
  }
  _Var1._Myptr = param_2;
  _Var1._padding_ = (int)param_1._Myptr;
  _Insert_n(this,_Var1,1,in_stack_00000010);
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_c,this->_Myfirst,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator+
                    ((_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&local_c,
                     param_1._padding_);
  _Var2._0_4_ = param_1._padding_;
  return _Var2;
}
