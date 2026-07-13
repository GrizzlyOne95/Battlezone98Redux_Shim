/*
 * Entry: 004e2bd8
 * Name: NetPlayer::DelPlayer
 * Namespace: NetPlayer
 * Signature: void DelPlayer(ushort param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NetPlayer::DelPlayer(ushort param_1,char *param_2)

{
  NetPlayer *this;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar1;
  AiMission *pAVar2;
  ushort *puVar3;
  const_iterator local_c;
  
  puVar3 = &param_1;
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::find((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          *)&netPlayerMap,(ushort *)&local_c);
  ppVar1 = std::
           _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
           ::const_iterator::operator*(&local_c);
  this = ppVar1->second;
  if (this != (NetPlayer *)0x0) {
    pAVar2 = AiMission::GetCurrent();
    if (pAVar2 != (AiMission *)0x0) {
      (**(code **)(pAVar2->_padding_ + 0x28))(this,puVar3);
    }
    ~NetPlayer(this);
    operator_delete(this);
  }
  return;
}
