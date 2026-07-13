/*
 * Entry: 004942e1
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Ufill
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: GameFeature * * _Ufill(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this, GameFeature * * param_1, uint param_2, GameFeature * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Ufill
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this,GameFeature **param_1,
          uint param_2,GameFeature **param_3)

{
  stdext::unchecked_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
