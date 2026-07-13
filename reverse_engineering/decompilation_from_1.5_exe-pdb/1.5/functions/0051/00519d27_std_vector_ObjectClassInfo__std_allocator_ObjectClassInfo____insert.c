/*
 * Entry: 00519d27
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::insert
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> insert(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> param_1, ObjectClassInfo * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::insert
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,
          _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> param_1,
          ObjectClassInfo **param_2)

{
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> _Var1;
  _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> _Var2;
  ObjectClassInfo **in_stack_00000010;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (ObjectClassInfo **)this;
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
              (&local_c,this->_Myfirst,(_Container_base_aux *)this);
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator-
              ((_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *)
               &param_1._Myptr,&local_c);
  }
  _Var1._Myptr = param_2;
  _Var1._padding_ = (int)param_1._Myptr;
  _Insert_n(this,_Var1,1,in_stack_00000010);
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            (&local_c,this->_Myfirst,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator+
                    ((_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *)
                     &local_c,param_1._padding_);
  _Var2._0_4_ = param_1._padding_;
  return _Var2;
}
