/*
 * Entry: 00494d2e
 * Name: GameFeature_PostLoadAll
 * Namespace: Global
 * Signature: void GameFeature_PostLoadAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameFeature_PostLoadAll(void)

{
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var1;
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var2;
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var3;
  _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var4;
  vector<GameFeature_*,std::allocator<GameFeature_*>_> *pvVar5;
  bool bVar6;
  GameFeature **ppGVar7;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_14;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_c;
  
  AnimSprite::Init();
  pvVar5 = GameFeature::features;
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_14,GameFeature::features->_Mylast,(_Container_base_aux *)GameFeature::features);
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_c,pvVar5->_Myfirst,(_Container_base_aux *)pvVar5);
  _Var1._4_4_ = local_c._Myptr;
  _Var1._0_4_ = local_c._padding_;
  _Var3._4_4_ = local_14._Myptr;
  _Var3._0_4_ = local_14._padding_;
  std::sort<std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>,GFPostLoadPri>
            (_Var1,_Var3,gfPostLoadPri);
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_14,pvVar5->_Myfirst,(_Container_base_aux *)pvVar5);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
    _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
              (&local_14,pvVar5->_Mylast,(_Container_base_aux *)pvVar5);
    bVar6 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar6) break;
    ppGVar7 = std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator*
                        (&local_c);
    (**(code **)((*ppGVar7)->_padding_ + 0xc))();
    std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++(&local_c);
  }
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_14,pvVar5->_Mylast,(_Container_base_aux *)pvVar5);
  std::_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            (&local_c,pvVar5->_Myfirst,(_Container_base_aux *)pvVar5);
  _Var2._4_4_ = local_c._Myptr;
  _Var2._0_4_ = local_c._padding_;
  _Var4._4_4_ = local_14._Myptr;
  _Var4._0_4_ = local_14._padding_;
  std::sort<std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>,GFRenderPri>
            (_Var2,_Var4,gfRenderPri);
  return;
}
