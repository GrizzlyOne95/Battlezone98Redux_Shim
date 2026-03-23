
void __thiscall FUN_00512660(int param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  undefined1 local_54 [12];
  undefined8 local_48;
  int local_40;
  undefined8 local_3c;
  int local_34;
  float local_30;
  int local_2c;
  undefined1 local_25;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = *(int *)(param_1 + 0x15c);
  local_34 = *(int *)(param_1 + 0x150);
  *(int *)(param_1 + 0x15c) = *(int *)(param_1 + 0x15c) + 1;
  local_24 = param_1;
  if (local_40 != local_34) {
    local_25 = FUN_0048fca0(*(undefined4 *)(param_1 + 0x16c),*(undefined4 *)(param_1 + 0x174));
    for (local_2c = 0; local_2c < 0x40; local_2c = local_2c + 1) {
      uVar3 = FUN_008205a0(*(undefined4 *)(local_24 + 0x164));
      local_20 = (undefined4)((ulonglong)uVar3 >> 0x20);
      local_18 = (undefined4)uVar3;
      local_1c = 0;
      local_48 = uVar3;
      local_3c = uVar3;
      puVar2 = (undefined4 *)
               FUN_00439d00(local_54,*(undefined4 *)(local_24 + 0x16c),
                            *(undefined4 *)(local_24 + 0x170),*(undefined4 *)(local_24 + 0x174),
                            *(undefined4 *)(local_24 + 0x160),local_20,0,local_18);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      *param_2 = local_14;
      param_2[1] = local_10;
      param_2[2] = local_c;
      *(float *)(local_24 + 0x164) = *(float *)(local_24 + 0x164) + *(float *)(local_24 + 0x168);
      if (6.2831855 - *(float *)(local_24 + 0x168) * 0.5 <= *(float *)(local_24 + 0x164)) {
        local_30 = *(float *)(local_24 + 0x160);
        *(float *)(local_24 + 0x164) = *(float *)(local_24 + 0x164) - 6.2831855;
        *(float *)(local_24 + 0x160) = *(float *)(local_24 + 0x160) + *(float *)(local_24 + 0x154);
        *(float *)(local_24 + 0x168) =
             (local_30 / *(float *)(local_24 + 0x160)) * *(float *)(local_24 + 0x168);
      }
      cVar1 = FUN_0058fd90(*param_2,param_2[2],local_25);
      if (cVar1 != '\0') break;
    }
  }
  FUN_0083e885();
  return;
}

