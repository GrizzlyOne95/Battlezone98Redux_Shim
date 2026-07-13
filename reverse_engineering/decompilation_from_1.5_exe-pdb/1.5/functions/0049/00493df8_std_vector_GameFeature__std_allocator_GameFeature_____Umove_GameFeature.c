/*
 * Entry: 00493df8
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Umove<GameFeature_*_*>
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: GameFeature * * _Umove<GameFeature_*_*>(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this, GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Umove<GameFeature_*_*>
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this,GameFeature **param_1,
          GameFeature **param_2,GameFeature **param_3)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = stdext::
            unchecked_uninitialized_copy<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
                      (param_1,param_2,param_3,(allocator<GameFeature_*> *)&this->_padding_);
  return ppGVar1;
}
