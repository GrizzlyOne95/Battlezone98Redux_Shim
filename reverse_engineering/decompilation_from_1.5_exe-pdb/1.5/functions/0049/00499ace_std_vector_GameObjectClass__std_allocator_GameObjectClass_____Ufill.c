/*
 * Entry: 00499ace
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Ufill
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: GameObjectClass * * _Ufill(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this, GameObjectClass * * param_1, uint param_2, GameObjectClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Ufill
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this,
          GameObjectClass **param_1,uint param_2,GameObjectClass **param_3)

{
  stdext::unchecked_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*>
            (param_1,param_2,param_3);
  return param_1 + param_2;
}
