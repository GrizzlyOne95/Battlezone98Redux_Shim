/*
 * Entry: 00494bf1
 * Name: GameFeature_InitAll
 * Namespace: Global
 * Signature: void GameFeature_InitAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameFeature_InitAll(void)

{
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var1;
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var2;
  vector<GameFeature_*,std::allocator<GameFeature_*>_> *pvVar3;
  bool bVar4;
  GameFeature **ppGVar5;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_14;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_c;
  
  pvVar3 = GameFeature::features;
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_14,GameFeature::features->_Mylast,(_Container_base_aux *)GameFeature::features);
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_c,pvVar3->_Myfirst,(_Container_base_aux *)pvVar3);
  _Var1._4_4_ = local_c._Myptr;
  _Var1._0_4_ = local_c._padding_;
  _Var2._4_4_ = local_14._Myptr;
  _Var2._0_4_ = local_14._padding_;
  std::sort<std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>,GFInitPri>
            (_Var1,_Var2,gfInitPri);
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_14,pvVar3->_Myfirst,(_Container_base_aux *)pvVar3);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
    _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
              (&local_14,pvVar3->_Mylast,(_Container_base_aux *)pvVar3);
    bVar4 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar4) break;
    ppGVar5 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator*
                        (&local_c);
    (**(code **)(*ppGVar5)->_padding_)();
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++(&local_c);
  }
  return;
}
