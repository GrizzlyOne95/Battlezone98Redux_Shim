/*
 * Entry: 004133b8
 * Name: GetNearestGeizer
 * Namespace: Global
 * Signature: Geizer * GetNearestGeizer(VECTOR_3D * param_1, Geizer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer * __cdecl GetNearestGeizer(VECTOR_3D *param_1,Geizer *param_2)

{
  bool bVar1;
  Geizer **ppGVar2;
  VECTOR_3D *pVVar3;
  float fVar4;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_20;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_18;
  Geizer *local_10;
  Geizer *local_c;
  float local_8;
  
  local_c = (Geizer *)0x0;
  local_8 = 1e+30;
  std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_20,Geizer::geizerList._Myfirst,(_Container_base_aux *)&Geizer::geizerList);
  local_18._padding_ = local_20._padding_;
  local_18._Myptr = local_20._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
              (&local_20,Geizer::geizerList._Mylast,(_Container_base_aux *)&Geizer::geizerList);
    bVar1 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator==
                      (&local_18,&local_20);
    if (bVar1) break;
    ppGVar2 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*(&local_18);
    local_10 = *ppGVar2;
    if ((local_10 != param_2) && (local_10->isLocked == false)) {
      pVVar3 = (VECTOR_3D *)(**(code **)(local_10->_padding_ + 0xc))();
      fVar4 = Dist3D_Squared(*param_1,*pVVar3);
      if (fVar4 < local_8) {
        local_c = local_10;
        local_8 = fVar4;
      }
    }
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++(&local_18);
  }
  return local_c;
}
