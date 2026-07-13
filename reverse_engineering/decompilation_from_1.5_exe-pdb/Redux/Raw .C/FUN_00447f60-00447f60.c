
void FUN_00447f60(undefined4 *param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 uStack_c;
  
  uVar1 = *(undefined8 *)(param_2 + 0x28);
  uVar2 = *(undefined8 *)(param_2 + 0x30);
  uVar3 = *(undefined8 *)(param_2 + 0x38);
  local_20 = (undefined4)uVar1;
  *param_1 = local_20;
  uStack_1c = (undefined4)((ulonglong)uVar1 >> 0x20);
  param_1[1] = uStack_1c;
  local_18 = (undefined4)uVar2;
  param_1[2] = local_18;
  uStack_14 = (undefined4)((ulonglong)uVar2 >> 0x20);
  param_1[3] = uStack_14;
  local_10 = (undefined4)uVar3;
  param_1[4] = local_10;
  uStack_c = (undefined4)((ulonglong)uVar3 >> 0x20);
  param_1[5] = uStack_c;
  FUN_0083e885();
  return;
}

