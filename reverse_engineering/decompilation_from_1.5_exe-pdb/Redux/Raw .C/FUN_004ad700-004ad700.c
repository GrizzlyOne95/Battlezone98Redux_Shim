
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004ad700(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_cc [24];
  undefined1 local_b4 [12];
  int local_a8;
  undefined4 local_a4;
  undefined4 *local_a0;
  int local_9c;
  undefined4 *local_98;
  int local_94;
  undefined4 local_90 [10];
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
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
  local_94 = param_1;
  if (*(int *)(param_1 + 0xec) != 0) {
    if (param_1 == DAT_00917afc) {
      iVar1 = FUN_004a7850();
      if (iVar1 != 0) {
        iVar1 = FUN_00572a70();
        if (iVar1 == 0) goto LAB_004ada1a;
      }
    }
    FUN_0047c210(local_94);
    *(undefined4 *)(local_94 + 0xec) = 0;
    if (*(int *)(local_94 + 0xfc) != 0) {
      local_a0 = *(undefined4 **)(local_94 + 0xfc);
      local_98 = local_a0;
      if (local_a0 == (undefined4 *)0x0) {
        local_a4 = 0;
      }
      else {
        local_a4 = (**(code **)*local_a0)(1);
      }
      *(undefined4 *)(local_94 + 0xfc) = 0;
    }
    memset((void *)(*(int *)(local_94 + 0x230) + 0xc4),0,0x2c);
    if (*(int *)(local_94 + 0x1a0) != 0) {
      FUN_004a7800();
    }
    if (local_94 == DAT_00917afc) {
      FUN_00621790();
      FUN_0061a000();
      FUN_0061cf30(*(undefined4 *)(local_94 + 0xf0));
      _DAT_009198e4 = 1;
      iVar1 = FUN_00572a70();
      if (iVar1 != 0) {
        FUN_00572ad0();
      }
    }
    puVar2 = (undefined4 *)
             FUN_0062e1b0(local_b4,*(undefined4 *)(*(int *)(local_94 + 0x230) + 0xfc),
                          *(undefined4 *)(local_94 + 0xf4));
    local_50 = *puVar2;
    local_4c = puVar2[1];
    local_48 = puVar2[2];
    local_14 = local_50;
    local_10 = local_4c;
    local_c = local_48;
    puVar2 = (undefined4 *)FUN_0081fd40(local_cc,&local_50,*(int *)(local_94 + 0xf4) + 0x20);
    local_44 = *puVar2;
    uStack_40 = puVar2[1];
    local_3c = puVar2[2];
    uStack_38 = puVar2[3];
    local_34 = puVar2[4];
    uStack_30 = puVar2[5];
    local_2c = local_44;
    local_28 = uStack_40;
    local_24 = local_3c;
    local_20 = uStack_38;
    local_1c = local_34;
    local_18 = uStack_30;
    if (*(int *)(*(int *)(local_94 + 0xf8) + 0x30c) != 0) {
      puVar2 = (undefined4 *)(*(int *)(local_94 + 0xf4) + 0x20);
      puVar3 = local_90;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      local_68 = CONCAT44(uStack_40,local_44);
      local_60 = CONCAT44(uStack_38,local_3c);
      local_58 = CONCAT44(uStack_30,local_34);
      FUN_004cb7b0(local_90,0);
    }
    local_9c = 10;
    while( true ) {
      local_a8 = local_9c;
      if (local_9c == 0) break;
      local_9c = local_9c + -1;
      FUN_004927d0(&local_44,local_94 + 300,0);
    }
    local_9c = local_9c + -1;
    FUN_004db4f0(0);
    FUN_004376c0("squish.wav",*(undefined4 *)(*(int *)(local_94 + 0x230) + 0xfc),0);
    *(undefined4 *)(local_94 + 0x298) = 0;
  }
LAB_004ada1a:
  FUN_0083e885();
  return;
}

