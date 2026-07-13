/*
 * Entry: 004d1b79
 * Name: DumpLargeMapBMP
 * Namespace: Global
 * Signature: void DumpLargeMapBMP(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DumpLargeMapBMP(char *param_1,int param_2)

{
  undefined1 *puVar1;
  short sVar2;
  ushort uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  byte bVar10;
  char *_Dest;
  int iVar11;
  TEXTURE *pTVar12;
  byte *pbVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  size_t _Size;
  int iVar17;
  int iStack_10240;
  int iStack_10238;
  undefined4 uStack_10230;
  uint uStack_1022c;
  size_t sStack_10228;
  undefined2 uStack_10224;
  undefined2 uStack_10222;
  undefined4 uStack_10220;
  undefined4 uStack_1021c;
  undefined4 uStack_10218;
  undefined4 uStack_10214;
  undefined4 uStack_10210;
  undefined4 uStack_1020c;
  double dStack_10208;
  undefined2 uStack_10200;
  int iStack_101fe;
  undefined2 uStack_101fa;
  undefined2 uStack_101f8;
  undefined4 uStack_101f6;
  float fStack_101f0;
  float fStack_101ec;
  float fStack_101e8;
  float fStack_101e4;
  float fStack_101e0;
  float fStack_101dc;
  float fStack_101d8;
  float fStack_101d4;
  int iStack_101d0;
  float fStack_101cc;
  uint uStack_101c8;
  uint uStack_101c4;
  uint uStack_101c0;
  uint uStack_101bc;
  size_t sStack_101b8;
  float fStack_101b4;
  float fStack_101b0;
  int iStack_101ac;
  float fStack_101a8;
  int iStack_101a4;
  float fStack_101a0;
  int iStack_1019c;
  float fStack_10198;
  float fStack_10194;
  undefined8 uStack_10190;
  float fStack_10188;
  double dStack_10184;
  float fStack_1017c;
  int iStack_10178;
  int iStack_10174;
  float fStack_10170;
  int iStack_1016c;
  undefined1 *puStack_10168;
  int iStack_10164;
  int iStack_10160;
  int iStack_1015c;
  double dStack_10158;
  int iStack_10150;
  int iStack_1014c;
  uint uStack_10148;
  int iStack_10144;
  int iStack_10140;
  int iStack_1013c;
  FILE *pFStack_10138;
  int iStack_10134;
  int iStack_10130;
  int iStack_1012c;
  size_t sStack_10128;
  int iStack_10124;
  float fStack_10120;
  byte bStack_10119;
  int iStack_10118;
  undefined1 *puStack_10114;
  int iStack_10110;
  undefined2 uStack_1010c;
  byte bStack_1010a;
  byte abStack_10108 [65536];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (int)&uStack_10190 + 4U;
  strncpy(local_108,param_1,0x100);
  _Dest = strrchr(local_108,0x2e);
  if (_Dest != (char *)0x0) {
    strncpy(_Dest,".BMP",(int)&local_8 - (int)_Dest);
  }
  pFStack_10138 = fopen(local_108,"wb");
  if (pFStack_10138 != (FILE *)0x0) {
    fVar4 = (float)Float2Int;
    dStack_10208 = (double)(edgeMinX * Terrain.Grid_Scale + fVar4);
    dStack_10184 = (double)(edgeMaxX * Terrain.Grid_Scale + fVar4);
    uVar15 = ((dStack_10184._0_4_ - dStack_10208._0_4_) + 1) * param_2;
    dStack_10158 = (double)(edgeMinZ * Terrain.Grid_Scale + fVar4);
    uStack_10190 = (double)(fVar4 + edgeMaxZ * Terrain.Grid_Scale);
    _Size = (((int)uStack_10190 - dStack_10158._0_4_) + 1) * param_2;
    sStack_101b8 = _Size;
    Trace("Writing %dx%d large map to %s\n");
    sStack_10128 = (uVar15 & 3) + uVar15 * 3;
    uStack_10200 = 0x4d42;
    iStack_101fe = sStack_10128 * _Size + 0x36;
    uStack_101f6 = 0x36;
    uStack_101fa = 0;
    uStack_101f8 = 0;
    fwrite(&uStack_10200,0xe,1,pFStack_10138);
    uStack_10224 = 1;
    uStack_10222 = 0x18;
    uStack_10230 = 0x28;
    uStack_10220 = 0;
    uStack_1021c = 0;
    uStack_10218 = 0xb12;
    uStack_10214 = 0xb12;
    uStack_10210 = 0;
    uStack_1020c = 0;
    uStack_1022c = uVar15;
    sStack_10228 = _Size;
    fwrite(&uStack_10230,0x28,1,pFStack_10138);
    iStack_10110 = 0;
    pbVar13 = abStack_10108;
    do {
      iStack_10124 = iStack_10110 << 6;
      iStack_10118 = 0;
      do {
        iVar11 = iStack_10124 / 0xff;
        if (0xff < iVar11) {
          iVar11 = 0xff;
        }
        iVar16 = iStack_10118 + 1;
        pbVar13[iStack_10118] = (byte)iVar11;
        iStack_10124 = iStack_10124 + iStack_10110;
        iStack_10118 = iVar16;
      } while (iVar16 < 0x100);
      iStack_10110 = iStack_10110 + 1;
      pbVar13 = pbVar13 + 0x100;
    } while (iStack_10110 < 0x100);
    puStack_10168 = calloc(sStack_10128,_Size);
    iStack_10110 = dStack_10158._0_4_;
    puStack_10114 = puStack_10168;
    if (dStack_10158._0_4_ <= (int)uStack_10190) {
      iVar11 = sStack_10128 * param_2 + uVar15 * -3;
      uVar15 = (uint)uStack_1010c._1_1_;
      iStack_10174 = iVar11;
      do {
        if (dStack_10208._0_4_ <= dStack_10184._0_4_) {
          iStack_101ac = (3 - sStack_10128) * param_2;
          iVar16 = dStack_10208._0_4_;
          do {
            iVar11 = iVar16;
            iVar17 = iStack_10110;
            GetTileTextureIndex(iVar16,iStack_10110);
            pbVar13 = GetNormalPtr(iVar11,iVar17);
            uStack_101c8 = (uint)*pbVar13;
            iStack_1016c = iVar16 + 1;
            pbVar13 = GetNormalPtr(iVar11,iVar17);
            uStack_101c4 = (uint)*pbVar13;
            pbVar13 = GetNormalPtr(iVar11,iVar17);
            uStack_101c0 = (uint)*pbVar13;
            pbVar13 = GetNormalPtr(iVar11,iVar17);
            uStack_101bc = (uint)*pbVar13;
            pTVar12 = GetTileTextureUV(iVar16,iStack_10110,&fStack_101e0,&fStack_101f0);
            iStack_10118 = (int)pTVar12->width;
            if (0 < pTVar12->type) {
              iStack_10118 = iStack_10118 >> 1;
            }
            if (2 < pTVar12->type) {
              iStack_10118 = iStack_10118 >> 1;
            }
            iStack_10144 = pTVar12->height;
            fStack_10170 = 1.0 / (float)iStack_10118;
            fStack_101cc = 1.0 / (float)iStack_10144;
            if (0 < param_2) {
              iStack_10124 = iStack_10144 * iStack_10118;
              iStack_101a4 = param_2 * 3;
              iStack_1012c = 0;
              iStack_1015c = param_2;
              do {
                iStack_1019c = iStack_1012c / param_2;
                iStack_101d0 = iStack_1012c + iStack_10144;
                iStack_10164 = iStack_101d0 / param_2;
                iStack_1013c = 0;
                iStack_1012c = param_2;
                do {
                  iStack_1014c = 0;
                  iStack_10150 = 0;
                  iStack_10140 = 0;
                  iStack_10130 = iStack_1019c;
                  if (iStack_1019c < iStack_10164) {
                    fVar4 = (float)Float2Int;
                    iStack_10178 = iStack_1013c / param_2;
                    iStack_10160 = (iStack_1013c + iStack_10118) / param_2;
                    do {
                      iStack_10134 = iStack_10178;
                      if (iStack_10178 < iStack_10160) {
                        fVar8 = ((float)iStack_10130 + 0.5) * fStack_101cc;
                        fStack_101b0 = fStack_101dc - fStack_101e0;
                        fStack_1017c = fStack_101d8 - fStack_101d4;
                        fStack_101b4 = (float)(iStack_10118 + -1);
                        fStack_10188 = fStack_101ec - fStack_101f0;
                        fStack_10198 = fStack_101e8 - fStack_101e4;
                        fStack_10194 = (float)(iStack_10144 + -1);
                        fStack_10120 = (float)(int)uStack_101bc;
                        fStack_101a0 = (float)(int)uStack_101c4 - (float)(int)uStack_101c8;
                        fStack_101a8 = (float)(int)uStack_101c0 - fStack_10120;
                        do {
                          iVar11 = (int)pTVar12->type;
                          fVar5 = ((float)iStack_10134 + 0.5) * fStack_10170;
                          fVar7 = fStack_101b0 * fVar5 + fStack_101e0;
                          fVar6 = fStack_10188 * fVar5 + fStack_101f0;
                          iStack_10238 = SUB84((double)((((fStack_10198 * fVar5 + fStack_101e4) -
                                                         fVar6) * fVar8 + fVar6) * fStack_10194 +
                                                       fVar4),0);
                          fVar6 = fStack_101a0 * fVar5 + (float)(int)uStack_101c8;
                          iStack_10240 = SUB84((double)((((fStack_1017c * fVar5 + fStack_101d4) -
                                                         fVar7) * fVar8 + fVar7) * fStack_101b4 +
                                                       fVar4),0);
                          iStack_10240 = iStack_10238 * iStack_10118 + iStack_10240;
                          dStack_10158 = (double)(((fStack_101a8 * fVar5 + fStack_10120) - fVar6) *
                                                  fVar8 + fVar6 + fVar4);
                          if (iVar11 == 0) {
                            iVar11 = (uint)*(byte *)((int)&pTVar12[1].width + iStack_10240) * 3;
                            bStack_1010a = (&DAT_0062c432)[iVar11];
                            uStack_1010c._1_1_ = (byte)(*(ushort *)(&Default_Palette + iVar11) >> 8)
                            ;
                            uVar15 = (uint)uStack_1010c._1_1_;
                            _Size = sStack_101b8;
                            uStack_1010c = *(ushort *)(&Default_Palette + iVar11);
                          }
                          else if (iVar11 == 1) {
                            uVar3 = (&pTVar12[1].width)[iStack_10240];
                            bVar10 = (byte)(uVar3 >> 8);
                            bStack_10119 = bVar10 << 4;
                            uStack_1010c = (ushort)(bVar10 & 0xf ^ bStack_10119);
                            bVar10 = (byte)(uVar3 >> 4);
                            uVar15 = (uint)(byte)(bVar10 & 0xf ^ bVar10 << 4);
                            bStack_1010a = (byte)uVar3 & 0xf ^ (byte)uVar3 << 4;
                          }
                          else {
                            if (iVar11 == 2) {
                              sVar2 = (&pTVar12[1].width)[iStack_10240];
                              bVar10 = (byte)((ushort)sVar2 >> 8);
                              bVar10 = bVar10 & 0xf8 | bVar10 >> 5;
                              uStack_10148 = CONCAT22(uStack_10148._2_2_,sVar2);
                              uVar9 = uStack_10148;
                              uVar15 = (uint)(byte)((byte)(uStack_10148 >> 9) & 3 |
                                                   (char)(uStack_10148 >> 5) << 2);
                              uStack_10148._0_1_ = (byte)sVar2;
                              uVar14 = (uint)(byte)((byte)uStack_10148 >> 2 & 7 |
                                                   (byte)uStack_10148 << 3);
                              uStack_10148 = uVar9;
                            }
                            else {
                              if (1 < iVar11 - 3U) goto LAB_004d20b8;
                              uVar14 = *(uint *)(&pTVar12[1].width + iStack_10240 * 2);
                              bVar10 = (byte)(uVar14 >> 0x10);
                              uVar15 = uVar14 >> 8;
                            }
                            uStack_1010c = (ushort)bVar10;
                            bStack_1010a = (byte)uVar14;
                          }
LAB_004d20b8:
                          uVar14 = uVar15 & 0xff;
                          uVar15 = (uint)abStack_10108[uVar14 * 0x100 + dStack_10158._0_4_];
                          iStack_1014c = iStack_1014c +
                                         (uint)abStack_10108
                                               [(uint)(byte)uStack_1010c * 0x100 +
                                                dStack_10158._0_4_];
                          iStack_10150 = iStack_10150 + uVar15;
                          bStack_1010a = abStack_10108
                                         [(uint)bStack_1010a * 0x100 + dStack_10158._0_4_];
                          iStack_10140 = iStack_10140 + (uint)bStack_1010a;
                          iStack_10134 = iStack_10134 + 1;
                          uStack_1010c = CONCAT11(abStack_10108[uVar14 * 0x100 + dStack_10158._0_4_]
                                                  ,abStack_10108
                                                   [(uint)(byte)uStack_1010c * 0x100 +
                                                    dStack_10158._0_4_]);
                        } while (iStack_10134 < iStack_10160);
                      }
                      iStack_10130 = iStack_10130 + 1;
                    } while (iStack_10130 < iStack_10164);
                  }
                  *puStack_10114 = (char)((iStack_10140 * param_2 * param_2) / iStack_10124);
                  puVar1 = puStack_10114 + 2;
                  puStack_10114[1] = (char)((iStack_10150 * param_2 * param_2) / iStack_10124);
                  puStack_10114 = puStack_10114 + 3;
                  *puVar1 = (char)((iStack_1014c * param_2 * param_2) / iStack_10124);
                  iStack_1013c = iStack_1013c + iStack_10118;
                  iStack_1012c = iStack_1012c + -1;
                } while (iStack_1012c != 0);
                puStack_10114 = puStack_10114 + sStack_10128 + param_2 * -3;
                iStack_1015c = iStack_1015c + -1;
                iStack_1012c = iStack_101d0;
              } while (iStack_1015c != 0);
              iStack_1015c = 0;
            }
            puStack_10114 = puStack_10114 + iStack_101ac;
            iVar11 = iStack_10174;
            iVar16 = iStack_1016c;
          } while (iStack_1016c <= dStack_10184._0_4_);
        }
        puStack_10114 = puStack_10114 + iVar11;
        iStack_10110 = iStack_10110 + 1;
      } while (iStack_10110 <= (int)uStack_10190);
    }
    fwrite(puStack_10168,_Size,sStack_10128,pFStack_10138);
    fclose(pFStack_10138);
    free(puStack_10168);
  }
  return;
}
