/*
 * Entry: 004e2303
 * Name: NetPlayer_GetNextPlayer
 * Namespace: Global
 * Signature: ushort NetPlayer_GetNextPlayer(char * * param_1, ulong * param_2, ulong * param_3, ulong * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl NetPlayer_GetNextPlayer(char **param_1,ulong *param_2,ulong *param_3,ulong *param_4)

{
  bool bVar1;
  ushort uVar2;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar3;
  ulong uVar4;
  const_iterator local_c;
  
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::_Inc((const_iterator *)&NetPlayer::iter);
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_c,(_Node *)NetPlayer::netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&NetPlayer::netPlayerMap);
  bVar1 = std::
          _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==((const_iterator *)&NetPlayer::iter,&local_c);
  if (bVar1) {
    uVar2 = 0xfa01;
  }
  else {
    if (param_1 != (char **)0x0) {
      ppVar3 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*((const_iterator *)&NetPlayer::iter);
      *param_1 = ppVar3->second->playerName;
    }
    if (param_2 != (ulong *)0x0) {
      ppVar3 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*((const_iterator *)&NetPlayer::iter);
      *param_2 = ppVar3->second->deaths;
    }
    if (param_3 != (ulong *)0x0) {
      ppVar3 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*((const_iterator *)&NetPlayer::iter);
      *param_3 = ppVar3->second->kills;
    }
    if (param_4 != (ulong *)0x0) {
      ppVar3 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*((const_iterator *)&NetPlayer::iter);
      uVar4 = NetPlayer::GetAveragePingTime(ppVar3->second);
      *param_4 = uVar4;
    }
    ppVar3 = std::
             _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
             ::const_iterator::operator*((const_iterator *)&NetPlayer::iter);
    uVar2 = ppVar3->first;
  }
  return uVar2;
}
