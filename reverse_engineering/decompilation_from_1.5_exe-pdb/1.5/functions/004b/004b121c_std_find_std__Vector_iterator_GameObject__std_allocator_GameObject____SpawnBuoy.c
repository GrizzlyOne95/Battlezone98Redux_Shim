/*
 * Entry: 004b121c
 * Name: std::find<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,SpawnBuoy_*>
 * Namespace: std
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> find<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,SpawnBuoy_*>(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1, _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2, SpawnBuoy * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> __cdecl
std::find<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,SpawnBuoy_*>
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1,
          _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2,SpawnBuoy **param_3)

{
  GameObject **ppGVar1;
  SpawnBuoy **in_stack_00000018;
  
  ppGVar1 = _Find<GameObject_*_*,SpawnBuoy_*>
                      ((GameObject **)param_2._0_4_,(GameObject **)param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(GameObject ***)(param_1._0_4_ + 4) = ppGVar1;
  return param_1;
}
