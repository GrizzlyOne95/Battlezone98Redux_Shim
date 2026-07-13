/*
 * Entry: 004b1338
 * Name: SpawnBuoy::SpawnBuoy
 * Namespace: SpawnBuoy
 * Signature: SpawnBuoy * SpawnBuoy(SpawnBuoy * this, _OBJ76 * param_1, SpawnBuoyClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnBuoy * __thiscall SpawnBuoy::SpawnBuoy(SpawnBuoy *this,_OBJ76 *param_1,SpawnBuoyClass *param_2)

{
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var1;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var2;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var3;
  bool bVar4;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var5;
  undefined1 local_24 [8];
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  DeleteCollisionEntity((tagENTITY *)this->_padding_);
  this->spawnPoint = (SpawnPoint *)0x0;
  bVar4 = Net::IsNetGame();
  if (bVar4) {
    obj_set_flag((_OBJ76 *)this->_padding_,1);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_1c,GameObject::objectList->_Mylast,
               (_Container_base_aux *)GameObject::objectList);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_c,GameObject::objectList->_Mylast,
               (_Container_base_aux *)GameObject::objectList);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_14,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    _Var5._4_4_ = local_14._padding_;
    _Var5._0_4_ = local_24;
    _Var2._4_4_ = local_c._padding_;
    _Var2._0_4_ = local_14._Myptr;
    _Var5 = std::
            remove<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,SpawnBuoy_*>
                      (_Var5,_Var2,(SpawnBuoy **)local_c._Myptr);
    _Var1._Myptr = (GameObject **)*_Var5._0_4_;
    _Var1._padding_ = (int)&local_1c;
    _Var3._Myptr = (GameObject **)local_1c._padding_;
    _Var3._padding_ = _Var5._0_4_[1];
    std::vector<GameObject_*,std::allocator<GameObject_*>_>::erase
              (GameObject::objectList,_Var1,_Var3);
  }
  return this;
}
