/*
 * Entry: 004e2b68
 * Name: NetPlayer::AddPlayer
 * Namespace: NetPlayer
 * Signature: void AddPlayer(ushort param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NetPlayer::AddPlayer(ushort param_1,char *param_2,int param_3)

{
  bool bVar1;
  NetPlayer *pNVar2;
  AiMission *pAVar3;
  iterator iVar4;
  ushort local_14 [4];
  const_iterator local_c;
  
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_c,(_Node *)netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&netPlayerMap);
  iVar4 = std::
          _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::find((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  *)&netPlayerMap,local_14);
  bVar1 = std::
          _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==(&local_c,iVar4._0_4_);
  if (bVar1) {
    pNVar2 = operator_new(0x278);
    if (pNVar2 == (NetPlayer *)0x0) {
      pNVar2 = (NetPlayer *)0x0;
    }
    else {
      pNVar2 = NetPlayer(pNVar2,param_1,param_2,param_3);
    }
    pAVar3 = AiMission::GetCurrent();
    if (pAVar3 != (AiMission *)0x0) {
      (**(code **)(pAVar3->_padding_ + 0x20))(pNVar2);
    }
  }
  return;
}
