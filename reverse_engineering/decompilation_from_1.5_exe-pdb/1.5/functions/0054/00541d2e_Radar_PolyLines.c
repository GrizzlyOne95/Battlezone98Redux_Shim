/*
 * Entry: 00541d2e
 * Name: Radar_PolyLines
 * Namespace: Global
 * Signature: void Radar_PolyLines(_GRAPHIC_BUFFER * param_1, RADAR_MESH * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Radar_PolyLines(_GRAPHIC_BUFFER *param_1,RADAR_MESH *param_2)

{
  RADAR_MESH *pRVar1;
  int iVar2;
  int iVar3;
  RADAR_MESH *pRVar4;
  RADAR_MESH *pRVar5;
  RADAR_MESH *pRVar6;
  long local_218 [128];
  POLYGON_SKIN local_18;
  int local_14;
  RADAR_MESH *local_10;
  RADAR_MESH *local_c;
  RADAR_MESH *local_8;
  
  local_14 = param_2->dx;
  pRVar6 = (RADAR_MESH *)param_2->dy;
  local_18 = (POLYGON_SKIN)param_2->color;
  local_10 = pRVar6;
  Render_RadarBackdrop();
  pRVar1 = pRVar6;
  pRVar5 = param_2;
  iVar3 = local_14;
  for (; pRVar4 = param_2, local_14 = iVar3, 0 < (int)pRVar6;
      pRVar6 = (RADAR_MESH *)((int)&pRVar6[-1].color + 3)) {
    iVar2 = 0;
    local_8 = pRVar5;
    if (0 < iVar3) {
      do {
        if (pRVar5->mesh[0].x == 0) {
          if (1 < iVar2) {
            D3D_PolyLine(local_c->mesh,iVar2,local_18);
          }
          iVar2 = 0;
        }
        else {
          if (iVar2 == 0) {
            local_c = pRVar5;
          }
          iVar2 = iVar2 + 1;
        }
        iVar3 = iVar3 + -1;
        pRVar5 = (RADAR_MESH *)(pRVar5->mesh + 1);
      } while (0 < iVar3);
      if (1 < iVar2) {
        D3D_PolyLine(local_c->mesh,iVar2,local_18);
      }
    }
    pRVar5 = (RADAR_MESH *)(local_8->mesh + local_14);
    pRVar1 = local_10;
    iVar3 = local_14;
  }
  while (local_10 = (RADAR_MESH *)iVar3, 0 < (int)local_10) {
    iVar3 = 0;
    pRVar6 = (RADAR_MESH *)local_218;
    param_2 = pRVar1;
    local_8 = pRVar4;
    if (0 < (int)pRVar1) {
      do {
        if (pRVar4->mesh[0].x == 0) {
          if (1 < iVar3) {
            D3D_PolyLine(local_c->mesh,iVar3,local_18);
          }
          iVar3 = 0;
        }
        else {
          if (iVar3 == 0) {
            local_c = pRVar6;
          }
          pRVar6->mesh[0].x = pRVar4->mesh[0].x;
          pRVar6->mesh[0].y = pRVar4->mesh[0].y;
          pRVar6 = (RADAR_MESH *)(pRVar6->mesh + 1);
          iVar3 = iVar3 + 1;
        }
        param_2 = (RADAR_MESH *)((int)&param_2[-1].color + 3);
        pRVar4 = (RADAR_MESH *)(pRVar4->mesh + local_14);
      } while (0 < (int)param_2);
      if (1 < iVar3) {
        D3D_PolyLine(local_c->mesh,iVar3,local_18);
      }
    }
    pRVar4 = (RADAR_MESH *)(local_8->mesh + 1);
    iVar3 = (int)local_10 + -1;
  }
  return;
}
