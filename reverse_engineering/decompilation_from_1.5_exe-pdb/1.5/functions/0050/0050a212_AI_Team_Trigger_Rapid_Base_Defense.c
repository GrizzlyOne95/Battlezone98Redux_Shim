/*
 * Entry: 0050a212
 * Name: AI_Team_Trigger_Rapid_Base_Defense
 * Namespace: Global
 * Signature: void AI_Team_Trigger_Rapid_Base_Defense(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, GameObject * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_Trigger_Rapid_Base_Defense
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
          GameObject *param_7)

{
  uchar uVar1;
  tag_team *ptVar2;
  Mapgrid_Goal *pMVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  void **ppvVar8;
  uint uVar9;
  float fVar10;
  Mapgrid_Goal *pMVar11;
  int iVar12;
  
  bVar4 = false;
  ptVar2 = AI_map->team[param_1];
  if (ptVar2 == (tag_team *)0x0) {
    return;
  }
  if (param_4 != 0) {
    param_2 = param_2 / AI_map->gridside;
    param_3 = param_3 / AI_map->gridside;
  }
  if (-1 < param_5) {
    iVar5 = param_5 / AI_map->gridside;
    iVar6 = param_6 / AI_map->gridside;
    if ((iVar5 == param_2) && (iVar6 == param_3)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    uVar7 = iVar5 - param_2;
    uVar9 = (int)uVar7 >> 0x1f;
    if ((1 < (int)((uVar7 ^ uVar9) - uVar9)) ||
       (uVar7 = iVar6 - param_3, uVar9 = (int)uVar7 >> 0x1f, 1 < (int)((uVar7 ^ uVar9) - uVar9))) {
      param_6 = -1;
      param_5 = -1;
    }
  }
  pMVar3 = (ptVar2->strategic_targets).grid[param_3][param_2];
  if ((pMVar3->_padding_ != 6) && (pMVar3->_padding_ != 1)) {
    return;
  }
  fVar10 = Get_Time();
  pMVar3->last_rapid_base_defense_time = fVar10;
  if (pMVar3->rapid_defense_state == 0) goto LAB_0050a3ad;
  if (pMVar3->rapid_defense_state != 2) {
    return;
  }
  uVar1 = pMVar3->neighbor_flags;
  if (uVar1 == '\x01') {
    ppvVar8 = (ptVar2->strategic_targets).grid[param_3 + -1];
    iVar6 = 0x80;
    iVar5 = 1;
LAB_0050a309:
    iVar12 = 1;
    pMVar11 = ppvVar8[param_2 + -1];
  }
  else {
    if (uVar1 == '\b') {
      ppvVar8 = (ptVar2->strategic_targets).grid[param_3];
      iVar6 = 0x10;
      iVar5 = 0;
      goto LAB_0050a309;
    }
    if (uVar1 == ' ') {
      ppvVar8 = (ptVar2->strategic_targets).grid[param_3 + 1];
      iVar6 = 4;
      iVar5 = -1;
      goto LAB_0050a309;
    }
    if (uVar1 == '\x02') {
      ppvVar8 = (ptVar2->strategic_targets).grid[param_3 + -1];
      iVar6 = 0x40;
      iVar5 = 1;
LAB_0050a34c:
      iVar12 = 0;
      pMVar11 = ppvVar8[param_2];
    }
    else {
      if (uVar1 == '@') {
        ppvVar8 = (ptVar2->strategic_targets).grid[param_3 + 1];
        iVar6 = 2;
        iVar5 = -1;
        goto LAB_0050a34c;
      }
      if (uVar1 == '\x04') {
        ppvVar8 = (ptVar2->strategic_targets).grid[param_3 + -1];
        iVar6 = 0x20;
        iVar5 = 1;
      }
      else if (uVar1 == '\x10') {
        ppvVar8 = (ptVar2->strategic_targets).grid[param_3];
        iVar6 = 8;
        iVar5 = 0;
      }
      else {
        if (uVar1 != 0x80) goto LAB_0050a3ad;
        ppvVar8 = (ptVar2->strategic_targets).grid[param_3 + 1];
        iVar6 = 1;
        iVar5 = -1;
      }
      iVar12 = -1;
      pMVar11 = ppvVar8[param_2 + 1];
    }
  }
  AI_Team_UnRecruit_Single_Neighbor(ptVar2,pMVar11,iVar12,iVar5,iVar6);
LAB_0050a3ad:
  pMVar3->rapid_defense_state = 1;
  AI_Team_Recruit_Neighbors(ptVar2,pMVar3,param_5,param_6,param_7);
  if ((bVar4) && ((tag_squad *)pMVar3->_padding_ != (tag_squad *)0x0)) {
    Squad_Send_Rapid_Base_Defense((tag_squad *)pMVar3->_padding_,pMVar3,param_7);
  }
  return;
}
