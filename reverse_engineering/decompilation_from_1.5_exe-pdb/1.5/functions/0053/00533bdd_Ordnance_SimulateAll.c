/*
 * Entry: 00533bdd
 * Name: Ordnance_SimulateAll
 * Namespace: Global
 * Signature: void Ordnance_SimulateAll(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_SimulateAll(float param_1)

{
  Ordnance *pOVar1;
  float fVar2;
  bool bVar3;
  Ordnance **ppOVar4;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
  bVar3 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                    (&local_c,&local_14);
  while (!bVar3) {
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_c);
    ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                        (&local_1c);
    pOVar1 = *ppOVar4;
    fVar2 = pOVar1->dt + param_1;
    pOVar1->dt = fVar2;
    if (0.0 < fVar2) {
      (**(code **)(pOVar1->_padding_ + 0x10))(fVar2);
      pOVar1->dt = 0.0;
    }
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
    bVar3 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
  }
  return;
}
