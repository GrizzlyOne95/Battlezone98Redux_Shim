/*
 * Entry: 00518213
 * Name: ScheduleGlue_Get_New_Patrol_Coords
 * Namespace: Global
 * Signature: int ScheduleGlue_Get_New_Patrol_Coords(VECTOR_3D param_1, int param_2, int param_3, float * param_4, float * param_5, int param_6, goal_type_enum param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
ScheduleGlue_Get_New_Patrol_Coords
          (VECTOR_3D param_1,int param_2,int param_3,float *param_4,float *param_5,int param_6,
          goal_type_enum param_7)

{
  tag_team *ptVar1;
  void *pvVar2;
  uint uVar3;
  VECTOR_2D *pVVar4;
  float fVar5;
  float fVar6;
  tag_strategy_map *ptVar7;
  int iVar8;
  int iVar9;
  AiPath *pAVar10;
  AOI *this;
  uint uVar11;
  uint uVar12;
  int iVar13;
  char local_14 [12];
  uint local_8;
  
  ptVar7 = AI_map;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar9 = AI_map->gridside;
  iVar8 = PosX2POS((double)param_1.x);
  iVar13 = iVar8 / iVar9 + param_2;
  iVar8 = PosZ2POS((double)param_1.z);
  iVar9 = iVar8 / iVar9 + param_3;
  if ((((-1 < iVar13) && (-1 < iVar9)) && (iVar13 < ptVar7->AI_map_columns)) &&
     (iVar9 < ptVar7->AI_map_rows)) {
    ptVar1 = ptVar7->team[param_6];
    pvVar2 = (ptVar1->strategic_targets).grid[iVar9][iVar13];
    if (*(goal_type_enum *)((int)pvVar2 + 4) == param_7) {
      fVar5 = (float)(aiGridX0 + *(int *)((int)pvVar2 + 0x44) * 8) * 10.0;
      uVar3 = sendPoints[*(int *)((int)pvVar2 + 0x40) * grid_columns + *(int *)((int)pvVar2 + 0x44)]
      ;
      fVar6 = (float)(aiGridZ0 + *(int *)((int)pvVar2 + 0x40) * 8) * 10.0;
      if (uVar3 == 0xffffffff) {
        Trace("gridLayout == -1\n");
      }
      if (uVar3 == 0) {
        sprintf(local_14,"bad_%d_%d",*(undefined4 *)((int)pvVar2 + 0x44));
        pAVar10 = operator_new(0x1c);
        if (pAVar10 == (AiPath *)0x0) {
          pAVar10 = (AiPath *)0x0;
        }
        else {
          pAVar10 = AiPath::AiPath(pAVar10,local_14,2);
        }
        pVVar4 = pAVar10->points;
        pVVar4->x = fVar5 + 2.0;
        pVVar4->z = fVar6 + 2.0;
        pAVar10->points[1].x = fVar5 + 6.0;
        pAVar10->points[1].z = fVar6 + 6.0;
        this = operator_new(0x18);
        if (this != (AOI *)0x0) {
          AOI::AOI(this,pAVar10,ptVar1->team_ID,false,true,-1,0);
        }
      }
      else {
        uVar11 = rand();
        uVar11 = uVar11 % 5;
        uVar12 = 0;
        do {
          if ((uVar3 & 1 << ((byte)uVar11 & 0x1f)) != 0) break;
          uVar11 = uVar11 + 1;
          if (4 < uVar11) {
            uVar11 = 0;
          }
          uVar12 = uVar12 + 1;
        } while (uVar12 < 5);
        if (uVar12 != 5) {
          *param_4 = layout[uVar12].rx * 8.0 + fVar5;
          *param_5 = layout[uVar12].rz * 8.0 + fVar6;
          return 1;
        }
      }
    }
  }
  return 0;
}
