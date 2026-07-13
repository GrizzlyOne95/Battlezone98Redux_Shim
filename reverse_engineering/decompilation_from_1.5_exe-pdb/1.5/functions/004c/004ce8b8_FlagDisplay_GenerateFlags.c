/*
 * Entry: 004ce8b8
 * Name: FlagDisplay::GenerateFlags
 * Namespace: FlagDisplay
 * Signature: void GenerateFlags(FlagDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagDisplay::GenerateFlags(FlagDisplay *this)

{
  byte *pbVar1;
  TEXTURE *pTVar2;
  float fVar3;
  bool bVar4;
  byte bVar5;
  ushort uVar6;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar7;
  int iVar8;
  byte bVar9;
  int *piVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  const_iterator local_38;
  const_iterator local_30;
  NetPlayer *local_28;
  int local_24;
  int local_20;
  int local_1c;
  long local_18;
  byte *local_14;
  int local_10;
  NetPlayer *local_c;
  byte *local_8;
  
  iVar11 = this->flagIndex;
  local_10 = iVar11;
  uVar6 = Net_GetMyPlayerID();
  local_28 = NetPlayer::Find(uVar6);
  if (local_28 != (NetPlayer *)0x0) {
    Team::GetTeam((uint)local_28->bTeamNumber);
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_38,*(_Node **)NetPlayer::netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&NetPlayer::netPlayerMap);
    local_30._padding_ = local_38._padding_;
    local_30._Ptr = local_38._Ptr;
    std::
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_38,(_Node *)NetPlayer::netPlayerMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                *)&NetPlayer::netPlayerMap);
    bVar4 = std::
            _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==(&local_30,&local_38);
    if (!bVar4) {
      piVar10 = &spriteTable[iVar11].v;
      do {
        ppVar7 = std::
                 _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 ::const_iterator::operator*(&local_30);
        local_c = ppVar7->second;
        local_20 = *piVar10;
        pTVar2 = (TEXTURE *)piVar10[5];
        local_1c = ((SPRITE *)(piVar10 + -1))->u;
        local_24 = piVar10[1] + local_1c;
        iVar11 = piVar10[2] + local_20;
        local_8 = (byte *)((int)&pTVar2[1].width + (iVar11 + -1) * (int)pTVar2->width + local_1c);
        local_14 = NetPlayer::GetFlag(local_c);
        if (local_14 != (byte *)0x0) {
          if (local_c == local_28) {
            fVar3 = 0.0;
            fVar13 = 0.0;
            fVar12 = 1.0;
          }
          else {
            uVar6 = NetPlayer::GetPlayerId(local_c);
            iVar8 = NetPlayer_IsPlayerAlly(uVar6);
            if (iVar8 == 0) {
              fVar13 = 0.0;
              fVar12 = 0.0;
              fVar3 = 1.0;
            }
            else {
              fVar13 = 1.0;
              fVar12 = 0.5;
              fVar3 = 0.0;
            }
          }
          local_18 = Get_Closest_RGB_Entry(fVar3,fVar12,fVar13);
          iVar8 = local_10 + 1;
          piVar10 = piVar10 + 8;
          local_c->flagIndex = local_10;
          local_10 = iVar8;
          if (local_20 < iVar11) {
            local_c = (NetPlayer *)(iVar11 - local_20);
            do {
              if (local_1c < local_24) {
                iVar11 = ((local_24 - local_1c) - 1U >> 3) + 1;
                do {
                  bVar9 = *local_14;
                  local_14 = local_14 + 1;
                  local_20 = 8;
                  do {
                    bVar5 = bVar9 & 0x80;
                    pbVar1 = local_8 + 1;
                    bVar9 = bVar9 * '\x02';
                    local_20 = local_20 + -1;
                    *local_8 = -(bVar5 != 0) & (byte)local_18;
                    local_8 = pbVar1;
                  } while (local_20 != 0);
                  iVar11 = iVar11 + -1;
                  local_20 = 0;
                } while (iVar11 != 0);
              }
              local_8 = local_8 + ((local_1c - pTVar2->width) - local_24);
              local_c = (NetPlayer *)((int)&local_c[-1].dwPingReplies + 3);
            } while (local_c != (NetPlayer *)0x0);
          }
        }
        std::
        _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
        ::const_iterator::_Inc(&local_30);
        std::
        _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
        ::const_iterator::const_iterator
                  (&local_38,(_Node *)NetPlayer::netPlayerMap._24_4_,
                   (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                    *)&NetPlayer::netPlayerMap);
        bVar4 = std::
                _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                ::const_iterator::operator==(&local_30,&local_38);
      } while (!bVar4);
    }
    if (useD3D != 0) {
      D3D_Video_Memory_Is_Dirty = 1;
    }
  }
  return;
}
