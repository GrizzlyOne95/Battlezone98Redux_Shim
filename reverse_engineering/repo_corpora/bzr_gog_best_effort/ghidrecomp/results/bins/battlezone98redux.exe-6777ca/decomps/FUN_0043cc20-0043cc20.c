
void FUN_0043cc20(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int local_30;
  undefined4 local_2c;
  uint local_28;
  int local_24 [8];
  
  local_24[7] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24[0] = 0;
  local_24[1] = 0;
  local_24[2] = 0;
  local_24[3] = 0;
  local_24[4] = 0;
  local_24[5] = 0;
  local_24[6] = 0;
  local_2c = 0x24;
  local_28 = 0x82;
  uVar5 = *(uint *)(param_2 + 0x14) >> 0xc & 0xf;
  if ((*(int *)(param_2 + 0x58) == 0) || (iVar2 = ___scrt_is_ucrt_dll_in_use(param_1), iVar2 == 0))
  {
    if (uVar5 == 4) {
      local_28 = local_28 | 0x60;
    }
    else {
      local_28 = local_28 | 0x40;
    }
  }
  else if ((*(uint *)(param_2 + 0x14) & 0x800) == 0) {
    local_28 = local_28 | 0x20010;
  }
  else if (uVar5 == 4) {
    local_28 = local_28 | 0x60;
  }
  else {
    local_28 = local_28 | 0x40;
  }
  if (*(int *)(param_2 + 0x44) != -1) {
    local_28 = local_28 | 0x20;
  }
  local_28 = local_28 | 0x40000;
  *(uint *)(param_2 + 0x84) = local_28;
  local_30 = 1;
  bVar1 = false;
  if ((*(uint *)(param_2 + 0x70) & 0x200) == 0) {
    iVar2 = FUN_00481af0(param_2 + 4);
    *(int *)(param_2 + 0x50) = iVar2;
    *(int *)(param_2 + 0x4c) = iVar2;
    if (iVar2 == 0) {
      local_30 = 0;
    }
    else {
      uVar3 = FUN_00481a60(param_2 + 4);
      *(undefined4 *)(param_2 + 0x54) = uVar3;
      bVar1 = true;
      if (**(int **)(param_2 + 0x4c) == 0x30534147) {
        *(int *)(param_2 + 0x50) = *(int *)(param_2 + 0x50) + 0x1c;
      }
    }
  }
  if (local_30 != 0) {
    local_30 = FUN_0043c9d0(*(undefined4 *)(param_2 + 0x50),local_24 + 2,param_2 + 0x50,local_24);
  }
  if ((local_30 == 0) || (local_24[0] == 0)) {
    if (((*(uint *)(param_2 + 0x70) & 0x200) == 0) && ((bVar1 && (local_30 != 0)))) {
      FUN_00481990(param_2 + 4);
      *(undefined4 *)(param_2 + 0x4c) = 0;
      *(undefined4 *)(param_2 + 0x50) = 0;
    }
  }
  else {
    iVar2 = (**(code **)(**(int **)(param_1 + 0x18) + 0xc))
                      (*(undefined4 *)(param_1 + 0x18),&local_2c,param_2 + 0x7c,0);
    iVar4 = FUN_0043cb70(*(undefined4 *)(param_2 + 0x7c),*(undefined4 *)(param_2 + 0x50),local_24[0]
                        );
    if ((iVar4 != 0) && (iVar2 == 0)) {
      *(int *)(param_2 + 0x68) = local_24[0];
      *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(local_24[2] + 4);
      *(float *)(param_2 + 0x18) =
           (float)((double)*(int *)(local_24[2] + 4) +
                  (double)(&DAT_008a2fd0)[-(*(int *)(local_24[2] + 4) >> 0x1f)]);
      if ((*(int *)(param_2 + 0x58) != 0) &&
         (iVar2 = ___scrt_is_ucrt_dll_in_use(param_1), iVar2 != 0)) {
        (**(code **)**(undefined4 **)(param_2 + 0x7c))
                  (*(undefined4 *)(param_2 + 0x7c),&DAT_0086e978,param_2 + 0x80);
      }
      if ((*(uint *)(param_2 + 0x70) & 0x200) == 0) {
        FUN_00481990(param_2 + 4);
        *(undefined4 *)(param_2 + 0x4c) = 0;
        *(undefined4 *)(param_2 + 0x50) = 0;
      }
    }
  }
  FUN_0083e885();
  return;
}

