
void FUN_006a1d40(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_30 [4];
  int local_2c;
  undefined4 *local_28;
  float local_24;
  float local_20;
  int *local_1c;
  float local_14;
  float local_10;
  int local_c;
  int local_8;
  
  DAT_00931018 = DAT_02ce99c0;
  DAT_00931020 = DAT_02cd9984;
  DAT_009310ac = DAT_02ce99a0;
  DAT_00931024 = DAT_02ce99c4;
  local_8 = 0;
  FUN_0042d8c0();
  do {
    FID_conflict_begin();
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') {
LAB_006a1de6:
      if (local_8 != 0) {
        local_20 = **(float **)(local_8 + 8);
        local_24 = *(float *)(*(int *)(local_8 + 8) + 4);
        local_14 = local_24;
        local_10 = local_20;
        for (local_c = 1; local_c < *(int *)(local_8 + 4); local_c = local_c + 1) {
          local_28 = (undefined4 *)(*(int *)(local_8 + 8) + local_c * 8);
          local_2c = *(int *)(local_8 + 8) + 4 + local_c * 8;
          fVar4 = (float10)FUN_00456080(local_10,*local_28);
          local_10 = (float)fVar4;
          fVar4 = (float10)FUN_00456080(local_14);
          local_14 = (float)fVar4;
          fVar4 = (float10)FUN_0044fb20(local_20);
          local_20 = (float)fVar4;
          fVar4 = (float10)FUN_0044fb20(local_24);
          local_24 = (float)fVar4;
        }
        floor((double)local_10 * 0.2);
        uVar2 = FUN_0083f040();
        DAT_00931018 = FUN_0043d130(DAT_00931018,uVar2);
        floor((double)local_14 * 0.2);
        uVar2 = FUN_0083f040();
        DAT_00931020 = FUN_0043d130(DAT_00931020,uVar2);
        ceil((double)local_20 * 0.2);
        uVar2 = FUN_0083f040();
        DAT_009310ac = FUN_0046b550(DAT_009310ac,uVar2);
        ceil((double)local_24 * 0.2);
        uVar2 = FUN_0083f040();
        iVar3 = FUN_0046b550(DAT_00931024,uVar2);
        DAT_00931018 = ((int)(DAT_00931018 + (DAT_00931018 >> 0x1f & 0xfU)) >> 4) << 4;
        DAT_009310ac = ((int)(DAT_009310ac + 0xf + (DAT_009310ac + 0xf >> 0x1f & 0xfU)) >> 4) << 4;
        DAT_00931020 = ((int)(DAT_00931020 + (DAT_00931020 >> 0x1f & 0xfU)) >> 4) << 4;
        DAT_00931024 = ((int)(iVar3 + 0xf + (iVar3 + 0xf >> 0x1f & 0xfU)) >> 4) << 4;
      }
      return;
    }
    local_1c = (int *)FUN_0042de50();
    local_1c = (int *)*local_1c;
    if (((char)local_1c[2] == '\0') && (*(char *)((int)local_1c + 9) == '\0')) {
      local_8 = *local_1c;
      goto LAB_006a1de6;
    }
    FUN_00438c10(local_30,0);
  } while( true );
}

