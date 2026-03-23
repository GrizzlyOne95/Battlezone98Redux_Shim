
void FUN_00696610(int param_1,int param_2,int param_3)

{
  int iVar1;
  char local_d0 [200];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((((param_2 < 0) || (param_3 < 0)) || (*(int *)(param_1 + 0x7c) <= param_2)) ||
     (*(int *)(param_1 + 0x78) <= param_3)) {
    FUN_006a60f0();
  }
  else {
    iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + param_3 * 4) + param_2 * 4);
    if (iVar1 == 0) {
      FUN_006a60f0();
    }
    else {
      sprintf(local_d0,"TEAM %d.  GRIDCELL ( %d, %d):");
      FUN_006a60f0();
      FUN_006a60f0();
      FUN_006a60f0();
      switch(*(undefined4 *)(iVar1 + 4)) {
      case 0:
        sprintf(local_d0,"Goal Type: NO_GOAL");
        break;
      case 1:
        sprintf(local_d0,"Goal Type: DEFEND_BASE");
        break;
      case 2:
        sprintf(local_d0,"Goal Type: ATTACK_TROOPS");
        break;
      case 3:
        sprintf(local_d0,"Goal Type: SEIGE");
        break;
      case 4:
        sprintf(local_d0,"Goal Type: EXPLORATION");
        break;
      case 5:
        sprintf(local_d0,"Goal Type: MANUALLY SCRIPTED");
        break;
      case 6:
        sprintf(local_d0,"Goal Type: PERIMETER");
        break;
      default:
        sprintf(local_d0,"Goal Type: UNDEFINED");
      }
      FUN_006a60f0();
      sprintf(local_d0,"Priority: %f",(double)*(float *)(iVar1 + 0x1c));
      FUN_006a60f0();
      sprintf(local_d0,"Threat: %d              Enemy Units:  %d",*(undefined4 *)(iVar1 + 0x48));
      FUN_006a60f0();
      sprintf(local_d0,"Our Units:  %d");
      FUN_006a60f0();
      sprintf(local_d0,"Ground Strength: %d");
      FUN_006a60f0();
      sprintf(local_d0,"Enemy Buildings: %f     Ours: %f",(double)*(float *)(iVar1 + 0x60),
              (double)*(float *)(iVar1 + 100));
      FUN_006a60f0();
      sprintf(local_d0,"Scripted Value:  %d");
      FUN_006a60f0();
      sprintf(local_d0,"Distance from Base: %d");
      FUN_006a60f0();
      if (*(int *)(*(int *)(*(int *)(param_1 + 0x90) + param_3 * 4) + param_2 * 4) == 0) {
        sprintf(local_d0,"UNEXPLORED");
      }
      else {
        sprintf(local_d0,"SCOUTED");
      }
      FUN_006a60f0();
      if (*(int *)(*(int *)(*(int *)(param_1 + 0x84) + param_3 * 4) + param_2 * 4) != 0) {
        sprintf(local_d0,"IN BASE");
        FUN_006a60f0();
      }
      if (*(int *)(iVar1 + 0x14) == 0) {
        sprintf(local_d0,"SQUAD: None");
      }
      else {
        sprintf(local_d0,"SQUAD: %d");
      }
      FUN_006a60f0();
      FUN_006a60f0();
    }
  }
  FUN_0083e885();
  return;
}

