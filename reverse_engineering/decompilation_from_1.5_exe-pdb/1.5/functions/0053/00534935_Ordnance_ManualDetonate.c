/*
 * Entry: 00534935
 * Name: Ordnance_ManualDetonate
 * Namespace: Global
 * Signature: void Ordnance_ManualDetonate(char * param_1, uint param_2, ushort param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_ManualDetonate(char *param_1,uint param_2,ushort param_3)

{
  char *pcVar1;
  bool bVar2;
  pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *ppVar3;
  const_iterator local_14;
  const_iterator local_c;
  
  pcVar1 = param_1 + param_2;
  while (param_1 < pcVar1) {
    param_1 = param_1 + 2;
    std::
    _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
    ::find((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
            *)&netOrdnanceMap,(pair<unsigned_short,unsigned_short> *)&local_c);
    std::
    _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_14,(_Node *)netOrdnanceMap._24_4_,
               (_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                *)&netOrdnanceMap);
    bVar2 = std::
            _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
            ::const_iterator::operator==(&local_c,&local_14);
    if (!bVar2) {
      ppVar3 = std::
               _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
               ::const_iterator::operator*(&local_c);
      ppVar3->second->lifeTimer = 0.0;
    }
  }
  return;
}
