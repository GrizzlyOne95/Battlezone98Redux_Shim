
void __fastcall FUN_00609090(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined *local_88;
  char *local_80;
  char *local_78;
  char *local_68 [4];
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = *(int *)(param_1 + 0xc);
  iVar4 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
  iVar3 = *(int *)(iVar2 + 0x230);
  sprintf(local_58," UserProcess:");
  FUN_004b70f0();
  uVar5 = FUN_00462450();
  sprintf(local_58," ID (%s) Seqno (%d)",iVar4 + 8,uVar5);
  FUN_004b70f0();
  local_68[0] = " undeployed";
  local_68[1] = " deploying";
  local_68[2] = " deployed";
  local_68[3] = " undeploying";
  local_80 = local_68[*(int *)(iVar2 + 0x228)];
  pcVar6 = local_58;
  local_78 = pcVar6;
  do {
    cVar1 = *local_80;
    *local_78 = cVar1;
    local_80 = local_80 + 1;
    local_78 = local_78 + 1;
  } while (cVar1 != '\0');
  FUN_004b70f0();
  sprintf(local_58," Steer (%+.2f)",(double)*(float *)(iVar3 + 0xc4),pcVar6);
  FUN_004b70f0();
  sprintf(local_58," Braccel (%+.2f)",(double)*(float *)(iVar3 + 0xd0));
  FUN_004b70f0();
  sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)*(float *)(iVar3 + 200),
          (double)*(float *)(iVar3 + 0xcc));
  FUN_004b70f0();
  if (*(int *)(iVar3 + 0xd4) == 0) {
    local_88 = &DAT_008865a8;
  }
  else {
    local_88 = &DAT_00886520;
  }
  sprintf(local_58," Turbo (%s) Jump (%s)",local_88);
  FUN_004b70f0();
  (**(code **)(*(int *)(*(int *)(param_1 + 0xc) + 0x18) + 4))();
  sprintf(local_58," Team (%d)");
  FUN_004b70f0();
  FUN_004625b0();
  sprintf(local_58," Perceived Team (%d)");
  FUN_004b70f0();
  FUN_0083e885();
  return;
}

