/*
 * Entry: 00499871
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::back
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: GameObjectClass * * back(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::back
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  GameObjectClass **ppGVar1;
  _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> local_c;
  
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator-
                    ((_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *)
                     &local_c,(int)local_14);
  ppGVar1 = _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator*
                      (_Var2._0_4_);
  return ppGVar1;
}
