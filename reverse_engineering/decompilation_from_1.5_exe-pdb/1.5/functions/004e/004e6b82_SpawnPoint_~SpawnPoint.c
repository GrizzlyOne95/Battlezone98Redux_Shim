/*
 * Entry: 004e6b82
 * Name: SpawnPoint::~SpawnPoint
 * Namespace: SpawnPoint
 * Signature: void ~SpawnPoint(SpawnPoint * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpawnPoint::~SpawnPoint(SpawnPoint *this)

{
  float fVar1;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var2;
  _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var3;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var4;
  _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var5;
  undefined1 local_28 [8];
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_20;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_18;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_10;
  SpawnPoint *local_8;
  
  fVar1 = this[1].location.x;
  if (fVar1 != 0.0) {
    *(undefined4 *)((int)fVar1 + 0x114) = 0;
  }
  this[1].location.x = 0.0;
  local_8 = this;
  std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            (&local_20,spawnPointList->_Mylast,(_Container_base_aux *)spawnPointList);
  std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            (&local_10,spawnPointList->_Mylast,(_Container_base_aux *)spawnPointList);
  std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            (&local_18,spawnPointList->_Myfirst,(_Container_base_aux *)spawnPointList);
  _Var5._4_4_ = local_18._padding_;
  _Var5._0_4_ = local_28;
  _Var3._4_4_ = local_10._padding_;
  _Var3._0_4_ = local_18._Myptr;
  _Var5 = std::
          remove<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>
                    (_Var5,_Var3,local_10._Myptr);
  _Var2._Myptr = (SpawnPoint **)*_Var5._0_4_;
  _Var2._padding_ = (int)&local_20;
  _Var4._Myptr = (SpawnPoint **)local_20._padding_;
  _Var4._padding_ = _Var5._0_4_[1];
  std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::erase(spawnPointList,_Var2,_Var4);
  return;
}
