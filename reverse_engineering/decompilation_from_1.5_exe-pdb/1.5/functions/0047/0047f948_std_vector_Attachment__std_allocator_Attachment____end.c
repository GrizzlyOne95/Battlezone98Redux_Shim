/*
 * Entry: 0047f948
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::end
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> end(vector<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::end
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> _Var1;
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
