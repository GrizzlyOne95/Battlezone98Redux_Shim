/*
 * Entry: 00493fb0
 * Name: GF_AddEntity
 * Namespace: Global
 * Signature: void GF_AddEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GF_AddEntity(tagENTITY *param_1)

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
    (**(code **)((*ppGVar3)->_padding_ + 0x28))(param_1);
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++(&local_c);
  }
  return;
}
