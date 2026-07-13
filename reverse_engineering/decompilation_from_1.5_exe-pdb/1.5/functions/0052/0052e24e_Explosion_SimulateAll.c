/*
 * Entry: 0052e24e
 * Name: Explosion::SimulateAll
 * Namespace: Explosion
 * Signature: void SimulateAll(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Explosion::SimulateAll(float param_1)

{
  Explosion *pEVar1;
  bool bVar2;
  Explosion **ppEVar3;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(explosionList._Myhead)->_Next,&explosionList);
  std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,explosionList._Myhead,&explosionList);
  bVar2 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator==
                    (&local_c,&local_14);
  while (!bVar2) {
    std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator++(&local_c);
    ppEVar3 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator*
                        (&local_1c);
    pEVar1 = *ppEVar3;
    (**(code **)(pEVar1->_padding_ + 0x10))(param_1);
    if ((pEVar1->obj->flags & 0x200) != 0) {
      (**(code **)(pEVar1->_padding_ + 0xc))();
    }
    std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,explosionList._Myhead,&explosionList);
    bVar2 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
  }
  return;
}
