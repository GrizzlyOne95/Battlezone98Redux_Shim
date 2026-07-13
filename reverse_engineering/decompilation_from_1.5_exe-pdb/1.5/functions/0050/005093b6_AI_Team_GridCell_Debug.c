/*
 * Entry: 005093b6
 * Name: AI_Team_GridCell_Debug
 * Namespace: Global
 * Signature: void AI_Team_GridCell_Debug(tag_team * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AI_Team_GridCell_Debug(tag_team *param_1,int param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  char *pcVar3;
  char local_d0 [96];
  undefined1 local_70 [104];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_70;
  if ((((param_2 < 0) || (param_3 < 0)) || ((param_1->strategic_targets).grid_columns <= param_2))
     || ((param_1->strategic_targets).grid_rows <= param_3)) {
    pcVar3 = "Invalid Cell Number";
  }
  else {
    pvVar1 = (param_1->strategic_targets).grid[param_3][param_2];
    if (pvVar1 == (void *)0x0) {
      pcVar3 = "Invalid Cell: NULL Pointer";
    }
    else {
      sprintf(local_d0,"TEAM %d.  GRIDCELL ( %d, %d):");
      DebCons_PutString("");
      DebCons_PutString(local_d0);
      DebCons_PutString("");
      iVar2 = *(int *)((int)pvVar1 + 4);
      if (iVar2 == 0) {
        pcVar3 = "Goal Type: NO_GOAL";
      }
      else if (iVar2 == 1) {
        pcVar3 = "Goal Type: DEFEND_BASE";
      }
      else if (iVar2 == 2) {
        pcVar3 = "Goal Type: ATTACK_TROOPS";
      }
      else if (iVar2 == 3) {
        pcVar3 = "Goal Type: SEIGE";
      }
      else if (iVar2 == 4) {
        pcVar3 = "Goal Type: EXPLORATION";
      }
      else if (iVar2 == 5) {
        pcVar3 = "Goal Type: MANUALLY SCRIPTED";
      }
      else if (iVar2 == 6) {
        pcVar3 = "Goal Type: PERIMETER";
      }
      else {
        pcVar3 = "Goal Type: UNDEFINED";
      }
      sprintf(local_d0,pcVar3);
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Priority: %f",(double)*(float *)((int)pvVar1 + 0x1c));
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Threat: %d              Enemy Units:  %d",
              *(undefined4 *)((int)pvVar1 + 0x48),*(undefined4 *)((int)pvVar1 + 0x58));
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Our Units:  %d",*(undefined4 *)((int)pvVar1 + 0x50));
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Ground Strength: %d",*(undefined4 *)((int)pvVar1 + 0x54));
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Enemy Buildings: %f     Ours: %f",(double)*(float *)((int)pvVar1 + 0x60),
              (double)*(float *)((int)pvVar1 + 100));
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Scripted Value:  %d",*(undefined4 *)((int)pvVar1 + 0x68));
      DebCons_PutString(local_d0);
      sprintf(local_d0,"Distance from Base: %d",
              (param_1->strategic_targets).distance_from_base[param_3][param_2]);
      DebCons_PutString(local_d0);
      if ((param_1->strategic_targets).scouted[param_3][param_2] == 0) {
        pcVar3 = "UNEXPLORED";
      }
      else {
        pcVar3 = "SCOUTED";
      }
      sprintf(local_d0,pcVar3);
      DebCons_PutString(local_d0);
      if ((param_1->strategic_targets).base_location[param_3][param_2] != 0) {
        sprintf(local_d0,"IN BASE");
        DebCons_PutString(local_d0);
      }
      if (*(int *)((int)pvVar1 + 0x14) == 0) {
        sprintf(local_d0,"SQUAD: None");
      }
      else {
        sprintf(local_d0,"SQUAD: %d");
      }
      DebCons_PutString(local_d0);
      pcVar3 = "";
    }
  }
  DebCons_PutString(pcVar3);
  return;
}
