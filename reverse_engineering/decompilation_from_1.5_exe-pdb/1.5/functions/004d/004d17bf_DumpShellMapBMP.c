/*
 * Entry: 004d17bf
 * Name: DumpShellMapBMP
 * Namespace: Global
 * Signature: void DumpShellMapBMP(char * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DumpShellMapBMP(char *param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  uint3 uVar2;
  undefined4 uVar3;
  RGB RVar4;
  char *_Dest;
  undefined1 extraout_var;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  byte *pbVar8;
  int unaff_EBX;
  int iVar9;
  int iVar10;
  int unaff_EDI;
  undefined1 local_c170 [49124];
  undefined1 local_18c [28];
  undefined4 local_170;
  int local_16c;
  int local_168;
  undefined2 local_164;
  undefined2 local_162;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  double local_148;
  double local_140;
  undefined2 local_138;
  int local_136;
  undefined2 local_132;
  undefined2 local_130;
  undefined4 local_12e;
  undefined1 *local_128;
  FILE *local_124;
  float local_120;
  undefined1 *local_11c;
  undefined4 local_118;
  float local_114;
  float local_110;
  undefined1 *local_10c;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_18c;
  if ((_S2 & 1) == 0) {
    _S2 = _S2 | 1;
    pad = param_2 & 3;
  }
  strncpy(local_108,param_1,0x100);
  _Dest = strrchr(local_108,0x2e);
  if (_Dest != (char *)0x0) {
    strncpy(_Dest,".BMP",(int)&local_8 - (int)_Dest);
  }
  local_124 = fopen(local_108,"wb");
  if (local_124 != (FILE *)0x0) {
    Trace("Writing %dx%d shell map to %s\n");
    iVar9 = param_2 * 3;
    local_138 = 0x4d42;
    local_136 = (iVar9 + pad) * param_3 + 0x36;
    local_12e = 0x36;
    local_132 = 0;
    local_130 = 0;
    fwrite(&local_138,0xe,1,local_124);
    local_16c = param_2;
    local_164 = 1;
    local_162 = 0x18;
    local_158 = 0xb12;
    local_154 = 0xb12;
    local_168 = param_3;
    local_170 = 0x28;
    local_160 = 0;
    local_15c = 0;
    local_150 = 0;
    local_14c = 0;
    fwrite(&local_170,0x28,1,local_124);
    local_10c = local_c170 + 1;
    local_110 = 0.0;
    do {
      RVar4 = GetTextureIndexColor((int)&local_128);
      iVar7 = pad;
      uVar2 = *(uint3 *)CONCAT13(extraout_var,RVar4);
      local_118 = (float)CONCAT13(local_118._3_1_,uVar2);
      uVar3 = local_118;
      local_118._1_1_ = (byte)(uVar2 >> 8);
      local_118._2_1_ = (byte)(uVar2 >> 0x10);
      local_120 = (float)((uint)local_118._2_1_ << 6);
      iVar10 = (uint)local_118._1_1_ << 6;
      local_114 = (float)((uVar2 & 0xff) << 6);
      local_11c = local_10c;
      local_10c = (undefined1 *)0x100;
      do {
        iVar5 = (int)local_114 / 0xff;
        if (0xff < iVar5) {
          iVar5 = 0xff;
        }
        local_11c[-1] = (char)iVar5;
        iVar5 = iVar10 / 0xff;
        if (0xff < iVar5) {
          iVar5 = 0xff;
        }
        *local_11c = (char)iVar5;
        iVar5 = 0xff;
        if ((int)local_120 / 0xff < 0x100) {
          iVar5 = (int)local_120 / 0xff;
        }
        local_11c[1] = (char)iVar5;
        local_114 = (float)((int)local_114 + (uVar2 & 0xff));
        iVar10 = iVar10 + ((uVar2 & 0xff00) >> 8);
        local_120 = (float)((int)local_120 + (uint)(uVar2 >> 0x10));
        local_11c = local_11c + 3;
        local_10c = (undefined1 *)((int)local_10c + -1);
      } while (local_10c != (undefined1 *)0x0);
      local_110 = (float)((int)local_110 + 1);
      local_118 = (float)uVar3;
      local_10c = local_11c;
    } while ((int)local_110 < 0x40);
    puVar6 = calloc(iVar9 + pad,param_3);
    local_114 = (float)param_3;
    local_10c = (undefined1 *)(float)param_2;
    local_128 = puVar6;
    local_110 = max<float>(((edgeMaxX - edgeMinX) * Terrain.Grid_Scale) / (float)local_10c,
                           ((edgeMaxZ - edgeMinZ) * Terrain.Grid_Scale) / local_114);
    local_118 = (edgeMinX + edgeMaxX) * Terrain.Grid_Scale * 0.5 -
                (float)local_10c * local_110 * 0.5;
    local_11c = (undefined1 *)
                ((edgeMinZ + edgeMaxZ) * Terrain.Grid_Scale * 0.5 - local_114 * local_110 * 0.5);
    if (0 < param_3) {
      local_114 = (float)param_3;
      do {
        local_140 = (double)((float)local_11c + (float)Float2Int);
        local_120 = local_118;
        if (0 < param_2) {
          local_10c = (undefined1 *)param_2;
          do {
            local_148 = (double)(local_120 + (float)Float2Int);
            iVar7 = GetTileTextureIndex(local_148._0_4_,local_140._0_4_);
            pbVar8 = GetNormalPtr(unaff_EDI,unaff_EBX);
            local_120 = local_120 + local_110;
            iVar7 = (iVar7 * 0x100 + (uint)*pbVar8) * 3;
            *puVar6 = local_c170[iVar7 + 2];
            uVar1 = local_c170[iVar7];
            puVar6[1] = local_c170[iVar7 + 1];
            puVar6[2] = uVar1;
            puVar6 = puVar6 + 3;
            local_10c = (undefined1 *)((int)local_10c + -1);
          } while (local_10c != (undefined1 *)0x0);
          local_10c = (undefined1 *)0x0;
          iVar7 = pad;
        }
        puVar6 = puVar6 + iVar7;
        local_114 = (float)((int)local_114 + -1);
        local_11c = (undefined1 *)((float)local_11c + local_110);
      } while (local_114 != 0.0);
    }
    fwrite(local_128,param_3,iVar9 + iVar7,local_124);
    fclose(local_124);
    free(local_128);
  }
  return;
}
