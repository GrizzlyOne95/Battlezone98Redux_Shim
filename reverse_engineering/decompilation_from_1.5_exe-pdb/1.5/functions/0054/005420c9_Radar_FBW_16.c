/*
 * Entry: 005420c9
 * Name: Radar_FBW_16
 * Namespace: Global
 * Signature: void Radar_FBW_16(_GRAPHIC_BUFFER * param_1, RADAR_MESH * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl Radar_FBW_16(_GRAPHIC_BUFFER *param_1,RADAR_MESH *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  RADAR_MESH *pRVar6;
  RADAR_MESH *pRVar7;
  ushort *puVar8;
  int iVar9;
  ushort uVar10;
  int local_50 [11];
  int local_24;
  int local_20;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = param_2->dx;
  iVar2 = param_2->dy;
  iVar3 = param_2->color;
  iVar4 = iVar2;
  pRVar7 = param_2;
  if (((byte)D3IniFlags & 0x40) == 0) {
    uVar10 = D3D_Remap_Palette[iVar3];
  }
  else {
    uVar10 = ((Device.Palette[iVar3].r & 0xf0) + 0xf00) * 0x10 + (Device.Palette[iVar3].g & 0xf0) +
             (ushort)(Device.Palette[iVar3].b >> 4);
  }
  for (; pRVar6 = pRVar7, local_c = iVar1, iVar3 = iVar1, 0 < iVar4; iVar4 = iVar4 + -1) {
    while ((local_c = local_c + -1, pRVar6->mesh[0].x == 0 && (0 < local_c))) {
      pRVar6 = (RADAR_MESH *)(pRVar6->mesh + 1);
    }
    iVar3 = param_1->Width;
    puVar8 = (ushort *)
             (param_1->Buffer +
             ((pRVar6->mesh[0].y + (param_1->Pane).y0) * iVar3 + (param_1->Pane).x0 +
             pRVar6->mesh[0].x) * 2);
    for (; 0 < local_c; local_c = local_c + -1) {
      local_14 = ((RADAR_MESH *)(pRVar6->mesh + 1))->mesh[0].x;
      if (local_14 == 0) break;
      local_14 = local_14 - pRVar6->mesh[0].x;
      local_10 = iVar3 * 2;
      local_20 = 2;
      if (local_14 < 0) {
        local_14 = -local_14;
        local_20 = -2;
      }
      local_24 = pRVar6->mesh[1].y - pRVar6->mesh[0].y;
      if (local_24 < 0) {
        local_10 = iVar3 * -2;
        local_24 = -local_24;
      }
      if (local_14 < local_24) {
        iVar9 = local_14 * 2 - local_24;
        local_50[0] = local_20 + local_10;
        local_50[1] = local_10;
        local_50[3] = local_14 * 2;
        local_50[2] = iVar9 - local_24;
        local_14 = local_24;
      }
      else {
        iVar9 = local_24 * 2 - local_14;
        local_50[0] = local_10 + local_20;
        local_50[1] = local_20;
        local_50[3] = local_24 * 2;
        local_50[2] = iVar9 - local_14;
      }
      while( true ) {
        iVar5 = iVar9 >> 0x1f;
        if (local_14 < 1) break;
        iVar9 = iVar9 + local_50[2 - iVar5];
        iVar5 = local_50[-iVar5];
        *puVar8 = uVar10;
        puVar8 = (ushort *)((int)puVar8 + iVar5);
        local_14 = local_14 + -1;
      }
      pRVar6 = (RADAR_MESH *)(pRVar6->mesh + 1);
    }
    pRVar7 = (RADAR_MESH *)(pRVar7->mesh + iVar1);
  }
  do {
    pRVar7 = param_2;
    local_8 = iVar2;
    if (iVar3 < 1) {
      return;
    }
    while ((local_8 = local_8 + -1, pRVar7->mesh[0].x == 0 && (0 < local_8))) {
      pRVar7 = (RADAR_MESH *)(pRVar7->mesh + iVar1);
    }
    iVar4 = param_1->Width;
    puVar8 = (ushort *)
             (param_1->Buffer +
             ((pRVar7->mesh[0].y + (param_1->Pane).y0) * iVar4 + (param_1->Pane).x0 +
             pRVar7->mesh[0].x) * 2);
    for (; 0 < local_8; local_8 = local_8 + -1) {
      pRVar6 = (RADAR_MESH *)(pRVar7->mesh + iVar1);
      local_14 = pRVar6->mesh[0].x;
      if (local_14 == 0) break;
      local_14 = local_14 - pRVar7->mesh[0].x;
      local_10 = iVar4 * 2;
      local_20 = 2;
      if (local_14 < 0) {
        local_14 = -local_14;
        local_20 = -2;
      }
      local_24 = pRVar6->mesh[0].y - pRVar7->mesh[0].y;
      if (local_24 < 0) {
        local_10 = iVar4 * -2;
        local_24 = -local_24;
      }
      if (local_14 < local_24) {
        iVar9 = local_14 * 2 - local_24;
        local_50[0] = local_20 + local_10;
        local_50[1] = local_10;
        local_50[3] = local_14 * 2;
        local_50[2] = iVar9 - local_24;
        local_14 = local_24;
      }
      else {
        iVar9 = local_24 * 2 - local_14;
        local_50[0] = local_10 + local_20;
        local_50[1] = local_20;
        local_50[3] = local_24 * 2;
        local_50[2] = iVar9 - local_14;
      }
      while( true ) {
        iVar5 = iVar9 >> 0x1f;
        if (local_14 < 1) break;
        iVar9 = iVar9 + local_50[2 - iVar5];
        iVar5 = local_50[-iVar5];
        *puVar8 = uVar10;
        puVar8 = (ushort *)((int)puVar8 + iVar5);
        local_14 = local_14 + -1;
      }
      pRVar7 = pRVar6;
    }
    param_2 = (RADAR_MESH *)(param_2->mesh + 1);
    iVar3 = iVar3 + -1;
  } while( true );
}
