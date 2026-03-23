
void __fastcall FUN_004adcc0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  float local_4c;
  undefined4 local_48;
  undefined4 *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 *local_38;
  uint local_34;
  undefined4 *local_30;
  undefined4 *local_2c;
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
  local_24 = param_1;
  if ((*(int *)(param_1 + 0xec) == 0) || (*(int *)(*(int *)(param_1 + 0xf4) + 0x84) == 4)) {
    if (*(int *)(param_1 + 0xfc) != 0) {
      local_44 = *(undefined4 **)(param_1 + 0xfc);
      local_30 = local_44;
      if (local_44 == (undefined4 *)0x0) {
        local_3c = 0;
      }
      else {
        local_3c = (**(code **)*local_44)(1);
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x298) = 0;
    local_34 = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10;
    local_48 = *(undefined4 *)(param_1 + 0xec);
    *(undefined4 *)(param_1 + 0xec) = 0;
    if (*(int *)(param_1 + 0xfc) != 0) {
      local_38 = *(undefined4 **)(param_1 + 0xfc);
      local_2c = local_38;
      if (local_38 == (undefined4 *)0x0) {
        local_40 = 0;
      }
      else {
        local_40 = (**(code **)*local_38)(1);
      }
      *(undefined4 *)(local_24 + 0xfc) = 0;
    }
    memset((void *)(*(int *)(local_24 + 0x230) + 0xc4),0,0x2c);
    if (*(int *)(local_24 + 0x1a0) != 0) {
      FUN_004a7800();
    }
    cVar1 = FUN_004b9830();
    if (cVar1 == '\0') {
      if (local_34 == 0) {
        fVar5 = (float10)FUN_004a7890();
        local_4c = (float)fVar5;
        if (*(float *)(local_24 + 0x288) * 2.0 + -1.0 < local_4c) goto LAB_004adf0f;
      }
      puVar2 = (undefined4 *)FUN_004795e0(local_58,*(int *)(local_24 + 0xf4) + 0x20);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00439d00(local_64,*(undefined4 *)(local_24 + 300),
                            *(undefined4 *)(local_24 + 0x130),*(undefined4 *)(local_24 + 0x134),
                            0x42480000,local_20,local_1c,local_18);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      local_28 = FUN_004adb00(local_48,&local_14);
      if ((local_34 != 0) && (iVar3 = FUN_00572a70(), iVar3 != 0)) {
        *(undefined1 *)(local_28 + 0x20) = 1;
      }
      uVar4 = (**(code **)(*(int *)(local_28 + 0x18) + 0x30))(0);
      FUN_004376c0(PTR_s_bail_wav_008e7c9c,uVar4);
    }
  }
LAB_004adf0f:
  FUN_0083e885();
  return;
}

