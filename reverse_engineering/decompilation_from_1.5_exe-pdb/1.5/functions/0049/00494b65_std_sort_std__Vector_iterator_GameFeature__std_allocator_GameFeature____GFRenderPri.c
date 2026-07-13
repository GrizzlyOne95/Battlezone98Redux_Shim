/*
 * Entry: 00494b65
 * Name: std::sort<std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>,GFRenderPri>
 * Namespace: std
 * Signature: void sort<std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>,GFRenderPri>(_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> param_1, _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> param_2, GFRenderPri param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::sort<std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>,GFRenderPri>
          (_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> param_1,
          _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> param_2,GFRenderPri param_3
          )

{
  int iVar1;
  
  iVar1 = _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator-
                    ((_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *)
                     &param_2,(_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
                               *)&param_1);
  _Sort<GameFeature_*_*,int,GFRenderPri>
            ((GameFeature **)param_1._4_4_,(GameFeature **)param_2._4_4_,iVar1,param_3);
  return;
}
