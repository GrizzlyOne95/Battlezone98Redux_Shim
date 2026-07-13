/*
 * Entry: 0047d0a4
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::begin
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> begin(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::begin
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var1;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
