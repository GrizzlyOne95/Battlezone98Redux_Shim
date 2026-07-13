/*
 * Entry: 0052e2ec
 * Name: Explosion::SubmitAll
 * Namespace: Explosion
 * Signature: void SubmitAll(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Explosion::SubmitAll(CAMERA *param_1)

{
  bool bVar1;
  Explosion **ppEVar2;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(explosionList._Myhead)->_Next,&explosionList);
  while( true ) {
    std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,explosionList._Myhead,&explosionList);
    bVar1 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    local_1c._padding_ = local_c._padding_;
    local_1c._Ptr = local_c._Ptr;
    std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator++(&local_c);
    ppEVar2 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator*
                        (&local_1c);
    (**(code **)((*ppEVar2)->_padding_ + 0x14))(param_1);
  }
  return;
}
