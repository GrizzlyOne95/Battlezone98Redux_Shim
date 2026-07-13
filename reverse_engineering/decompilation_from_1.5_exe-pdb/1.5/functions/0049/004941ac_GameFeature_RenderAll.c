/*
 * Entry: 004941ac
 * Name: GameFeature_RenderAll
 * Namespace: Global
 * Signature: void GameFeature_RenderAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameFeature_RenderAll(void)

{
  vector<GameFeature_*,std::allocator<GameFeature_*>_> *pvVar1;
  bool bVar2;
  GameFeature **ppGVar3;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_18;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_10;
  float local_8;
  
  pvVar1 = GameFeature::features;
  local_8 = spriteZ;
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_18,GameFeature::features->_Myfirst,(_Container_base_aux *)GameFeature::features)
  ;
  local_10._padding_ = local_18._padding_;
  local_10._Myptr = local_18._Myptr;
  while( true ) {
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
    _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
              (&local_18,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
    bVar2 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator==
                      (&local_10,&local_18);
    if (bVar2) break;
    ppGVar3 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator*
                        (&local_10);
    if (((*ppGVar3)->field_0x24 & 8) != 0) {
      (**(code **)((*ppGVar3)->_padding_ + 0x24))();
      spriteZ = local_8;
    }
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++(&local_10)
    ;
  }
  return;
}
