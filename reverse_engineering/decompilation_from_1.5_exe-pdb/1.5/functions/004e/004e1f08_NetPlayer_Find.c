/*
 * Entry: 004e1f08
 * Name: NetPlayer::Find
 * Namespace: NetPlayer
 * Signature: NetPlayer * Find(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NetPlayer * __cdecl NetPlayer::Find(char *param_1)

{
  byte bVar1;
  bool bVar2;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar3;
  char *pcVar4;
  int iVar5;
  byte *pbVar6;
  const_iterator local_14;
  const_iterator local_c;
  
  if (param_1 != (char *)0x0) {
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_14,*(_Node **)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    local_c._padding_ = local_14._padding_;
    local_c._Ptr = local_14._Ptr;
    while( true ) {
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_14,(_Node *)netPlayerMap._24_4_,
                 (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  *)&netPlayerMap);
      bVar2 = std::
              _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              ::const_iterator::operator==(&local_c,&local_14);
      if (bVar2) break;
      ppVar3 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*(&local_c);
      if (ppVar3->second != (NetPlayer *)0x0) {
        ppVar3 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_c);
        pcVar4 = ppVar3->second->playerName;
        pbVar6 = (byte *)param_1;
        do {
          bVar1 = *pcVar4;
          bVar2 = bVar1 < *pbVar6;
          if (bVar1 != *pbVar6) {
LAB_004e1f7b:
            iVar5 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
            goto LAB_004e1f80;
          }
          if (bVar1 == 0) break;
          bVar1 = pcVar4[1];
          bVar2 = bVar1 < pbVar6[1];
          if (bVar1 != pbVar6[1]) goto LAB_004e1f7b;
          pcVar4 = pcVar4 + 2;
          pbVar6 = pbVar6 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_004e1f80:
        if (iVar5 == 0) {
          ppVar3 = std::
                   _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                   ::const_iterator::operator*(&local_c);
          return ppVar3->second;
        }
      }
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::_Inc(&local_c);
    }
  }
  return (NetPlayer *)0x0;
}
