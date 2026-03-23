
void FUN_006a44d0(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined8 local_48;
  float local_40;
  float local_3c;
  int local_38;
  int local_34;
  int local_30;
  float local_2c;
  float local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  int local_18;
  float local_14 [3];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = *param_1;
  local_1c = param_2 * 0x80 + DAT_0093101c;
  local_48 = 0;
  strncpy((char *)&local_48,(char *)(local_1c + 0x40),8);
  local_34 = FUN_004e0f70((undefined4)local_48,local_48._4_4_);
  local_30 = (int)(param_3 + (param_3 >> 0x1f & 0xfU)) >> 4;
  local_38 = (int)(param_4 + (param_4 >> 0x1f & 0xfU)) >> 4;
  FUN_00696610(*(undefined4 *)(DAT_00920f04 + (char)param_1[4] * 4),local_30,local_38,
               (int)(param_1[6] + (param_1[6] >> 0x1f & 0xfU)) >> 4);
  fVar3 = (float10)FUN_006a0980(param_3);
  local_40 = (float)fVar3;
  local_20 = *(uint *)(local_1c + 0x24) >> 0x12 & 0xf;
  local_14[0] = local_40 + ((float)local_20 + 0.0) * 0.5 * 5.0;
  local_14[1] = 0.0;
  local_3c = local_40;
  fVar3 = (float10)FUN_006a09b0(param_4);
  local_2c = (float)fVar3;
  local_24 = *(uint *)(local_1c + 0x24) >> 0x16 & 0xf;
  local_14[2] = local_2c + ((float)local_24 + 0.0) * 0.5 * 5.0;
  local_28 = local_2c;
  iVar1 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
  if (*(int *)(iVar1 + 0x14) == 0x434e5354) {
    uVar2 = FUN_00462490();
    FUN_0049cf90(local_14,uVar2);
  }
  FUN_004dbe70(0x15,local_14,local_34,local_34 >> 0x1f);
  FUN_0083e885();
  return;
}

