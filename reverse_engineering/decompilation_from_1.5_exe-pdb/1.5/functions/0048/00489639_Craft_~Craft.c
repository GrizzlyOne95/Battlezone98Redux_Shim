/*
 * Entry: 00489639
 * Name: Craft::~Craft
 * Namespace: Craft
 * Signature: void ~Craft(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::~Craft(Craft *this)

{
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Var1;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var2;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Var3;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var4;
  undefined1 local_28 [8];
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_20;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_18;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_10;
  Craft *local_8;
  
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  local_8 = this;
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_20,craftList._Mylast,(_Container_base_aux *)&craftList);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_10,craftList._Mylast,(_Container_base_aux *)&craftList);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_18,craftList._Myfirst,(_Container_base_aux *)&craftList);
  _Var4._4_4_ = local_18._padding_;
  _Var4._0_4_ = local_28;
  _Var2._4_4_ = local_10._padding_;
  _Var2._0_4_ = local_18._Myptr;
  _Var4 = std::remove<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
                    (_Var4,_Var2,local_10._Myptr);
  _Var1._Myptr = (Craft **)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_20;
  _Var3._Myptr = (Craft **)local_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<Craft_*,std::allocator<Craft_*>_>::erase(&craftList,_Var1,_Var3);
  GameObject::~GameObject((GameObject *)this);
  return;
}
