
void FUN_0045acc0(float param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 local_5c [4];
  undefined4 local_58;
  int local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 *local_48;
  undefined4 *local_44;
  int local_40;
  uint local_3c;
  uint local_38;
  int local_34;
  undefined4 *local_30;
  undefined1 local_2c [4];
  int local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  undefined4 *local_18;
  uint local_14;
  uint local_10;
  float *local_c;
  char local_6;
  char local_5;
  
  FUN_00447e20(local_2c);
  do {
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50(local_5c);
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) {
        return;
      }
      local_44 = (undefined4 *)FUN_00447e70();
      local_18 = local_44;
      FUN_00447e90();
      if (*(char *)(local_18 + 7) == '\0') break;
      FUN_0045b050(local_18,param_1);
LAB_0045ad89:
      local_6 = '\0';
      local_3c = get();
      for (local_14 = 0; local_14 < local_3c; local_14 = local_14 + 1) {
        piVar3 = (int *)FUN_0045bb80(local_14);
        local_1c = *piVar3;
        local_5 = '\0';
        local_38 = get();
        for (local_10 = 0; local_10 < local_38; local_10 = local_10 + 1) {
          local_c = (float *)FUN_0045ba30(local_10);
          local_c[6] = local_c[6] + param_1;
          if (local_c[6] < *(float *)(local_28 + 0x1b0) ||
              local_c[6] == *(float *)(local_28 + 0x1b0)) {
            *local_c = param_1 * local_c[3] + *local_c;
            local_c[1] = param_1 * local_c[4] + local_c[1];
            local_c[2] = param_1 * local_c[5] + local_c[2];
            local_c[8] = local_c[7] * param_1 + local_c[8];
          }
          else {
            *(undefined1 *)(local_c + 9) = 0;
            local_5 = '\x01';
          }
        }
        if (local_5 != '\0') {
          local_20 = 0;
          for (local_10 = 0; local_10 < local_38; local_10 = local_10 + 1) {
            local_50 = FUN_0045ba30(local_10);
            if (*(char *)(local_50 + 0x24) != '\0') {
              if (local_20 != local_10) {
                puVar4 = (undefined4 *)FUN_0045ba30(local_10);
                puVar5 = (undefined4 *)FUN_0045ba30(local_20);
                for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
                  *puVar5 = *puVar4;
                  puVar4 = puVar4 + 1;
                  puVar5 = puVar5 + 1;
                }
              }
              local_20 = local_20 + 1;
            }
          }
          FUN_0045ba10(local_20);
        }
        iVar1 = get();
        if (iVar1 == 0) {
          *(undefined1 *)(local_1c + 0x14) = 0;
          local_6 = '\x01';
        }
      }
      if (local_6 != '\0') {
        local_24 = 0;
        for (local_14 = 0; local_14 < local_3c; local_14 = local_14 + 1) {
          piVar3 = (int *)FUN_0045bb80(local_14);
          local_34 = *piVar3;
          if (*(char *)(local_34 + 0x14) == '\0') {
            FUN_0045b9c0();
            local_54 = local_34;
            local_40 = local_34;
            if (local_34 == 0) {
              local_58 = 0;
            }
            else {
              local_58 = FUN_00459990(1);
            }
          }
          else {
            if (local_24 != local_14) {
              puVar4 = (undefined4 *)FUN_0045bb80(local_14);
              puVar5 = (undefined4 *)FUN_0045bb80(local_24);
              *puVar5 = *puVar4;
            }
            local_24 = local_24 + 1;
          }
        }
        FUN_0045ba10(local_24);
      }
    }
    iVar1 = get();
    if (iVar1 != 0) goto LAB_0045ad89;
    local_48 = local_18;
    local_30 = local_18;
    if (local_18 == (undefined4 *)0x0) {
      local_4c = 0;
    }
    else {
      local_4c = (**(code **)*local_18)(1);
    }
  } while( true );
}

