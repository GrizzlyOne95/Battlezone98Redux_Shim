
void FUN_0043a170(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_4c [12];
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00437b00();
  if (DAT_00915594 != 0) {
    if ((param_1 != 0) && (iVar2 = ___scrt_is_ucrt_dll_in_use(DAT_00915594), iVar2 != 0)) {
      FUN_0043a7e0();
    }
    FUN_0043c1c0();
    local_40 = FUN_00439e60();
    local_14 = (float)*(double *)(local_40 + 0x160);
    local_10 = (float)*(double *)(local_40 + 0x168);
    local_c = (float)*(double *)(local_40 + 0x170);
    local_3c = 0;
    local_38 = 0;
    local_34 = FUN_0043bc50();
LAB_0043a220:
    if (local_34 != 0) {
      local_30 = local_34;
      local_34 = FUN_00439cc0(local_34);
      if ((*(int *)(local_30 + 0x58) == 0) ||
         (iVar2 = FUN_00439cd0(*(undefined4 *)(local_30 + 0x78),*(undefined4 *)(local_30 + 0x58)),
         iVar2 != 0)) {
        if ((*(uint *)(local_30 + 0x70) & 8) == 0) {
          if ((*(int *)(local_30 + 0x58) != 0) && ((*(uint *)(local_30 + 0x14) & 0x800) == 0)) {
            puVar3 = (undefined4 *)FUN_0062e120(local_4c,*(undefined4 *)(local_30 + 0x58));
            local_2c = *puVar3;
            local_28 = puVar3[1];
            local_24 = puVar3[2];
            local_20 = local_2c;
            local_1c = local_28;
            local_18 = local_24;
            cVar1 = FUN_0043a0c0(local_14,local_10,local_c,local_2c,local_28,local_24);
            if (cVar1 != '\0') {
              if ((*(uint *)(local_30 + 0x70) & 4) != 0) {
                FUN_0043aec0(local_30);
              }
              if (*(int *)(local_30 + 0x3c) != 1) {
                FUN_0043b010(local_30);
              }
              goto LAB_0043a220;
            }
            if (local_3c == *(int *)(DAT_00915594 + 4)) {
              if ((*(uint *)(local_30 + 0x70) & 4) != 0) {
                FUN_0043aec0(local_30);
              }
              if (*(int *)(local_30 + 0x3c) != 1) {
                FUN_0043b010(local_30);
              }
              goto LAB_0043a220;
            }
            iVar2 = FUN_0043c070(local_30);
            if (*(int *)(local_30 + 0x38) < iVar2) {
              if ((*(uint *)(local_30 + 0x70) & 4) != 0) {
                FUN_0043aec0(local_30);
              }
              if (*(int *)(local_30 + 0x3c) != 1) {
                FUN_0043b010(local_30);
              }
              goto LAB_0043a220;
            }
            local_3c = local_3c + 1;
          }
          if ((*(uint *)(local_30 + 0x70) & 4) != 0) {
            if (*(int *)(local_30 + 0x3c) == 2) {
              if (*(char *)(local_30 + 0x6c) == '\0') {
                FUN_0043aec0(local_30);
              }
              else {
                *(undefined1 *)(local_30 + 0x6c) = 0;
              }
            }
            iVar2 = FUN_00439ec0(local_30);
            if (iVar2 == 0) {
              if (*(int *)(local_30 + 0x2c) == 0) {
                if (*(int *)(local_30 + 0x3c) == 1) {
                  *(uint *)(local_30 + 0x70) = *(uint *)(local_30 + 0x70) & 0xfffffffb;
                }
                else {
                  FUN_0043b010(local_30);
                }
                goto LAB_0043a220;
              }
              iVar2 = (**(code **)(local_30 + 0x2c))(local_30,3);
              if (iVar2 == 0) goto LAB_0043a220;
            }
            if (*(int *)(local_30 + 0x58) != 0) {
              *(uint *)(local_30 + 0x14) = *(uint *)(local_30 + 0x14) | 0x200;
            }
            *(float *)(local_30 + 0x1c) = (float)*(int *)(local_30 + 0x40);
            if (*(int *)(local_30 + 0x44) == 1) {
              if (*(int *)(local_30 + 0x44) == 2) {
                iVar2 = rand();
                *(float *)(local_30 + 0x18) =
                     *(float *)(local_30 + 0x18) * *(float *)(&DAT_008e7604 + (iVar2 % 10) * 4);
                *(uint *)(local_30 + 0x14) = *(uint *)(local_30 + 0x14) | 0x40;
              }
            }
            else {
              *(float *)(local_30 + 0x18) = (float)*(int *)(local_30 + 0x48);
            }
            if ((*(int *)(local_30 + 0x28) == 0) ||
               (iVar2 = (**(code **)(local_30 + 0x28))(local_30,2), iVar2 != 0)) {
              FUN_0043b720(local_30,0);
              local_38 = local_38 + 1;
            }
            goto LAB_0043a220;
          }
          FUN_0043ad20(local_30,1);
        }
      }
      else {
        FUN_0043b010(local_30);
      }
      goto LAB_0043a220;
    }
    if ((local_38 != 0) && (param_1 != 0)) {
      FUN_0043c6e0(DAT_00915594);
    }
  }
  FUN_0083e885();
  return;
}

