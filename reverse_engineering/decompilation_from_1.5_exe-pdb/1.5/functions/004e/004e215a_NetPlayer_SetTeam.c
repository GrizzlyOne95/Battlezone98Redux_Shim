/*
 * Entry: 004e215a
 * Name: NetPlayer::SetTeam
 * Namespace: NetPlayer
 * Signature: void SetTeam(NetPlayer * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall NetPlayer::SetTeam(NetPlayer *this,int param_1)

{
  bool bVar1;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar2;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar3;
  const_iterator local_14;
  const_iterator local_c;
  
  if ((uint)this->bTeamNumber != param_1) {
    this->bTeamNumber = (uchar)param_1;
    memset(netPlayerByTeam,0,0x40);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_c,*(_Node **)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_14,(_Node *)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    bVar1 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_c,&local_14);
    while (!bVar1) {
      ppVar2 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*(&local_c);
      if (ppVar2->second->bTeamNumber != '\0') {
        ppVar2 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_c);
        ppVar3 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_c);
        netPlayerByTeam[ppVar3->second->bTeamNumber] = ppVar2->second;
      }
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::_Inc(&local_c);
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_14,(_Node *)netPlayerMap._24_4_,
                 (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  *)&netPlayerMap);
      bVar1 = std::
              _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              ::const_iterator::operator==(&local_c,&local_14);
    }
  }
  return;
}
