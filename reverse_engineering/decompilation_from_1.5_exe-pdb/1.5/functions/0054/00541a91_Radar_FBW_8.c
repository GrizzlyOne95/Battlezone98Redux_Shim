/*
 * Entry: 00541a91
 * Name: Radar_FBW_8
 * Namespace: Global
 * Signature: void Radar_FBW_8(_GRAPHIC_BUFFER * param_1, RADAR_MESH * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl Radar_FBW_8(_GRAPHIC_BUFFER *param_1,RADAR_MESH *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  RADAR_MESH *pRVar6;
  RADAR_MESH *pRVar7;
  int iVar8;
  uchar uVar9;
  uchar *puVar10;
  int local_50 [11];
  int local_24;
  int local_20;
  int local_1c;
  int local_10;
  int local_c;
  int local_8;
  
  iVar3 = param_2->dx;
  uVar9 = (uchar)param_2->color;
  iVar2 = param_2->dy;
  pRVar7 = param_2;
  for (iVar1 = iVar2; pRVar6 = pRVar7, local_c = iVar3, iVar4 = iVar3, 0 < iVar1; iVar1 = iVar1 + -1
      ) {
    while ((local_c = local_c + -1, pRVar6->mesh[0].x == 0 && (0 < local_c))) {
      pRVar6 = (RADAR_MESH *)(pRVar6->mesh + 1);
    }
    iVar4 = param_1->Width;
    puVar10 = param_1->Buffer +
              (pRVar6->mesh[0].y + (param_1->Pane).y0) * iVar4 + pRVar6->mesh[0].x +
              (param_1->Pane).x0;
    for (; 0 < local_c; local_c = local_c + -1) {
      local_10 = ((RADAR_MESH *)(pRVar6->mesh + 1))->mesh[0].x;
      if (local_10 == 0) break;
      local_10 = local_10 - pRVar6->mesh[0].x;
      local_20 = 1;
      if (local_10 < 0) {
        local_20 = -1;
        local_10 = -local_10;
      }
      local_24 = pRVar6->mesh[1].y - pRVar6->mesh[0].y;
      local_1c = iVar4;
      if (local_24 < 0) {
        local_1c = -iVar4;
        local_24 = -local_24;
      }
      if (local_10 < local_24) {
        iVar8 = local_10 * 2 - local_24;
        local_50[0] = local_20 + local_1c;
        local_50[1] = local_1c;
        local_50[3] = local_10 * 2;
        local_50[2] = iVar8 - local_24;
        local_10 = local_24;
      }
      else {
        iVar8 = local_24 * 2 - local_10;
        local_50[0] = local_1c + local_20;
        local_50[1] = local_20;
        local_50[3] = local_24 * 2;
        local_50[2] = iVar8 - local_10;
      }
      while( true ) {
        iVar5 = iVar8 >> 0x1f;
        if (local_10 < 1) break;
        iVar8 = iVar8 + local_50[2 - iVar5];
        iVar5 = local_50[-iVar5];
        *puVar10 = uVar9;
        puVar10 = puVar10 + iVar5;
        local_10 = local_10 + -1;
      }
      pRVar6 = (RADAR_MESH *)(pRVar6->mesh + 1);
    }
    pRVar7 = (RADAR_MESH *)(pRVar7->mesh + iVar3);
  }
  do {
    pRVar7 = param_2;
    local_8 = iVar2;
    if (iVar4 < 1) {
      return;
    }
    while ((local_8 = local_8 + -1, pRVar7->mesh[0].x == 0 && (0 < local_8))) {
      pRVar7 = (RADAR_MESH *)(pRVar7->mesh + iVar3);
    }
    iVar1 = param_1->Width;
    puVar10 = param_1->Buffer +
              (pRVar7->mesh[0].y + (param_1->Pane).y0) * iVar1 + pRVar7->mesh[0].x +
              (param_1->Pane).x0;
    for (; 0 < local_8; local_8 = local_8 + -1) {
      pRVar6 = (RADAR_MESH *)(pRVar7->mesh + iVar3);
      local_10 = pRVar6->mesh[0].x;
      if (local_10 == 0) break;
      local_10 = local_10 - pRVar7->mesh[0].x;
      local_20 = 1;
      if (local_10 < 0) {
        local_20 = -1;
        local_10 = -local_10;
      }
      local_24 = pRVar6->mesh[0].y - pRVar7->mesh[0].y;
      local_1c = iVar1;
      if (local_24 < 0) {
        local_1c = -iVar1;
        local_24 = -local_24;
      }
      if (local_10 < local_24) {
        iVar8 = local_10 * 2 - local_24;
        local_50[0] = local_20 + local_1c;
        local_50[1] = local_1c;
        local_50[3] = local_10 * 2;
        local_50[2] = iVar8 - local_24;
        local_10 = local_24;
      }
      else {
        iVar8 = local_24 * 2 - local_10;
        local_50[0] = local_1c + local_20;
        local_50[1] = local_20;
        local_50[3] = local_24 * 2;
        local_50[2] = iVar8 - local_10;
      }
      while( true ) {
        iVar5 = iVar8 >> 0x1f;
        if (local_10 < 1) break;
        iVar8 = iVar8 + local_50[2 - iVar5];
        iVar5 = local_50[-iVar5];
        *puVar10 = uVar9;
        puVar10 = puVar10 + iVar5;
        local_10 = local_10 + -1;
      }
      pRVar7 = pRVar6;
    }
    param_2 = (RADAR_MESH *)(param_2->mesh + 1);
    iVar4 = iVar4 + -1;
  } while( true );
}
