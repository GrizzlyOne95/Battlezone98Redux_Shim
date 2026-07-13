/*
 * Entry: 00522f26
 * Name: Set_Terrain_Texture_Info
 * Namespace: Global
 * Signature: void Set_Terrain_Texture_Info(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Set_Terrain_Texture_Info(void)

{
  undefined2 uVar1;
  char cVar2;
  ushort uVar3;
  short *psVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  char *pcVar9;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar10;
  long lVar11;
  RGB *pRVar12;
  int iVar13;
  char *pcVar14;
  TEXTURE *pTVar15;
  int iVar16;
  uint extraout_EAX_03;
  uint extraout_EAX_04;
  uint extraout_EAX_05;
  uint uVar17;
  float *pfVar18;
  uchar uVar19;
  int iVar20;
  float *pfVar21;
  uchar *puVar22;
  uint uVar23;
  uint uVar24;
  char *pcVar25;
  uchar (*paauVar26) [4] [2];
  uint *puVar27;
  RGB *local_4c;
  undefined4 *local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  undefined4 local_2c;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar14 = secStr;
  do {
    pcVar9 = pcVar14;
    pcVar14 = pcVar9 + 1;
  } while (*pcVar9 != '\0');
  SelectTerrainView(0);
  Init_AnimatedScrounge();
  uVar8 = secStr._8_4_;
  builtin_strncpy(secStr,"NormalView",0xb);
  secStr[0xb] = SUB41(uVar8,3);
  mipDistance[0] = GetPrivateProfileIntA(secStr,"MIP0",mipDistance[0],&cfgFileName);
  mipDistance[1] = GetPrivateProfileIntA(secStr,"MIP1",mipDistance[1],&cfgFileName);
  mipDistance[2] = GetPrivateProfileIntA(secStr,"MIP2",mipDistance[2],&cfgFileName);
  mipDistance[3] = GetPrivateProfileIntA(secStr,"MIP3",mipDistance[3],&cfgFileName);
  builtin_strncpy(secStr,"TextureType0",0xd);
  if (TerrainFirstMIP == 0) {
    D3IniFlags = D3IniFlags & 0xfffffffb;
  }
  else {
    D3IniFlags = D3IniFlags | 4;
    mipDistance[0] = 1000;
  }
  _ftol2_sse();
  mipDistance2[0] = extraout_EAX;
  _ftol2_sse();
  mipDistance2[1] = extraout_EAX_00;
  _ftol2_sse();
  mipDistance2[2] = extraout_EAX_01;
  _ftol2_sse();
  uVar24 = 0;
  mipDistance2[3] = extraout_EAX_02;
  memset(TileFileName,0,0x1000);
  memset(TileIndex,0,0x200);
  memset(TileTexturePtr,0,0x400);
  local_2c = 0;
  do {
    lVar11 = TerrainView.Flat_Color;
    pcVar9[-1] = (char)local_2c + '0';
    iVar10 = GetINIInt(secStr,"FlatColor",lVar11,missionName);
    iVar13 = local_2c + 1;
    MaterialColors[local_2c] = iVar10;
    local_2c = iVar13;
  } while (iVar13 < 8);
  TileFileCount = 0;
  do {
    lVar11 = Get_Closest_RGB_Entry(0.0,(float)(uVar24 & 0x1f) * 0.024193548 + 0.25,0.0);
    WireFrameColors[uVar24] = lVar11;
    uVar24 = uVar24 + 1;
  } while ((int)uVar24 < 0x100);
  local_2c = 0;
  do {
    fVar5 = (float)(int)local_2c * 0.022580644 + 0.1;
    lVar11 = Get_Closest_RGB_Entry(fVar5,fVar5,fVar5);
    GreyColors[local_2c] = lVar11;
    lVar11 = Get_Closest_RGB_Entry(fVar5,0.0,0.0);
    iVar13 = local_2c + 1;
    LavaColors[local_2c] = lVar11;
    local_2c = iVar13;
  } while (iVar13 < 0x20);
  TerrainLastQuality = (int)(UserProfilePtr->graphicDetail).terrain;
  uVar24 = 0;
  pRVar12 = TileColors;
  do {
    iVar13 = MaterialColors[(int)((uVar24 & 0x3c00) << 2) >> 0xc];
    puVar22 = &pRVar12->b;
    uVar1 = *(undefined2 *)(&Default_Palette + iVar13 * 3);
    pRVar12->r = (char)uVar1;
    pRVar12->g = (char)((ushort)uVar1 >> 8);
    pRVar12 = pRVar12 + 1;
    uVar24 = uVar24 + 1;
    *puVar22 = (&DAT_0062c432)[iVar13 * 3];
    iVar13 = TileFileCount;
  } while ((int)pRVar12 < 0xcaf4a0);
  local_2c = (uint)CONCAT12(DAT_0062c567,DAT_0062c565);
  uVar24 = local_2c & 0xff;
  local_2c._1_1_ = (byte)((ushort)DAT_0062c565 >> 8);
  colorTable[10] = ((uVar24 | 0xffffff00) << 8 | (uint)local_2c._1_1_) << 8 | (uint)DAT_0062c567;
  if (TerrainTextured != 0) {
    TileFileCount = TileFileCount + 1;
    TileTexturePtr[iVar13] = &badTexture;
    local_2c = 0;
    local_44 = 0;
    do {
      local_30 = 0;
      pcVar9[-1] = (char)local_2c + '0';
      do {
        local_38 = 0;
        uVar24 = -(uint)(local_30 != 0) & 7;
        do {
          local_3c = 0;
          if (uVar24 != 0xffffffff) {
            do {
              iVar13 = local_38 + 0x41;
              if (local_30 == 0) {
                sprintf(local_28,"%s%c0",borderName[0],iVar13);
              }
              else {
                sprintf(local_28,"%s%d_%c0",borderName[local_30],local_3c);
              }
              GetINIString(secStr,local_28,"",TileFileName[TileFileCount],0x10,missionName);
              pcVar14 = TileFileName[TileFileCount];
              do {
                cVar2 = *pcVar14;
                pcVar14 = pcVar14 + 1;
              } while (cVar2 != '\0');
              if (pcVar14 != TileFileName[TileFileCount] + 1) {
                uVar19 = (uchar)TileFileCount;
                if (local_30 == 0) {
                  if (local_38 < 4) {
                    puVar22 = TileIndex[0][0][local_44 + local_38] + 1;
                    iVar10 = 4 - local_38;
                    do {
                      (*(uchar (*) [2])(puVar22 + -1))[0] = uVar19;
                      *puVar22 = uVar19;
                      puVar22 = puVar22 + 2;
                      iVar10 = iVar10 + -1;
                    } while (iVar10 != 0);
                  }
                }
                else if (local_38 < 4) {
                  puVar22 = TileIndex[local_2c][local_3c][local_38] + (local_30 >> 1);
                  iVar10 = 4 - local_38;
                  do {
                    *puVar22 = uVar19;
                    puVar22 = puVar22 + 2;
                    iVar10 = iVar10 + -1;
                  } while (iVar10 != 0);
                }
                local_48 = (undefined4 *)0x0;
                do {
                  if (local_30 == 0) {
                    sprintf(local_28,"%s%c%d",borderName[0],iVar13,TerrainFirstMIP + (int)local_48);
                  }
                  else {
                    sprintf(local_28,"%s%d_%c%d",borderName[local_30],local_3c,iVar13,
                            TerrainFirstMIP + (int)local_48);
                  }
                  GetINIString(secStr,local_28,"",TileFileName[TileFileCount],0x10,missionName);
                  iVar10 = TileFileCount;
                  pcVar14 = TileFileName[TileFileCount];
                  pcVar25 = pcVar14;
                  do {
                    cVar2 = *pcVar25;
                    pcVar25 = pcVar25 + 1;
                  } while (cVar2 != '\0');
                  if (pcVar25 == TileFileName[TileFileCount] + 1) {
                    paauVar26 = TileIndex[7] + TileFileCount * 2 + 6;
                    TileTexturePtr[TileFileCount] = (TEXTURE *)MaterialColors[TileFileCount + 0xf];
                    iVar20 = (int)pcVar14 - (int)paauVar26;
                    do {
                      uVar19 = (*paauVar26)[0][0];
                      *(uchar *)((int)paauVar26 + iVar20) = uVar19;
                      paauVar26 = (uchar (*) [4] [2])((*paauVar26)[0] + 1);
                    } while (uVar19 != '\0');
                  }
                  else {
                    pTVar15 = UseItem(pcVar14);
                    iVar10 = TileFileCount;
                    TileTexturePtr[TileFileCount] = pTVar15;
                    if (pTVar15 == (TEXTURE *)0x0) {
                      DEBUG_systemWarning("Terrain Texture %s not found\nTexture will be off");
                      Close_Terrain_Texture_Info();
                      return;
                    }
                  }
                  if (iVar10 < 0xff) {
                    TileFileCount = iVar10 + 1;
                  }
                  local_48 = (undefined4 *)((int)local_48 + 1);
                } while ((int)local_48 < 4);
              }
              local_3c = local_3c + 1;
            } while (local_3c < (int)(uVar24 + 1));
          }
          local_38 = local_38 + 1;
        } while (local_38 < 4);
        local_30 = local_30 + 1;
      } while (local_30 < 3);
      local_44 = local_44 + 0x24;
      local_2c = local_2c + 1;
    } while (local_44 < 0x120);
    local_4c = TileColors;
    local_48 = &DAT_00caf4ec;
    do {
      psVar4 = (short *)*local_48;
      iVar13 = 0;
      if (psVar4 == (short *)0x0) {
        local_2c._0_2_ = 0;
        local_2c._2_1_ = '\0';
      }
      else {
        iVar20 = (int)psVar4[1];
        iVar10 = 0;
        puVar27 = (uint *)(psVar4 + 4);
        local_3c = 0;
        local_30 = 0;
        if (iVar20 == 0) {
          local_44 = *(int *)(psVar4 + 2);
          if (0 < local_44) {
            iVar20 = (int)*psVar4;
            do {
              if (0 < iVar20) {
                local_30 = local_30 + iVar20;
                local_40 = iVar20;
                do {
                  iVar16 = (uint)(byte)*puVar27 * 3;
                  iVar10 = iVar10 + (uint)(byte)(&Default_Palette)[iVar16];
                  local_3c = local_3c + (uint)(byte)(&DAT_0062c431)[iVar16];
                  puVar27 = (uint *)((int)puVar27 + 1);
                  iVar13 = iVar13 + (uint)(byte)(&DAT_0062c432)[iVar16];
                  local_40 = local_40 + -1;
                } while (local_40 != 0);
              }
              local_44 = local_44 + -1;
            } while (local_44 != 0);
          }
        }
        else if (iVar20 == 1) {
          local_40 = *(int *)(psVar4 + 2);
          if (0 < local_40) {
            iVar20 = (int)*psVar4 / 2;
            do {
              if (0 < iVar20) {
                local_30 = local_30 + iVar20;
                local_34 = iVar20;
                do {
                  uVar3 = (ushort)*puVar27;
                  iVar10 = iVar10 + (uVar3 >> 8 & 0xf) * 0x11;
                  local_3c = local_3c + (uVar3 >> 4 & 0xf) * 0x11;
                  puVar27 = (uint *)((int)puVar27 + 2);
                  iVar13 = iVar13 + (uVar3 & 0xf) * 0x11;
                  local_34 = local_34 + -1;
                } while (local_34 != 0);
              }
              local_40 = local_40 + -1;
            } while (local_40 != 0);
          }
        }
        else if (iVar20 == 2) {
          local_40 = *(int *)(psVar4 + 2);
          if (0 < local_40) {
            iVar20 = (int)*psVar4 / 2;
            do {
              if (0 < iVar20) {
                local_30 = local_30 + iVar20;
                local_34 = iVar20;
                do {
                  uVar3 = (ushort)*puVar27;
                  iVar10 = (uint)(uVar3 >> 0xd) + iVar10 + (uint)(uVar3 >> 0xb) * 8;
                  local_3c = (uVar3 >> 9 & 3) + local_3c + (uVar3 >> 5 & 0x3f) * 4;
                  puVar27 = (uint *)((int)puVar27 + 2);
                  local_34 = local_34 + -1;
                  iVar13 = (uVar3 >> 2 & 7) + iVar13 + (uVar3 & 0x1f) * 8;
                } while (local_34 != 0);
              }
              local_40 = local_40 + -1;
            } while (local_40 != 0);
          }
        }
        else if ((iVar20 - 3U < 2) && (local_40 = *(int *)(psVar4 + 2), 0 < local_40)) {
          iVar20 = (int)((int)*psVar4 + ((int)*psVar4 >> 0x1f & 3U)) >> 2;
          do {
            if (0 < iVar20) {
              local_30 = local_30 + iVar20;
              local_34 = iVar20;
              do {
                uVar24 = *puVar27;
                iVar10 = iVar10 + (uVar24 >> 0x10 & 0xff);
                local_3c = local_3c + (uVar24 >> 8 & 0xff);
                puVar27 = puVar27 + 1;
                iVar13 = iVar13 + (uVar24 & 0xff);
                local_34 = local_34 + -1;
              } while (local_34 != 0);
            }
            local_40 = local_40 + -1;
          } while (local_40 != 0);
        }
        local_2c._0_2_ = CONCAT11((char)(local_3c / local_30),(char)(iVar10 / local_30));
        local_2c._2_1_ = (uchar)(iVar13 / local_30);
      }
      local_48 = local_48 + 4;
      local_4c->r = (char)(undefined2)local_2c;
      local_4c->g = (char)((ushort)(undefined2)local_2c >> 8);
      local_4c->b = local_2c._2_1_;
      local_4c = local_4c + 1;
    } while ((int)local_48 < 0xcaf8ec);
    _ftol2_sse();
    uVar24 = extraout_EAX_03;
    if (0xff < (int)extraout_EAX_03) {
      uVar24 = 0xff;
    }
    _ftol2_sse();
    uVar23 = extraout_EAX_04;
    if (0xff < (int)extraout_EAX_04) {
      uVar23 = 0xff;
    }
    _ftol2_sse();
    uVar17 = extraout_EAX_05;
    if (0xff < (int)extraout_EAX_05) {
      uVar17 = 0xff;
    }
    colorTable[10] = ((uVar24 | 0xffffff00) << 8 | uVar23 & 0xff) << 8 | uVar17 & 0xff;
    iVar13 = 0;
    do {
      local_38 = 0;
      local_2c = 2;
      pfVar21 = &mix2UV[iVar13][0][0].u1;
      do {
        local_3c = 0;
        local_30 = 2;
        pfVar18 = pfVar21;
        do {
          switch(iVar13) {
          case 0:
          case 8:
            fVar5 = (float)local_38 * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)local_3c * 0.5;
            pfVar18[-1] = fVar6;
            fVar7 = fVar5 + 0.5;
            break;
          case 1:
          case 9:
            fVar5 = (float)local_3c * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)(int)local_2c * 0.5;
            pfVar18[-1] = fVar6;
            *pfVar18 = fVar5;
            fVar7 = fVar6 - 0.5;
            goto LAB_00523799;
          case 2:
          case 10:
            fVar5 = (float)(int)local_2c * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)local_30 * 0.5;
            pfVar18[-1] = fVar6;
            fVar7 = fVar5 - 0.5;
            goto LAB_00523830;
          case 3:
          case 0xb:
            fVar5 = (float)local_30 * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)local_38 * 0.5;
            pfVar18[-1] = fVar6;
            *pfVar18 = fVar5;
            fVar7 = fVar6 + 0.5;
            goto LAB_005237c9;
          case 4:
          case 0xf:
            fVar5 = (float)(int)local_2c * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)local_3c * 0.5;
            pfVar18[-1] = fVar6;
            fVar7 = fVar5 - 0.5;
            break;
          case 5:
          case 0xc:
            fVar5 = (float)local_30 * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)(int)local_2c * 0.5;
            pfVar18[-1] = fVar6;
            *pfVar18 = fVar5;
            fVar7 = fVar6 - 0.5;
LAB_005237c9:
            pfVar18[1] = fVar7;
            fVar5 = fVar5 - 0.5;
            goto LAB_005237a0;
          case 6:
          case 0xd:
            fVar5 = (float)local_38 * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)local_30 * 0.5;
            pfVar18[-1] = fVar6;
            fVar7 = fVar5 + 0.5;
LAB_00523830:
            *pfVar18 = fVar7;
            pfVar18[2] = fVar7;
            pfVar18[1] = fVar6;
            fVar6 = fVar6 - 0.5;
            goto LAB_0052383a;
          case 7:
          case 0xe:
            fVar5 = (float)local_3c * 0.5;
            ((tagMIX2UV *)(pfVar18 + -2))->u0 = fVar5;
            fVar6 = (float)local_38 * 0.5;
            pfVar18[-1] = fVar6;
            *pfVar18 = fVar5;
            fVar7 = fVar6 + 0.5;
LAB_00523799:
            pfVar18[1] = fVar7;
            fVar5 = fVar5 + 0.5;
LAB_005237a0:
            pfVar18[2] = fVar5;
            pfVar18[4] = fVar5;
            pfVar18[3] = fVar7;
            pfVar18[5] = fVar6;
          default:
            goto switchD_00523741_default;
          }
          *pfVar18 = fVar7;
          pfVar18[2] = fVar7;
          pfVar18[1] = fVar6;
          fVar6 = fVar6 + 0.5;
LAB_0052383a:
          pfVar18[3] = fVar6;
          pfVar18[5] = fVar6;
          pfVar18[4] = fVar5;
switchD_00523741_default:
          local_3c = local_3c + 1;
          pfVar18 = pfVar18 + 0x40;
          local_30 = local_30 + -1;
        } while (-6 < local_30);
        local_38 = local_38 + 1;
        pfVar21 = pfVar21 + 8;
        local_2c = local_2c + -1;
      } while (-6 < (int)local_2c);
      iVar13 = iVar13 + 1;
    } while (iVar13 < 0x10);
  }
  return;
}
