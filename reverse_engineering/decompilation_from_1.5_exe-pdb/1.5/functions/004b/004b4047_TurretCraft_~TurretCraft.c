/*
 * Entry: 004b4047
 * Name: TurretCraft::~TurretCraft
 * Namespace: TurretCraft
 * Signature: void ~TurretCraft(TurretCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::~TurretCraft(TurretCraft *this)

{
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Var1;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var2;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Var3;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var4;
  undefined1 auStack_28 [8];
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_20;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_18;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_10;
  TurretCraft *pTStack_8;
  
  this->_padding_ = (int)&Craft::_vftable__for__Attachable__;
  this->_padding_ = (int)&Craft::_vftable__for__DistributedObject__;
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  pTStack_8 = this;
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&_Stack_20,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&_Stack_10,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&_Stack_18,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
  _Var4._4_4_ = _Stack_18._padding_;
  _Var4._0_4_ = auStack_28;
  _Var2._4_4_ = _Stack_10._padding_;
  _Var2._0_4_ = _Stack_18._Myptr;
  _Var4 = std::remove<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
                    (_Var4,_Var2,_Stack_10._Myptr);
  _Var1._Myptr = (Craft **)*_Var4._0_4_;
  _Var1._padding_ = (int)&_Stack_20;
  _Var3._Myptr = (Craft **)_Stack_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<Craft_*,std::allocator<Craft_*>_>::erase(&Craft::craftList,_Var1,_Var3);
  GameObject::~GameObject((GameObject *)this);
  return;
}
