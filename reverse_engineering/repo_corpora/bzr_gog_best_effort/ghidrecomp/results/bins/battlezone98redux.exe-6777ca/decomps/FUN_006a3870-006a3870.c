
void FUN_006a3870(undefined4 param_1,int *param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  int local_34;
  int local_30;
  undefined4 local_2c;
  int local_28;
  undefined1 local_24 [4];
  int local_20;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = DAT_00917a74;
  FID_conflict_begin(local_24);
  while( true ) {
    uVar2 = FID_conflict_end(local_3c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_18 = *piVar3;
    local_20 = 0;
    iVar4 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
    if (*(int *)(iVar4 + 0x14) == 0x53435250) {
      pfVar5 = (float *)(**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
      local_14 = *pfVar5;
      local_10 = pfVar5[1];
      local_c = pfVar5[2];
      local_20 = 1;
    }
    else {
      iVar4 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
      if (*(int *)(iVar4 + 0x14) == 0x53434156) {
        iVar4 = (**(code **)(*(int *)(local_18 + 0x18) + 4))();
        if (iVar4 == *param_2) {
          local_28 = FUN_0045bdf0();
          if (local_28 != 0) {
            pfVar5 = (float *)FUN_005c40b0();
            local_14 = *pfVar5;
            local_10 = pfVar5[1];
            local_c = pfVar5[2];
            if (0.0 < local_10) {
              local_20 = 3;
            }
          }
        }
      }
    }
    if (0 < local_20) {
      FUN_006a08c0((double)local_14,0,DAT_02c00ed8 + -1);
      local_30 = FUN_00453d10();
      FUN_006a0920((double)local_c,0,DAT_02c00a94 + -1);
      local_34 = FUN_00453d10();
      local_1c = *(int *)(*(int *)(param_2[0x20] + local_34 * 4) + local_30 * 4);
      *(int *)(local_1c + 0x68) = *(int *)(local_1c + 0x68) + local_20;
      *(undefined4 *)(local_1c + 0x6c) = 1;
      *(undefined4 *)(local_1c + 0x70) = 1;
    }
    FUN_0046b260(local_38,0);
  }
  FUN_006a1bc0(param_2,1);
  FUN_006a1bc0(param_2,0);
  FUN_0083e885();
  return;
}

