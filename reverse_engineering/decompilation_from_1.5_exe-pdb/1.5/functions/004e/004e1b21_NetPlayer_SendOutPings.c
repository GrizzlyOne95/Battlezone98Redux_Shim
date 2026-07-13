/*
 * Entry: 004e1b21
 * Name: NetPlayer::SendOutPings
 * Namespace: NetPlayer
 * Signature: void SendOutPings(dp_s * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl NetPlayer::SendOutPings(dp_s *param_1,ushort param_2)

{
  NetPlayer *pNVar1;
  undefined4 uVar2;
  bool bVar3;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar4;
  ulong uVar5;
  int iVar6;
  const_iterator local_14c;
  const_iterator local_144;
  const_iterator local_13c;
  undefined2 local_134;
  ulong local_132;
  ulong local_12e;
  byte local_12a;
  ushort auStack_126 [2];
  ulong auStack_122 [6];
  char local_108 [56];
  undefined1 local_d0 [200];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_d0;
  local_144._Ptr = (_Node *)Get_Time_Long();
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_14c,*(_Node **)netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&netPlayerMap);
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_13c,(_Node *)netPlayerMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)&netPlayerMap);
  bVar3 = std::
          _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==(&local_14c,&local_13c);
  while (!bVar3) {
    ppVar4 = std::
             _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
             ::const_iterator::operator*(&local_14c);
    pNVar1 = ppVar4->second;
    if ((pNVar1 != (NetPlayer *)0x0) && (param_2 != pNVar1->playerId)) {
      if (((pNVar1->dwJoinTime == 0) ||
          (local_144._Ptr <= (_Node *)(pNVar1->dwJoinTime + Net::dwAutoKickStart))) ||
         ((uVar5 = GetAveragePingTime(pNVar1), uVar5 <= Net::dwAutoKickPing &&
          (uVar5 = GetAverageLoss(pNVar1), uVar5 <= Net::dwAutoKickLoss)))) {
        if (pNVar1->dwLaggingTime != 0) {
          builtin_strncpy(local_108,"%s stopped lagging",0x13);
          memset(local_108 + 0x13,0,0xed);
          read_text_label("multi_message","stop_lagging",local_108);
          DisplayMessage(local_108);
          pNVar1->dwLaggingTime = 0;
        }
      }
      else {
        uVar2 = local_108._12_4_;
        if (pNVar1->dwLaggingTime == 0) {
          builtin_strncpy(local_108,"%s is lagging",0xe);
          local_108._14_2_ = SUB42(uVar2,2);
          memset(local_108 + 0xe,0,0xf2);
          read_text_label("multi_message","start_lagging",local_108);
          DisplayMessage(local_108);
          pNVar1->dwLaggingTime = (ulong)local_144._Ptr;
        }
        iVar6 = Net_IsHosting();
        if ((iVar6 != 0) &&
           ((_Node *)(pNVar1->dwLaggingTime + Net::dwAutoKickTime) < local_144._Ptr)) {
          builtin_strncpy(local_108,"Auto-kicking %s",0x10);
          memset(local_108 + 0x10,0,0xf0);
          read_text_label("multi_message","autokick",local_108);
          DisplayMessage(local_108);
          Net_AutoKickPlayer(pNVar1->playerId);
          pNVar1->dwLaggingTime = 0xffffffff;
        }
      }
    }
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::_Inc(&local_14c);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_13c,(_Node *)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    bVar3 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_14c,&local_13c);
  }
  if (Net::bBroadcastOptimize == false) {
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_13c,*(_Node **)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    local_144._padding_ = local_13c._padding_;
    local_144._Ptr = local_13c._Ptr;
    while( true ) {
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_13c,(_Node *)netPlayerMap._24_4_,
                 (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  *)&netPlayerMap);
      bVar3 = std::
              _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              ::const_iterator::operator==(&local_144,&local_13c);
      if (bVar3) break;
      ppVar4 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*(&local_144);
      if ((ppVar4->second != (NetPlayer *)0x0) &&
         (ppVar4 = std::
                   _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                   ::const_iterator::operator*(&local_144), param_2 != ppVar4->second->playerId)) {
        ppVar4 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_144);
        SendPing(ppVar4->second,param_1,param_2);
      }
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::_Inc(&local_144);
    }
  }
  else {
    local_134 = 0x4147;
    local_12a = 0;
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_14c,*(_Node **)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_13c,(_Node *)netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&netPlayerMap);
    bVar3 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_14c,&local_13c);
    while (bVar3 == false) {
      ppVar4 = std::
               _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
               ::const_iterator::operator*(&local_14c);
      pNVar1 = ppVar4->second;
      if ((pNVar1 != (NetPlayer *)0x0) && (param_2 != pNVar1->playerId)) {
        auStack_126[(uint)local_12a * 6] = pNVar1->playerId;
        if (pNVar1->bClockInitialized == false) {
          auStack_122[(uint)local_12a * 3] = 0;
          auStack_122[(uint)local_12a * 3 + 1] = 0;
        }
        else {
          auStack_122[(uint)local_12a * 3] = pNVar1->offset;
          if (pNVar1->offset == 0) {
            auStack_122[(uint)local_12a * 3 + 1] = 1;
          }
          else {
            auStack_122[(uint)local_12a * 3 + 1] = pNVar1->BAddOffset;
          }
        }
        local_12a = local_12a + 1;
        pNVar1->dwPingReplies = pNVar1->dwPingReplies << 1;
      }
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::_Inc(&local_14c);
      std::
      _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_13c,(_Node *)netPlayerMap._24_4_,
                 (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                  *)&netPlayerMap);
      bVar3 = std::
              _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              ::const_iterator::operator==(&local_14c,&local_13c);
    }
    local_12e = GetStartTime();
    local_132 = GetCurrentNetworkTime();
    Net::Send(param_1,param_2,0,0,&local_134,(uint)local_12a * 0xc + 0xe);
  }
  return;
}
