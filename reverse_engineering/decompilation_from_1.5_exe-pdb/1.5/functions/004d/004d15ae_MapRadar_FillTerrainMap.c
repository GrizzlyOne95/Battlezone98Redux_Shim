/*
 * Entry: 004d15ae
 * Name: MapRadar::FillTerrainMap
 * Namespace: MapRadar
 * Signature: void FillTerrainMap(MapRadar * this, TEXTURE * param_1, float param_2, float param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall
MapRadar::FillTerrainMap
          (MapRadar *this,TEXTURE *param_1,float param_2,float param_3,float param_4,float param_5)

{
  undefined2 uVar1;
  float fVar2;
  RGB RVar3;
  undefined1 extraout_var;
  byte *pbVar4;
  int iVar5;
  int unaff_ESI;
  int iVar6;
  int unaff_EDI;
  TEXTURE *pTVar7;
  undefined1 local_84c [4];
  undefined8 local_848;
  undefined8 local_840;
  int local_838;
  int local_834;
  int local_830;
  int local_82c;
  int local_828;
  TEXTURE *local_824;
  float local_820;
  int local_81c;
  int local_818;
  undefined2 local_814;
  byte local_812;
  undefined1 *local_810;
  float local_80c;
  undefined1 local_808 [60];
  undefined1 local_7cc [1988];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7cc;
  local_82c = 0;
  local_824 = param_1;
  local_810 = local_808;
  do {
    RVar3 = GetTextureIndexColor((int)local_84c);
    local_828 = 0;
    uVar1 = *(undefined2 *)CONCAT13(extraout_var,RVar3);
    local_812 = *(byte *)((undefined2 *)CONCAT13(extraout_var,RVar3) + 1);
    local_814._1_1_ = (byte)((ushort)uVar1 >> 8);
    local_814._0_1_ = (byte)uVar1;
    local_838 = (uint)local_812 * 8 + 8;
    local_830 = (uint)local_814._1_1_ * 8 + 8;
    local_834 = (uint)(byte)local_814 * 8 + 8;
    do {
      local_830 = local_830 + (uint)local_814._1_1_;
      local_838 = local_838 + (uint)local_812;
      local_834 = local_834 + (uint)(byte)local_814;
      local_81c = -1;
      local_80c = 0.0;
      local_840 = (double)CONCAT44(local_834 >> 5,(long)local_840);
      local_848 = (double)CONCAT44(local_830 >> 5,(long)local_848);
      local_820 = (float)(local_838 >> 5);
      local_818 = 0x7fffffff;
      pbVar4 = &DAT_0062c431;
      do {
        iVar5 = (local_834 >> 5) - (uint)pbVar4[-1];
        iVar6 = (local_830 >> 5) - (uint)*pbVar4;
        iVar5 = ((int)local_820 - (uint)pbVar4[1]) * ((int)local_820 - (uint)pbVar4[1]) +
                iVar6 * iVar6 + iVar5 * iVar5;
        if (iVar5 < local_818) {
          local_81c = (int)local_80c;
          local_818 = iVar5;
        }
        local_80c = (float)((int)local_80c + 1);
        pbVar4 = pbVar4 + 3;
      } while ((int)pbVar4 < 0x62c731);
      iVar5 = local_828 + 1;
      local_810[local_828] = (undefined1)local_81c;
      local_828 = iVar5;
    } while (iVar5 < 0x20);
    local_82c = local_82c + 1;
    local_810 = local_810 + 0x20;
    local_814 = uVar1;
  } while (local_82c < 0x40);
  iVar5 = (int)local_824->width;
  local_818 = local_824->height;
  pTVar7 = local_824 + 1;
  local_824 = (TEXTURE *)(((param_4 - param_2) * Terrain.Grid_Scale) / (float)iVar5);
  local_820 = ((param_3 - param_5) * Terrain.Grid_Scale) / (float)local_818;
  local_80c = param_5 * Terrain.Grid_Scale;
  fVar2 = Terrain.Grid_Scale;
  if (0 < local_818) {
    do {
      local_848 = (double)(local_80c + (float)Float2Int);
      local_810 = (undefined1 *)(param_2 * fVar2);
      local_81c = iVar5;
      if (0 < iVar5) {
        do {
          local_840 = (double)((float)local_810 + (float)Float2Int);
          iVar6 = GetTileTextureIndex((long)local_840,(long)local_848);
          pbVar4 = GetNormalPtr(unaff_EDI,unaff_ESI);
          local_810 = (undefined1 *)((float)local_810 + (float)local_824);
          *(undefined1 *)&pTVar7->width = local_808[(uint)(*pbVar4 >> 3) + iVar6 * 0x20];
          pTVar7 = (TEXTURE *)((int)&pTVar7->width + 1);
          local_81c = local_81c + -1;
          fVar2 = Terrain.Grid_Scale;
        } while (local_81c != 0);
      }
      local_818 = local_818 + -1;
      local_80c = local_80c + local_820;
    } while (local_818 != 0);
  }
  return;
}
