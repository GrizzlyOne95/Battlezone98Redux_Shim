/*
 * Entry: 004e2802
 * Name: NetPlayer::DelAllPlayers
 * Namespace: NetPlayer
 * Signature: void DelAllPlayers(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl NetPlayer::DelAllPlayers(void)

{
  NetPlayer *this;
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar4;
  uint uVar5;
  undefined4 *puVar6;
  int aiStack_38 [4];
  const_iterator local_18;
  const_iterator local_10;
  uint local_8;
  
  uVar2 = netPlayerMap._28_4_;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  aiStack_38[3] = 0x4e2825;
  iVar1 = netPlayerMap._28_4_ * -4;
  puVar6 = (undefined4 *)(&stack0xffffffd8 + iVar1);
  aiStack_38[3 - netPlayerMap._28_4_] = (int)&netPlayerMap;
  aiStack_38[2 - netPlayerMap._28_4_] = *(undefined4 *)netPlayerMap._24_4_;
  aiStack_38[1 - netPlayerMap._28_4_] = 0x4e283f;
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_10,(_Node *)aiStack_38[2 - netPlayerMap._28_4_],
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)aiStack_38[3 - netPlayerMap._28_4_]);
  local_18._padding_ = local_10._padding_;
  local_18._Ptr = local_10._Ptr;
  while( true ) {
    aiStack_38[3 - uVar2] = (int)&netPlayerMap;
    aiStack_38[2 - uVar2] = netPlayerMap._24_4_;
    aiStack_38[1 - uVar2] = 0x4e2874;
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_10,(_Node *)aiStack_38[2 - uVar2],
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)aiStack_38[3 - uVar2]);
    aiStack_38[3 - uVar2] = (int)&local_10;
    aiStack_38[2 - uVar2] = 0x4e2880;
    bVar3 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_18,(const_iterator *)aiStack_38[3 - uVar2]);
    if (bVar3) break;
    aiStack_38[3 - uVar2] = 0x4e2855;
    ppVar4 = std::
             _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
             ::const_iterator::operator*(&local_18);
    *puVar6 = ppVar4->second;
    aiStack_38[3 - uVar2] = 0x4e2862;
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::_Inc(&local_18);
    puVar6 = puVar6 + 1;
  }
  uVar5 = 0;
  if (uVar2 != 0) {
    do {
      this = *(NetPlayer **)(&stack0xffffffd8 + uVar5 * 4 + iVar1);
      if (this != (NetPlayer *)0x0) {
        aiStack_38[3 - uVar2] = 0x4e289b;
        ~NetPlayer(this);
        aiStack_38[3 - uVar2] = (int)this;
        aiStack_38[2 - uVar2] = 0x4e28a1;
        operator_delete((void *)aiStack_38[3 - uVar2]);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)uVar2);
  }
  aiStack_38[3 - uVar2] = 0x40;
  aiStack_38[2 - uVar2] = 0;
  aiStack_38[1 - uVar2] = (int)netPlayerByTeam;
  aiStack_38[-uVar2] = 0x4e28b5;
  memset();
  return;
}
