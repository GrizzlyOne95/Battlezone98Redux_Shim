/*
 * Entry: 00518e00
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::end
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> end(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::end
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> _Var1;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
