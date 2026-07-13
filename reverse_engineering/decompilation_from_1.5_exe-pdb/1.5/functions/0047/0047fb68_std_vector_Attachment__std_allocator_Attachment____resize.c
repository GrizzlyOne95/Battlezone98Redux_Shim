/*
 * Entry: 0047fb68
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::resize
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: void resize(vector<Attachment_*,std::allocator<Attachment_*>_> * this, uint param_1, Attachment * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::resize
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this,uint param_1,Attachment *param_2
          )

{
  Attachment **ppAVar1;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> _Var2;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> _Var3;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> _Var4;
  uint uVar5;
  _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> _Var6;
  undefined1 local_1c [8];
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> local_14;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> local_c;
  
  ppAVar1 = this->_Mylast;
  uVar5 = (int)ppAVar1 - (int)this->_Myfirst >> 2;
  if (uVar5 < param_1) {
    _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
    _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
              (&local_c,ppAVar1,(_Container_base_aux *)this);
    _Var3._Myptr = local_c._Myptr;
    _Var3._padding_ = local_c._padding_;
    _Insert_n(this,_Var3,param_1 - ((int)this->_Mylast - (int)this->_Myfirst >> 2),&param_2);
  }
  else if (param_1 < uVar5) {
    _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
    _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
              (&local_c,ppAVar1,(_Container_base_aux *)this);
    _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
    _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
              (&local_14,this->_Myfirst,(_Container_base_aux *)this);
    _Var6 = _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>::operator+
                      ((_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> *)&local_14,
                       (int)local_1c);
    _Var2._Myptr = (Attachment **)*_Var6._0_4_;
    _Var2._padding_ = (int)&local_14;
    _Var4._Myptr = (Attachment **)local_c._padding_;
    _Var4._padding_ = _Var6._0_4_[1];
    erase(this,_Var2,_Var4);
  }
  return;
}
