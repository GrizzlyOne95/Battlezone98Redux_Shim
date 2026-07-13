/*
 * Entry: 004e28ca
 * Name: NetPlayer::Find
 * Namespace: NetPlayer
 * Signature: NetPlayer * Find(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NetPlayer * __cdecl NetPlayer::Find(ushort param_1)

{
  bool bVar1;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar2;
  const_iterator local_14;
  const_iterator local_c;
  
  if (param_1 != 0xfa01) {
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::find((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            *)&netPlayerMap,(ushort *)&local_c);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_14,(_Node *)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    bVar1 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_c,&local_14);
    if (((!bVar1) &&
        (ppVar2 = std::
                  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  ::const_iterator::operator*(&local_c), ppVar2->second != (NetPlayer *)0x0)) &&
       (ppVar2 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_c), ppVar2->second->playerId == param_1)) {
      ppVar2 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*(&local_c);
      return ppVar2->second;
    }
  }
  return (NetPlayer *)0x0;
}
