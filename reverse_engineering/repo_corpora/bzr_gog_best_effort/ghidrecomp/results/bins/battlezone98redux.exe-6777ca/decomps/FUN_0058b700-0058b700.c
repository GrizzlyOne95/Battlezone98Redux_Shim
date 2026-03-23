
void __thiscall FUN_0058b700(int param_1,float param_2)

{
  int iVar1;
  uint uVar2;
  float fVar3;
  uint local_24;
  float local_20;
  int local_1c;
  double *local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = *(uint *)(param_1 + 0x28);
  local_1c = param_1;
  do {
    while( true ) {
      if (local_24 == *(uint *)(local_1c + 0x2c)) {
        FUN_0083e885();
        return;
      }
      local_18 = (double *)(local_1c + 0x30 + local_24 * 0x30);
      local_24 = local_24 + 1;
      if (0xff < local_24) {
        local_24 = 0;
      }
      *(float *)((int)local_18 + 0x24) = *(float *)((int)local_18 + 0x24) + param_2;
      if (*(float *)(local_1c + 0x303c) <= *(float *)((int)local_18 + 0x24) &&
          *(float *)((int)local_18 + 0x24) != *(float *)(local_1c + 0x303c)) break;
LAB_0058b7e6:
      *(float *)((int)local_18 + 0x1c) = *(float *)((int)local_18 + 0x1c) - param_2 * 9.8;
      local_20 = param_2;
      iVar1 = FUN_00784620(*(undefined4 *)local_18,*(undefined4 *)((int)local_18 + 4),
                           *(undefined4 *)(local_18 + 1),*(undefined4 *)((int)local_18 + 0xc),
                           *(undefined4 *)(local_18 + 2),*(undefined4 *)((int)local_18 + 0x14),
                           *(undefined4 *)(local_18 + 3),*(undefined4 *)((int)local_18 + 0x1c),
                           *(undefined4 *)(local_18 + 4),&local_20,&local_14);
      if (iVar1 == 0) {
        *local_18 = (double)(*(float *)(local_18 + 3) * param_2) + *local_18;
        local_18[1] = (double)(*(float *)((int)local_18 + 0x1c) * param_2) + local_18[1];
        local_18[2] = (double)(*(float *)(local_18 + 4) * param_2) + local_18[2];
      }
      else {
        *local_18 = (double)(*(float *)(local_18 + 3) * local_20) + *local_18;
        local_18[1] = (double)(*(float *)((int)local_18 + 0x1c) * local_20) + local_18[1];
        local_18[2] = (double)(*(float *)(local_18 + 4) * local_20) + local_18[2];
        fVar3 = *(float *)(local_18 + 3) * local_14 + *(float *)((int)local_18 + 0x1c) * local_10 +
                *(float *)(local_18 + 4) * local_c;
        *(float *)(local_18 + 3) = *(float *)(local_18 + 3) * 0.5 - fVar3 * local_14;
        *(float *)((int)local_18 + 0x1c) = *(float *)((int)local_18 + 0x1c) * 0.5 - fVar3 * local_10
        ;
        *(float *)(local_18 + 4) = *(float *)(local_18 + 4) * 0.5 - fVar3 * local_c;
        *local_18 = (double)((param_2 - local_20) * *(float *)(local_18 + 3)) + *local_18;
        local_18[1] = (double)((param_2 - local_20) * *(float *)((int)local_18 + 0x1c)) +
                      local_18[1];
        local_18[2] = (double)((param_2 - local_20) * *(float *)(local_18 + 4)) + local_18[2];
      }
    }
    *(float *)((int)local_18 + 0x24) =
         *(float *)((int)local_18 + 0x24) - *(float *)(local_1c + 0x303c);
    iVar1 = *(int *)(local_18 + 5);
    *(int *)(local_18 + 5) = iVar1 + 1;
    if (iVar1 + 1 < *(int *)(local_1c + 0x3034)) goto LAB_0058b7e6;
    uVar2 = *(int *)(local_1c + 0x28) + 1;
    *(uint *)(local_1c + 0x28) = uVar2;
    if (0xff < uVar2) {
      *(undefined4 *)(local_1c + 0x28) = 0;
    }
  } while( true );
}

