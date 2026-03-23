
void __fastcall FUN_005c0d90(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  undefined8 local_5c;
  float local_54;
  int local_50;
  undefined8 local_4c;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 *local_38;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar3 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  local_38 = (undefined4 *)(iVar3 + 0xc4);
  *(undefined4 *)(iVar3 + 0xd0) = 0;
  *local_38 = 0;
  *(undefined4 *)(iVar3 + 200) = 0;
  *(undefined4 *)(iVar3 + 0xd4) = 0;
  local_34 = *(int *)(param_1 + 8) + -1;
  local_30 = param_1;
  switch(*(int *)(param_1 + 8)) {
  case 1:
    uVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(local_30 + 0x18) = uVar4;
    if ((*(int *)(local_30 + 0x18) == 0) || (iVar3 = FUN_00417ca0(), iVar3 == 0)) {
      *(undefined4 *)(local_30 + 0xc) = 0xd;
    }
    else {
      uVar1 = FUN_005c16a0();
      *(undefined1 *)(local_30 + 0xc4) = uVar1;
      if (*(char *)(local_30 + 0xc4) != '\0') {
        cVar2 = FUN_005bf890(*(undefined4 *)(local_30 + 0x10));
        if (cVar2 != '\0') {
          *(undefined4 *)(local_30 + 0xc) = 5;
          break;
        }
      }
      *(undefined4 *)(local_30 + 0xc) = 0xf;
    }
    break;
  case 2:
  case 0xf:
    uVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(local_30 + 0x18) = uVar4;
    if (*(int *)(local_30 + 0x18) == 0) {
      *(undefined4 *)(local_30 + 0xc) = 0xd;
    }
    else {
      puVar5 = (undefined4 *)FUN_00465e60(local_68,*(undefined4 *)(local_30 + 0x18),0x40000000);
      local_20 = *puVar5;
      local_1c = puVar5[1];
      local_18 = puVar5[2];
      *(undefined4 *)(local_30 + 0x28) = local_20;
      *(undefined4 *)(local_30 + 0x2c) = local_1c;
      *(undefined4 *)(local_30 + 0x30) = local_18;
      if (*(int *)(local_30 + 8) == 0xf) {
        local_50 = FUN_004778f0(*(undefined4 *)(local_30 + 0x10));
        local_3c = ((float)local_50 * 6.2831855) / 16.0;
        local_5c = FUN_008205a0(local_3c);
        local_24 = (undefined4)((ulonglong)local_5c >> 0x20);
        local_2c = (undefined4)local_5c;
        local_28 = 0;
        local_4c = local_5c;
        puVar5 = (undefined4 *)
                 FUN_00439d00(local_74,*(undefined4 *)(local_30 + 0x28),
                              *(undefined4 *)(local_30 + 0x2c),*(undefined4 *)(local_30 + 0x30),
                              *(undefined4 *)(local_30 + 0xf0),local_2c,0,local_24);
        local_14 = *puVar5;
        local_10 = puVar5[1];
        local_c = puVar5[2];
        *(undefined4 *)(local_30 + 0x28) = local_14;
        *(undefined4 *)(local_30 + 0x2c) = local_10;
        *(undefined4 *)(local_30 + 0x30) = local_c;
      }
      FUN_005bf850(*(undefined4 *)(local_30 + 0x10));
      FUN_00601070();
    }
    break;
  case 5:
    fVar6 = (float10)FUN_00822d80();
    local_54 = (float)fVar6;
    *(float *)(local_30 + 0x120) = local_54 + 15.0;
    fVar6 = (float10)FUN_00822d80();
    local_40 = (float)fVar6;
    *(float *)(local_30 + 0x108) = local_40 + 3.0;
    break;
  case 0xe:
    FUN_005bf850(*(undefined4 *)(param_1 + 0x10));
    fVar6 = (float10)FUN_00822d80();
    local_44 = (float)fVar6;
    *(float *)(local_30 + 0x120) = local_44 + 5.0;
  }
  FUN_0083e885();
  return;
}

