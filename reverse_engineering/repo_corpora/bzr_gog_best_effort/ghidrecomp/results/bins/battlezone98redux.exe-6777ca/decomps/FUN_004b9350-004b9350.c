
void FUN_004b9350(undefined2 param_1,byte *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 local_134 [64];
  undefined1 local_f4 [4];
  undefined1 local_f0 [4];
  undefined1 local_ec [4];
  undefined1 local_e8 [4];
  undefined1 local_e4 [4];
  int *local_e0;
  undefined4 local_dc;
  int *local_d8;
  undefined4 local_d4;
  int *local_d0;
  CMetaFileDC *local_cc;
  int local_c8;
  undefined8 local_c4;
  int local_bc;
  undefined4 local_b8;
  byte *local_b4;
  undefined4 local_b0;
  byte *local_ac;
  byte local_a5;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined2 local_98;
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849a4f;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_b4 = param_2;
  local_ac = param_2;
  if ((param_2[0x14] & 0x80) == 0) {
    if (*param_2 < 0x1c) {
      FUN_007d6a70("Not enough data to create object",local_14);
      goto LAB_004b972f;
    }
    local_a4 = *(undefined4 *)(param_2 + 6);
    local_a0 = *(undefined4 *)(param_2 + 10);
    local_9c = *(undefined4 *)(param_2 + 0xe);
    local_98 = *(undefined2 *)(param_2 + 0x12);
    local_b0 = *(undefined4 *)(param_2 + 2);
    local_a5 = param_2[1];
  }
  else {
    if (*param_2 < 0x15) {
      FUN_007d6a70("Not enough data to create object",local_14);
      goto LAB_004b972f;
    }
    local_a4 = *(undefined4 *)(param_2 + 6);
    local_a0 = *(undefined4 *)(param_2 + 10);
    local_9c = *(undefined4 *)(param_2 + 0xe);
    local_98 = *(undefined2 *)(param_2 + 0x12);
    local_b0 = *(undefined4 *)(param_2 + 2);
    local_a5 = param_2[1];
  }
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0046b370(local_e4,&local_b0);
  local_b8 = *puVar2;
  uVar3 = FID_conflict_begin(local_e8);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    iVar4 = FUN_00422150();
    if (*(int *)(iVar4 + 4) != 0) goto LAB_004b972f;
  }
  puVar2 = (undefined4 *)FUN_0046b370(local_f0,&local_b0);
  local_b8 = *puVar2;
  FUN_0044eb20(&local_d4,&local_b0);
  uVar3 = FUN_0044eaa0(local_f4);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    FUN_007d6a70("Reviving id %08x\n",local_b0);
    local_dc = local_d4;
    FUN_0044eac0(local_ec,local_d4);
  }
  if ((local_ac[0x14] & 0x80) == 0) {
    local_c4 = FUN_0045c0c0(local_b4 + 0x14);
  }
  else {
    local_c4 = FUN_004b76c0(local_ac[0x14]);
  }
  local_c8 = FUN_004e0f70(local_c4);
  if (local_c8 == 0) {
    FUN_007d6a70("Unknown game object class \"%8s\"",&local_c4);
  }
  else {
    puVar2 = (undefined4 *)FUN_006253c0(local_134,local_a4,local_a0,local_9c,local_98);
    puVar5 = local_94;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar2 = local_94;
    puVar5 = local_54;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    local_bc = FUN_004e1190(local_54,(int)(uint)local_a5 >> 2 & 0xf,0,0xffffffff,0);
    local_cc = operator_new(0x18);
    local_8 = 0;
    if (local_cc == (CMetaFileDC *)0x0) {
      local_d0 = (int *)0x0;
    }
    else {
      local_d0 = (int *)CMetaFileDC::CMetaFileDC(local_cc);
    }
    local_e0 = local_d0;
    local_8 = 0xffffffff;
    local_d8 = local_d0;
    uVar3 = FUN_0045ca50(local_bc);
    (**(code **)(*local_d8 + 0x18))(uVar3);
    FUN_004b7f00(param_1);
    *(undefined4 *)(local_bc + 0x7c) = local_b0;
    FUN_004b7f20();
  }
LAB_004b972f:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

