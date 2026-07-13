/*
 * Entry: 00484f12
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::end
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> end(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::end
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var1;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
