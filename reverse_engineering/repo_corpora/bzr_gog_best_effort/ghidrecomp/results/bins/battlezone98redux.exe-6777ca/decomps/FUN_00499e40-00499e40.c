
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall FUN_00499e40(undefined4 param_1,int *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  size_t asStack_5c [4];
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined8 local_44;
  float local_3c;
  undefined1 *local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  uint local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_48 = param_1;
  iVar1 = *param_2;
  local_10 = iVar1;
  uStack_4c = 0x499e64;
  local_34 = (undefined1 *)(&local_48 + iVar1 * -3);
  local_20 = (undefined1 *)(&local_48 + iVar1 * -3);
  if (param_3 == 0) {
    asStack_5c[iVar1 * -3 + 4] = iVar1 * 0xc;
    asStack_5c[iVar1 * -3 + 3] = param_2[1];
    asStack_5c[iVar1 * -3 + 2] = (size_t)local_20;
    asStack_5c[iVar1 * -3 + 1] = 0x499ea5;
    memcpy((void *)asStack_5c[iVar1 * -3 + 2],(void *)asStack_5c[iVar1 * -3 + 3],
           asStack_5c[iVar1 * -3 + 4]);
    puVar3 = &local_48 + iVar1 * -3;
  }
  else {
    asStack_5c[iVar1 * -3 + 4] = param_3;
    asStack_5c[iVar1 * -3 + 3] = local_10;
    asStack_5c[iVar1 * -3 + 2] = param_2[1];
    asStack_5c[iVar1 * -3 + 1] = (size_t)local_20;
    asStack_5c[iVar1 * -3] = 0x499e8b;
    FUN_00820180();
    puVar3 = &local_48 + iVar1 * -3;
  }
  iVar1 = local_10;
  *(undefined4 *)((int)puVar3 + -4) = 0x499eb3;
  uVar4 = CONCAT44(local_44._4_4_,(undefined4)local_44);
  iVar1 = iVar1 * -8;
  local_38 = (undefined1 *)((int)puVar3 + iVar1);
  local_1c = (undefined1 *)((int)puVar3 + iVar1);
  for (local_14 = 0; local_14 < local_10; local_14 = local_14 + 1) {
    local_44 = uVar4;
    *(float **)((int)puVar3 + iVar1 + -4) = &local_3c;
    *(undefined4 *)((int)puVar3 + iVar1 + -8) = DAT_00917594;
    *(undefined1 **)((int)puVar3 + iVar1 + -0xc) = local_20 + local_14 * 0xc;
    *(undefined4 *)((int)puVar3 + iVar1 + -0x10) = 0x499eee;
    uVar4 = FUN_00497780();
    *(int *)(local_1c + local_14 * 8) = (int)uVar4;
    *(int *)(local_1c + local_14 * 8 + 4) = (int)((ulonglong)uVar4 >> 0x20);
    if (local_3c < 0.0) goto LAB_00499fdc;
  }
  for (local_c = param_2[5]; local_c < (uint)(param_2[4] * 0x18 + param_2[5]);
      local_c = local_c + 0x18) {
    uVar2 = (uint)*(ushort *)(*(int *)(local_c + 0x14) + -2 + *(int *)(local_c + 0x10) * 2);
    local_28 = *(undefined4 *)(local_1c + uVar2 * 8);
    local_24 = *(undefined4 *)(local_1c + uVar2 * 8 + 4);
    for (local_18 = 0; local_18 < *(uint *)(local_c + 0x10); local_18 = local_18 + 1) {
      uVar2 = (uint)*(ushort *)(*(int *)(local_c + 0x14) + local_18 * 2);
      local_30 = *(undefined4 *)(local_1c + uVar2 * 8);
      local_2c = *(undefined4 *)(local_1c + uVar2 * 8 + 4);
      local_44 = uVar4;
      *(undefined4 *)((int)puVar3 + iVar1 + -4) = 0;
      *(undefined4 *)((int)puVar3 + iVar1 + -8) = param_4;
      *(undefined4 *)((int)puVar3 + iVar1 + -0xc) = local_2c;
      *(undefined4 *)((int)puVar3 + iVar1 + -0x10) = local_30;
      *(undefined4 *)((int)puVar3 + iVar1 + -0x14) = local_24;
      *(undefined4 *)((int)puVar3 + iVar1 + -0x18) = local_28;
      *(undefined4 *)((int)puVar3 + iVar1 + -0x1c) = DAT_00917580;
      *(undefined4 *)((int)puVar3 + iVar1 + -0x20) = 0x499fc6;
      FUN_0068af40();
      local_28 = local_30;
      local_24 = local_2c;
      uVar4 = local_44;
    }
  }
LAB_00499fdc:
  uStack_4c = 0x499fe9;
  local_44 = uVar4;
  FUN_0083e885();
  return;
}

