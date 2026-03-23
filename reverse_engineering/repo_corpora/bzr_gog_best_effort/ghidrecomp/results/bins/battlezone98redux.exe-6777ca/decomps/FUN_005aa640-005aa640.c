
void __fastcall FUN_005aa640(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_b4 [24];
  float local_9c;
  float local_98;
  int local_94;
  float local_90;
  int local_8c;
  int *local_88;
  undefined4 local_84 [10];
  undefined8 local_5c;
  undefined8 local_54;
  undefined8 local_4c;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_88 = param_1;
  FUN_0062de40(param_1[0x37],0x200);
  puVar1 = (undefined4 *)FUN_0081fd40(local_b4,local_88[0x36] + 8,local_88[0x37] + 0x20);
  local_38 = *puVar1;
  uStack_34 = puVar1[1];
  local_30 = puVar1[2];
  uStack_2c = puVar1[3];
  local_28 = puVar1[4];
  uStack_24 = puVar1[5];
  puVar1 = (undefined4 *)(local_88[0x37] + 0x20);
  puVar3 = local_84;
  local_20 = local_38;
  local_1c = uStack_34;
  local_18 = local_30;
  local_14 = uStack_2c;
  local_10 = local_28;
  local_c = uStack_24;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_5c = CONCAT44(uStack_34,local_38);
  local_54 = CONCAT44(uStack_2c,local_30);
  local_4c = CONCAT44(uStack_24,local_28);
  if (*(int *)(local_88[0x38] + 0x144) == 0) {
    if ((DAT_00917a48 == 0) || (*(float *)(local_88[0x36] + 0x14) <= 3.0)) {
      if (DAT_00917a4c != 0) {
        FUN_004cb7b0(local_84,0);
      }
    }
    else {
      FUN_004cb7b0(local_84,0);
    }
  }
  else {
    (**(code **)(**(int **)(local_88[0x38] + 0x144) + 8))(0);
  }
  local_8c = (int)(*(float *)(local_88[0x36] + 0x14) * 10.0);
  while( true ) {
    local_94 = local_8c;
    if (local_8c == 0) break;
    local_8c = local_8c + -1;
    fVar4 = (float10)FUN_004464c0();
    local_98 = (float)fVar4;
    local_44 = local_98 * 20.0 + (float)local_88[0x45];
    fVar4 = (float10)FUN_004464c0();
    local_9c = (float)fVar4;
    local_40 = local_9c * 15.0 + (float)local_88[0x46] + 5.0;
    fVar4 = (float10)FUN_004464c0();
    local_90 = (float)fVar4;
    local_3c = local_90 * 20.0 + (float)local_88[0x47];
    FUN_0058b650(&local_38,&local_44);
  }
  local_8c = local_8c + -1;
  FUN_00492640(local_88[0x37],local_88 + 0x45,0);
  (**(code **)(*local_88 + 0x10))();
  FUN_0083e885();
  return;
}

