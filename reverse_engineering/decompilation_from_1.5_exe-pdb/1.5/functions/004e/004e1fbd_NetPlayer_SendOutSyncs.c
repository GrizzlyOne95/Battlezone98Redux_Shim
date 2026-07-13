/*
 * Entry: 004e1fbd
 * Name: NetPlayer::SendOutSyncs
 * Namespace: NetPlayer
 * Signature: bool SendOutSyncs(dp_s * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl NetPlayer::SendOutSyncs(dp_s *param_1,ushort param_2)

{
  bool bVar1;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar2;
  const_iterator local_28;
  const_iterator local_20;
  undefined1 local_15;
  undefined2 local_14 [6];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14[0] = 0x5353;
  local_15 = 1;
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_28,*(_Node **)netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&netPlayerMap);
  local_20._padding_ = local_28._padding_;
  local_20._Ptr = local_28._Ptr;
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_28,(_Node *)netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&netPlayerMap);
  bVar1 = std::
          _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==(&local_20,&local_28);
  while (!bVar1) {
    ppVar2 = std::
             _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
             ::const_iterator::operator*(&local_20);
    if (((ppVar2->second != (NetPlayer *)0x0) &&
        (ppVar2 = std::
                  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  ::const_iterator::operator*(&local_20), ppVar2->second->playerId != param_2)) &&
       (ppVar2 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_20), ppVar2->second->bGotSyncPacketAck == false)
       ) {
      ppVar2 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*(&local_20);
      Net::Send(param_1,param_2,ppVar2->second->playerId,0,local_14,4);
      local_15 = 0;
    }
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::_Inc(&local_20);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_28,(_Node *)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    bVar1 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_20,&local_28);
  }
  return (bool)local_15;
}
