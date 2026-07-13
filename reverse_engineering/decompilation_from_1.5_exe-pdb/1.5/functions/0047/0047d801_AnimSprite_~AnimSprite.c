/*
 * Entry: 0047d801
 * Name: AnimSprite::~AnimSprite
 * Namespace: AnimSprite
 * Signature: void ~AnimSprite(AnimSprite * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimSprite::~AnimSprite(AnimSprite *this)

{
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var1;
  _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var2;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var3;
  _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var4;
  undefined1 local_28 [8];
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_20;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_18;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_10;
  AnimSprite *local_8;
  
  local_8 = this;
  std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
            (&local_20,spriteList._Mylast,(_Container_base_aux *)&spriteList);
  std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
            (&local_10,spriteList._Mylast,(_Container_base_aux *)&spriteList);
  std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
            (&local_18,spriteList._Myfirst,(_Container_base_aux *)&spriteList);
  _Var4._4_4_ = local_18._padding_;
  _Var4._0_4_ = local_28;
  _Var2._4_4_ = local_10._padding_;
  _Var2._0_4_ = local_18._Myptr;
  _Var4 = std::
          remove<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
                    (_Var4,_Var2,local_10._Myptr);
  _Var1._Myptr = (AnimSprite **)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_20;
  _Var3._Myptr = (AnimSprite **)local_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::erase(&spriteList,_Var1,_Var3);
  return;
}
