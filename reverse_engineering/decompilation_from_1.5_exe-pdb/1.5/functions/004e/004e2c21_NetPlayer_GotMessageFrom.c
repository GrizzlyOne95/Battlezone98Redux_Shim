/*
 * Entry: 004e2c21
 * Name: NetPlayer::GotMessageFrom
 * Namespace: NetPlayer
 * Signature: void GotMessageFrom(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl NetPlayer::GotMessageFrom(ushort param_1)

{
  SpawnPoint **ppSVar1;
  NetPlayer *this;
  bool bVar2;
  int iVar3;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar4;
  ulong uVar5;
  AiMission *pAVar6;
  DWORD DVar7;
  iterator iVar8;
  undefined2 in_stack_00000006;
  ushort *puVar9;
  const_iterator local_4c;
  const_iterator local_44;
  int local_3c;
  char local_38 [28];
  char local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_3c = 0x10;
  iVar3 = dpGetPlayerBlob(Net::dp,_param_1,local_1c,&local_3c);
  if (iVar3 != 0) {
    local_3c = 0;
  }
  puVar9 = &param_1;
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::find((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          *)&netPlayerMap,(ushort *)&local_44);
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_4c,(_Node *)netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&netPlayerMap);
  bVar2 = std::
          _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==(&local_4c,&local_44);
  if (bVar2) {
    iVar3 = dpGetPlayerName(Net::dp,_param_1,local_38,0x19,puVar9);
    if (iVar3 != 0) {
      return;
    }
    if (local_3c == 0) {
      return;
    }
    AddPlayer((ushort)_param_1,local_38,(int)local_1c[0] & 0xf);
    iVar8 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::find((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                    *)&netPlayerMap,(ushort *)&local_4c);
    local_44._padding_ = *iVar8._0_4_;
    local_44._Ptr = (_Node *)iVar8._0_4_[1];
  }
  ppVar4 = std::
           _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
           ::const_iterator::operator*(&local_44);
  this = ppVar4->second;
  if (this != (NetPlayer *)0x0) {
    if ((local_3c != 0) && ((uint)this->bTeamNumber != ((int)local_1c[0] & 0xfU))) {
      SetTeam(this,(int)local_1c[0] & 0xfU);
    }
    this->waitingForSpawnPoint = false;
    if (this->dwJoinTime == 0) {
      uVar5 = Get_Time_Long();
      this->dwJoinTime = uVar5;
      pAVar6 = AiMission::GetCurrent();
      if (pAVar6 != (AiMission *)0x0) {
        (**(code **)(pAVar6->_padding_ + 0x24))(this);
      }
    }
    ppSVar1 = &this->SpawnPointer;
    if ((*ppSVar1 != (SpawnPoint *)0x0) && (iVar3 = Net_IsDeathMatch(), iVar3 != 0)) {
      SpawnPoint::Unlock(*ppSVar1,this);
      *ppSVar1 = (SpawnPoint *)0x0;
    }
    DVar7 = Get_TimeNow();
    uVar5 = this->dwNewestRxTime;
    if ((uVar5 != 0) && (iVar3 = DVar7 - uVar5, Net::MaxPositionPacketInterval < iVar3)) {
      Net::MaxPositionPacketInterval = iVar3;
    }
    this->dwNewestRxTime = DVar7;
  }
  return;
}
