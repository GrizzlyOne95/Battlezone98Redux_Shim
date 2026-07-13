
void __thiscall FUN_0047b9d0(int param_1,float param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 local_128 [64];
  float local_e8;
  float local_e4;
  int local_e0;
  float local_dc;
  int local_d8;
  int local_d4;
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_d4 = param_1;
  if ((*(char *)(param_1 + 0xc4) == '\0') ||
     (((*(int *)(*(int *)(param_1 + 0xc) + 0x4c) != 0 && (iVar2 = FUN_00417c80(), iVar2 < 1)) ||
      (cVar1 = FUN_00611840(), cVar1 == '\0')))) {
    if (*(int *)(local_d4 + 200) != 0) {
      uVar3 = FUN_0043ac70(0,*(undefined4 *)(local_d4 + 0x10));
      *(undefined4 *)(local_d4 + 200) = uVar3;
      if (*(int *)(local_d4 + 200) != 0) {
        FUN_0043aaa0(*(undefined4 *)(local_d4 + 200));
        *(undefined4 *)(local_d4 + 200) = 0;
      }
    }
    if (*(int *)(local_d4 + 0xd0) != 0) {
      if (*(int *)(*(int *)(*(int *)(local_d4 + 0xd0) + 0xc) + 0xc) == 0x4245414d) {
        FUN_0047b760();
      }
      *(undefined4 *)(local_d4 + 0xd0) = 0;
    }
  }
  else {
    local_dc = param_2;
    if (0 < *(int *)(*(int *)(local_d4 + 0xc) + 0x4c)) {
      iVar2 = FUN_00417c80();
      local_e4 = (float)iVar2 / (float)*(int *)(*(int *)(local_d4 + 0xc) + 0x4c);
      if (local_e4 < local_dc) {
        local_dc = local_e4;
      }
    }
    if ((*(char *)(*(int *)(local_d4 + 8) + 0x58) != '\0') && (*(int *)(local_d4 + 200) == 0)) {
      FUN_0043a990(local_50);
      local_40 = 0x1001;
      FUN_0043a9e0(local_24);
      local_18 = 1;
      if ((*(uint *)(*(int *)(local_d4 + 0x18) + 0x14) & 0x10) != 0) {
        local_20 = 0x41;
      }
      uVar3 = FUN_0043aa30(*(int *)(local_d4 + 8) + 0x58,*(undefined4 *)(local_d4 + 0x10),local_50,
                           local_24);
      *(undefined4 *)(local_d4 + 200) = uVar3;
    }
    puVar4 = (undefined4 *)FUN_0081fe60(local_128,*(int *)(local_d4 + 0x10) + 0x20,local_d4 + 0x28);
    puVar5 = local_d0;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar4 = local_d0;
    puVar5 = local_90;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    local_e8 = (float)*(int *)(*(int *)(local_d4 + 0xc) + 0x4c) * param_2 +
               *(float *)(local_d4 + 0xcc);
    local_e0 = (int)local_e8;
    *(float *)(local_d4 + 0xcc) = local_e8 - (float)local_e0;
    (**(code **)(**(int **)(local_d4 + 0xc0) + 0x18))(-local_e0);
    cVar1 = FUN_004b9830();
    if ((cVar1 == '\0') &&
       ((*(int *)(local_d4 + 0xd0) == 0 ||
        ((*(uint *)(*(int *)(*(int *)(local_d4 + 0xd0) + 0x14) + 0x14) & 0x200) != 0)))) {
      uVar3 = FUN_00586ff0(local_90,*(undefined4 *)(local_d4 + 0x18));
      *(undefined4 *)(local_d4 + 0xd0) = uVar3;
      if (*(int *)(*(int *)(*(int *)(local_d4 + 0xd0) + 0xc) + 0xc) == 0x4245414d) {
        for (local_d8 = 0; local_d8 < 5; local_d8 = local_d8 + 1) {
          iVar2 = FUN_00417ca0();
          if (iVar2 != 0) {
            iVar2 = local_d8;
            FUN_00417ca0(local_d8);
            iVar2 = FUN_00417f60(iVar2);
            if (iVar2 == local_d4) {
              FUN_0047b740(local_d8);
              break;
            }
          }
        }
      }
      *(float *)(*(int *)(local_d4 + 0xd0) + 0x10) = local_dc - param_2;
    }
  }
  if ((*(int *)(local_d4 + 0xc0) == 0) || (cVar1 = FUN_004b9830(), cVar1 == '\0')) {
    *(undefined1 *)(local_d4 + 0xc4) = 0;
  }
  FUN_0083e885();
  return;
}

