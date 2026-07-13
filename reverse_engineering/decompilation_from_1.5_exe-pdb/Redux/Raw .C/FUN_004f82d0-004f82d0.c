
void __thiscall FUN_004f82d0(int param_1,float param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 local_118 [64];
  undefined4 local_d8;
  int local_d4;
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  local_d4 = param_1;
  if (((*(int *)(param_1 + 0xe4) == 0) || (*(char *)(param_1 + 0xe0) != '\0')) ||
     (cVar1 = FUN_00611840(), cVar1 == '\0')) {
    if (0.0 < *(float *)(local_d4 + 0xc0)) {
      *(undefined4 *)(local_d4 + 0xc0) = 0;
    }
  }
  else if (0.0 < *(float *)(local_d4 + 0xc0)) {
    iVar2 = FUN_00417c80();
    if (*(int *)(*(int *)(local_d4 + 8) + 0x34) <= iVar2) {
      if (*(char *)(*(int *)(local_d4 + 8) + 0x58) != '\0') {
        FUN_0043a990(local_50);
        local_40 = 0x1000;
        FUN_0043a9e0(local_24);
        FUN_0043aa30(*(int *)(local_d4 + 8) + 0x58,*(undefined4 *)(local_d4 + 0x10),local_50,
                     local_24);
      }
      (**(code **)(**(int **)(local_d4 + 0xd8) + 0x18))(-*(int *)(*(int *)(local_d4 + 0xc) + 0x4c));
      puVar3 = (undefined4 *)
               FUN_0081fe60(local_118,*(int *)(local_d4 + 0x10) + 0x20,local_d4 + 0x28);
      puVar5 = local_90;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = local_90;
      puVar5 = local_d0;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      local_d8 = FUN_00586ff0(local_d0,*(undefined4 *)(local_d4 + 0x18));
      uVar4 = FUN_004da060(*(undefined4 *)(local_d4 + 0xe4));
      FUN_0056a490(uVar4);
    }
    *(undefined4 *)(local_d4 + 0xe4) = 0;
    *(undefined4 *)(local_d4 + 0xc4) = 0;
    *(undefined4 *)(local_d4 + 0xd0) = 0;
    *(float *)(local_d4 + 0xc0) =
         *(float *)(local_d4 + 0xc0) - *(float *)(*(int *)(local_d4 + 8) + 0x84);
  }
  *(undefined1 *)(local_d4 + 0xe0) = 0;
  FUN_0083e885();
  return;
}

