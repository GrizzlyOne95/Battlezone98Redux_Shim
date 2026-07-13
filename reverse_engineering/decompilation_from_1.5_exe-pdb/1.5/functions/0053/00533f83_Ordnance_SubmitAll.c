/*
 * Entry: 00533f83
 * Name: Ordnance_SubmitAll
 * Namespace: Global
 * Signature: void Ordnance_SubmitAll(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_SubmitAll(CAMERA *param_1)

{
  bool bVar1;
  Ordnance **ppOVar2;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
  while( true ) {
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
    bVar1 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    local_1c._padding_ = local_c._padding_;
    local_1c._Ptr = local_c._Ptr;
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_c);
    ppOVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                        (&local_1c);
    (**(code **)((*ppOVar2)->_padding_ + 0x18))(param_1);
  }
  return;
}
