/*
 * Entry: 004998af
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Umove<GameObjectClass_*_*>
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: GameObjectClass * * _Umove<GameObjectClass_*_*>(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this, GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Umove<GameObjectClass_*_*>
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this,
          GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3)

{
  GameObjectClass **ppGVar1;
  
  ppGVar1 = stdext::
            unchecked_uninitialized_copy<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
                      (param_1,param_2,param_3,(allocator<GameObjectClass_*> *)&this->_padding_);
  return ppGVar1;
}
