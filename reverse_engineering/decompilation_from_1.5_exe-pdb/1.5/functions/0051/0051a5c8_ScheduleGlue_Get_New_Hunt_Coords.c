/*
 * Entry: 0051a5c8
 * Name: ScheduleGlue_Get_New_Hunt_Coords
 * Namespace: Global
 * Signature: int ScheduleGlue_Get_New_Hunt_Coords(VECTOR_3D param_1, int param_2, float * param_3, float * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
ScheduleGlue_Get_New_Hunt_Coords
          (VECTOR_3D param_1,int param_2,float *param_3,float *param_4,int param_5)

{
  matrix<unsigned_char> *pmVar1;
  uint uVar2;
  VECTOR_2D *pVVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  FindSendPoints *this;
  AiMission *pAVar8;
  AiPath *pAVar9;
  AOI *this_00;
  uint uVar10;
  uint uVar11;
  int local_1c;
  char local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar6 = rand();
  iVar6 = iVar6 % AI_map->AI_map_rows;
  iVar7 = rand();
  iVar7 = iVar7 % AI_map->AI_map_columns;
  pmVar1 = AI_map->hunt_map[param_5];
  if ((param_2 == 0) || (pmVar1->data[iVar6 + pmVar1->columns * iVar7] == '\0')) {
    if (loadedAIP == false) {
      loadedAIP = true;
      this = operator_new(0x20);
      if (this != (FindSendPoints *)0x0) {
        pAVar8 = AiMission::GetCurrent();
        FindSendPoints::FindSendPoints(this,pAVar8);
      }
    }
    local_1c = 0;
    do {
      local_1c = local_1c + 1;
      AddGridPoint(iVar7,iVar6);
      fVar4 = (float)(aiGridX0 + iVar7 * 8) * 10.0;
      fVar5 = (float)(aiGridZ0 + iVar6 * 8) * 10.0;
      uVar2 = sendPoints[grid_columns * iVar6 + iVar7];
      if (uVar2 != 0xffffffff) break;
      Trace("gridLayout == -1\n");
      if (last_hunt_x < 0) {
        last_hunt_x = grid_columns / 2;
        last_hunt_z = grid_rows / 2;
      }
      iVar7 = last_hunt_x;
      iVar6 = last_hunt_z;
    } while (local_1c < 2);
    last_hunt_z = iVar6;
    last_hunt_x = iVar7;
    if (uVar2 == 0) {
      sprintf(local_14,"bad_%d_%d",iVar7,iVar6);
      pAVar9 = operator_new(0x1c);
      if (pAVar9 == (AiPath *)0x0) {
        pAVar9 = (AiPath *)0x0;
      }
      else {
        pAVar9 = AiPath::AiPath(pAVar9,local_14,2);
      }
      pVVar3 = pAVar9->points;
      pVVar3->x = fVar4 + 2.0;
      pVVar3->z = fVar5 + 2.0;
      pAVar9->points[1].x = fVar4 + 6.0;
      pAVar9->points[1].z = fVar5 + 6.0;
      this_00 = operator_new(0x18);
      if (this_00 != (AOI *)0x0) {
        AOI::AOI(this_00,pAVar9,param_5,false,true,-1,0);
      }
    }
    else {
      uVar10 = rand();
      uVar10 = uVar10 % 5;
      uVar11 = 0;
      do {
        if ((uVar2 & 1 << ((byte)uVar10 & 0x1f)) != 0) break;
        uVar10 = uVar10 + 1;
        if (4 < uVar10) {
          uVar10 = 0;
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 < 5);
      if (uVar11 != 5) {
        *param_3 = layout[uVar11].rx * 8.0 + fVar4;
        *param_4 = layout[uVar11].rz * 8.0 + fVar5;
        pmVar1->data[iVar6 + pmVar1->columns * iVar7] = '\x01';
        return 1;
      }
    }
  }
  return 0;
}
