
void __fastcall FUN_004b0ff0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_5c [12];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  undefined8 local_3c;
  undefined8 local_34;
  float local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = *(int *)(param_1 + 8) + -1;
  local_24 = param_1;
  local_3c = CONCAT44(local_3c._4_4_,(undefined4)local_3c);
  local_34 = CONCAT44(local_34._4_4_,(undefined4)local_34);
  switch(local_28) {
  case 0:
    *(undefined4 *)(param_1 + 0xc) = 6;
    local_3c = CONCAT44(local_3c._4_4_,(undefined4)local_3c);
    local_34 = CONCAT44(local_34._4_4_,(undefined4)local_34);
    break;
  case 1:
    FUN_00601070();
    local_3c = CONCAT44(local_3c._4_4_,(undefined4)local_3c);
    local_34 = CONCAT44(local_34._4_4_,(undefined4)local_34);
    break;
  case 2:
    FUN_006028d0();
    local_3c = CONCAT44(local_3c._4_4_,(undefined4)local_3c);
    local_34 = CONCAT44(local_34._4_4_,(undefined4)local_34);
    break;
  case 5:
    fVar4 = (float10)FUN_00822d80();
    local_40 = (float)fVar4;
    *(float *)(local_24 + 0x120) = local_40 + 10.0;
    uVar1 = FUN_00462630(*(undefined4 *)(local_24 + 0x14));
    *(undefined4 *)(local_24 + 0x18) = uVar1;
    if (*(int *)(local_24 + 0x18) == 0) {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_24 + 0x10) + 0x18) + 0xc))();
      *(undefined4 *)(local_24 + 0x28) = *puVar2;
      *(undefined4 *)(local_24 + 0x2c) = puVar2[1];
      *(undefined4 *)(local_24 + 0x30) = puVar2[2];
      local_3c = CONCAT44(local_3c._4_4_,(undefined4)local_3c);
      local_34 = CONCAT44(local_34._4_4_,(undefined4)local_34);
    }
    else {
      fVar4 = (float10)FUN_00462470();
      local_44 = (float)fVar4;
      local_4c = local_44 + 10.0;
      fVar4 = (float10)FUN_00462470();
      local_48 = (float)fVar4;
      local_50 = local_4c + local_48;
      iVar3 = rand();
      local_2c = ((float)iVar3 * 6.2831855) / 32767.0;
      local_3c = FUN_008205a0(local_2c);
      local_18 = (undefined4)((ulonglong)local_3c >> 0x20);
      local_20 = (undefined4)local_3c;
      local_1c = 0;
      local_34 = local_3c;
      puVar2 = (undefined4 *)
               (**(code **)(*(int *)(*(int *)(local_24 + 0x18) + 0x18) + 0xc))
                         (local_50,local_20,0,local_18);
      puVar2 = (undefined4 *)FUN_00439d00(local_5c,*puVar2,puVar2[1],puVar2[2]);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      *(undefined4 *)(local_24 + 0x28) = local_14;
      *(undefined4 *)(local_24 + 0x2c) = local_10;
      *(undefined4 *)(local_24 + 0x30) = local_c;
    }
  }
  FUN_0083e885();
  return;
}

