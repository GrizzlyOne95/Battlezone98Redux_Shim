/*
 * Entry: 0047f991
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::erase
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> erase(vector<Attachment_*,std::allocator<Attachment_*>_> * this, _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> param_1, _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::erase
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this,
          _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> param_1,
          _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> param_2)

{
  bool bVar1;
  Attachment **ppAVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> _Var4;
  Attachment **in_stack_00000014;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (Attachment **)this;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
            ((_Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> *)param_1._padding_
             ,(Attachment **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::operator==
                    ((_Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> *)
                     param_1._padding_,&local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppAVar2 = stdext::unchecked_copy<Attachment_*_*,Attachment_*_*>
                        (local_c._Myptr,this->_Mylast,*(Attachment ***)(param_1._padding_ + 4));
    this->_Mylast = ppAVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
