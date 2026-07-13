
void __fastcall FUN_005fa020(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  char *pcVar4;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  int local_b4;
  int local_b0;
  undefined *local_ac;
  int *local_a8;
  int *local_a4;
  int local_a0;
  undefined *local_9c;
  char *local_98;
  char *local_94;
  float *local_90;
  int local_8c;
  char local_85;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  char *local_68 [4];
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_84 = param_1;
  local_b4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0x30))();
  local_90 = (float *)(*(int *)(*(int *)(local_84 + 0x34) + 0x230) + 0xc4);
  sprintf(local_58," UnitProcess:");
  FUN_004b70f0();
  uVar1 = FUN_00462450();
  sprintf(local_58," ID (%s) Seqno (%d)",local_b4 + 8,uVar1);
  FUN_004b70f0();
  fVar3 = (float10)FUN_00822d80();
  sprintf(local_58," Time (%.2f)",(double)fVar3);
  FUN_004b70f0();
  sprintf(local_58," State (%s)");
  FUN_004b70f0();
  sprintf(local_58," SaveState (%s)");
  FUN_004b70f0();
  sprintf(local_58," Priority (%d)");
  FUN_004b70f0();
  local_68[0] = " undeployed";
  local_68[1] = " deploying";
  local_68[2] = " deployed";
  local_68[3] = " undeploying";
  local_98 = local_68[*(int *)(*(int *)(local_84 + 0x34) + 0x228)];
  pcVar4 = local_58;
  local_94 = pcVar4;
  do {
    local_85 = *local_98;
    *local_94 = local_85;
    local_98 = local_98 + 1;
    local_94 = local_94 + 1;
  } while (local_85 != '\0');
  FUN_004b70f0();
  sprintf(local_58," Steer (%+.2f)",(double)*local_90,pcVar4);
  FUN_004b70f0();
  sprintf(local_58," Braccel (%+.2f)",(double)local_90[3]);
  FUN_004b70f0();
  sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)local_90[1],(double)local_90[2]);
  FUN_004b70f0();
  if (local_90[5] == 0.0) {
    local_ac = &DAT_008865a8;
  }
  else {
    local_ac = &DAT_00886520;
  }
  if (local_90[4] == 0.0) {
    local_9c = &DAT_008865a8;
  }
  else {
    local_9c = &DAT_00886520;
  }
  sprintf(local_58," Turbo (%s) Jump (%s)",local_9c);
  FUN_004b70f0();
  (**(code **)(*(int *)(*(int *)(local_84 + 0x34) + 0x18) + 4))();
  sprintf(local_58," Team (%d)");
  FUN_004b70f0();
  FUN_004625b0();
  sprintf(local_58," Perceived Team (%d)");
  FUN_004b70f0();
  local_8c = FUN_00462630();
  if (local_8c != 0) {
    local_a0 = FUN_004623e0();
    if (local_a0 != 0) {
      sprintf(local_58," Who (%s)");
      FUN_004b70f0();
    }
    local_a8 = DAT_00917554;
    local_c8 = DAT_00917574;
    uVar1 = DAT_00917564;
    puVar2 = (undefined4 *)(**(code **)(*(int *)(local_8c + 0x18) + 0xc))(pcVar4,DAT_00917564);
    local_80 = *puVar2;
    local_7c = puVar2[1];
    local_78 = puVar2[2];
    (**(code **)(*local_a8 + 0x24))(local_80,local_78,&local_cc);
    FUN_0068af40(DAT_00917580,local_c8,uVar1,local_cc,local_c4,DAT_0091755c);
  }
  local_8c = FUN_00462630();
  if (local_8c != 0) {
    local_b0 = FUN_004623e0();
    if (local_b0 != 0) {
      sprintf(local_58," Save Who (%s)");
      FUN_004b70f0();
    }
    uVar1 = DAT_00917564;
    local_a4 = DAT_00917554;
    local_b8 = DAT_00917574;
    puVar2 = (undefined4 *)(**(code **)(*(int *)(local_8c + 0x18) + 0xc))();
    local_74 = *puVar2;
    local_70 = puVar2[1];
    local_6c = puVar2[2];
    (**(code **)(*local_a4 + 0x24))(local_74,local_6c,&local_c0,&local_bc);
    FUN_0068af40(DAT_00917580,local_b8,uVar1,local_c0,local_bc,DAT_0091755c,0);
  }
  if (*(int *)(local_84 + 0x38) != 0) {
    (**(code **)(**(int **)(local_84 + 0x38) + 0x20))();
  }
  FUN_0083e885();
  return;
}

