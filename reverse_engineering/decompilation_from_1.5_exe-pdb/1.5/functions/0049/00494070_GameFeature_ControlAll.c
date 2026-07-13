/*
 * Entry: 00494070
 * Name: GameFeature_ControlAll
 * Namespace: Global
 * Signature: void GameFeature_ControlAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameFeature_ControlAll(void)

{
  vector<GameFeature_*,std::allocator<GameFeature_*>_> *pvVar1;
  bool bVar2;
  GameFeature **ppGVar3;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_14;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_c;
  
  pvVar1 = GameFeature::features;
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_14,GameFeature::features->_Myfirst,(_Container_base_aux *)GameFeature::features)
  ;
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
    _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
              (&local_14,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
    bVar2 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    ppGVar3 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator*
                        (&local_c);
    if (((*ppGVar3)->field_0x24 & 1) != 0) {
      (**(code **)((*ppGVar3)->_padding_ + 0x18))();
    }
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++(&local_c);
  }
  return;
}
