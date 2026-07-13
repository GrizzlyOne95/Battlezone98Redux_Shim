/*
 * Entry: 00533e96
 * Name: Ordnance_Sent
 * Namespace: Global
 * Signature: void Ordnance_Sent(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_Sent(int param_1)

{
  bool bVar1;
  Ordnance **ppOVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
  bVar1 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                    (&local_c,&local_14);
  if (param_1 == 1) {
    while (bVar1 == false) {
      ppOVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_c);
      if ((*ppOVar2)->bSend == 2) {
        ppOVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                            (&local_c);
        (*ppOVar2)->bSend = 0;
      }
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_c);
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
      bVar1 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
    }
  }
  else {
    while (bVar1 == false) {
      ppOVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_c);
      if ((*ppOVar2)->bSend == 2) {
        ppOVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                            (&local_c);
        (*ppOVar2)->bSend = 1;
      }
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_c);
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
      bVar1 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
    }
  }
  return;
}
