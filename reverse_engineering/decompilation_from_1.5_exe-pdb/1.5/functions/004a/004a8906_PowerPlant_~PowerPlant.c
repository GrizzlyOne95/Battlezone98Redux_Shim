/*
 * Entry: 004a8906
 * Name: PowerPlant::~PowerPlant
 * Namespace: PowerPlant
 * Signature: void ~PowerPlant(PowerPlant * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerPlant::~PowerPlant(PowerPlant *this)

{
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var1;
  _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var2;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var3;
  _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var4;
  undefined1 local_28 [8];
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_20;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_18;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_10;
  PowerPlant *local_8;
  
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  local_8 = this;
  std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
            (&local_20,powerPlantList._Mylast,(_Container_base_aux *)&powerPlantList);
  std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
            (&local_10,powerPlantList._Mylast,(_Container_base_aux *)&powerPlantList);
  std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
            (&local_18,powerPlantList._Myfirst,(_Container_base_aux *)&powerPlantList);
  _Var4._4_4_ = local_18._padding_;
  _Var4._0_4_ = local_28;
  _Var2._4_4_ = local_10._padding_;
  _Var2._0_4_ = local_18._Myptr;
  _Var4 = std::
          remove<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>
                    (_Var4,_Var2,local_10._Myptr);
  _Var1._Myptr = (PowerPlant **)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_20;
  _Var3._Myptr = (PowerPlant **)local_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::erase(&powerPlantList,_Var1,_Var3);
  Building::~Building((Building *)this);
  return;
}
