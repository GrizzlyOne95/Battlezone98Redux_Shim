/*
 * Entry: 004e20c6
 * Name: NetPlayer::GotAllSyncs
 * Namespace: NetPlayer
 * Signature: bool GotAllSyncs(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl NetPlayer::GotAllSyncs(ushort param_1)

{
  bool bVar1;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar2;
  const_iterator local_14;
  const_iterator local_c;
  
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
    bVar1 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_c,&local_14);
    if (bVar1) {
      return true;
    }
    ppVar2 = std::
             _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
             ::const_iterator::operator*(&local_c);
    if (((ppVar2->second != (NetPlayer *)0x0) &&
        (ppVar2 = std::
                  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  ::const_iterator::operator*(&local_c), ppVar2->second->playerId != param_1)) &&
       (ppVar2 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_c), ppVar2->second->bGotSyncPacket == false))
    break;
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::_Inc(&local_c);
  }
  return false;
}
