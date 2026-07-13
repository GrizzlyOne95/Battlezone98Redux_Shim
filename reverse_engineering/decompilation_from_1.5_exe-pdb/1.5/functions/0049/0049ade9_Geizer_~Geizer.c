/*
 * Entry: 0049ade9
 * Name: Geizer::~Geizer
 * Namespace: Geizer
 * Signature: void ~Geizer(Geizer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Geizer::~Geizer(Geizer *this)

{
  uint *puVar1;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var2;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var3;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var4;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var5;
  undefined1 local_28 [8];
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_20;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_18;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_10;
  Geizer *local_8;
  
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 | 0x401;
  this->isSteamOn = false;
  local_8 = this;
  std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_20,geizerList._Mylast,(_Container_base_aux *)&geizerList);
  std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_10,geizerList._Mylast,(_Container_base_aux *)&geizerList);
  std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_18,geizerList._Myfirst,(_Container_base_aux *)&geizerList);
  _Var5._4_4_ = local_18._padding_;
  _Var5._0_4_ = local_28;
  _Var3._4_4_ = local_10._padding_;
  _Var3._0_4_ = local_18._Myptr;
  _Var5 = std::remove<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
                    (_Var5,_Var3,local_10._Myptr);
  _Var2._Myptr = (Geizer **)*_Var5._0_4_;
  _Var2._padding_ = (int)&local_20;
  _Var4._Myptr = (Geizer **)local_20._padding_;
  _Var4._padding_ = _Var5._0_4_[1];
  std::vector<Geizer_*,std::allocator<Geizer_*>_>::erase(&geizerList,_Var2,_Var4);
  Building::~Building((Building *)this);
  return;
}
