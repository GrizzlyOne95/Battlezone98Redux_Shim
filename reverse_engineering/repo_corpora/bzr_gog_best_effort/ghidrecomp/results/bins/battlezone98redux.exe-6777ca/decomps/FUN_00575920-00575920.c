
undefined1 *
FUN_00575920(undefined4 *param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_40 [16];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined4 local_20;
  int *local_1c;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b8e6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00428520(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_0073a6b0();
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  if (DAT_009180e4 == 0) {
    DAT_009180e4 = FID_conflict__Immortalize<class_std::_Generic_error_category>();
  }
  local_14[0x18] = 0;
  local_20 = FUN_007659f0();
  local_14[0x8d] = 0;
  *(undefined2 *)(local_14 + 0x28) = param_2;
  *(undefined4 *)(local_14 + 0x30) = *param_1;
  *(undefined4 *)(local_14 + 0x34) = param_1[1];
  *(undefined4 *)(local_14 + 0x38) = param_1[2];
  *(undefined4 *)(local_14 + 0x3c) = param_1[3];
  local_18 = (int *)FUN_00764760();
  uVar2 = (**(code **)(*local_18 + 0x38))(local_40);
  uVar1 = FUN_0056f780(uVar2);
  local_14[0x8e] = uVar1;
  *(undefined4 *)(local_14 + 0x50) = 0;
  *(undefined4 *)(local_14 + 0x40) = 0;
  *(undefined4 *)(local_14 + 0x44) = 0;
  *(undefined4 *)(local_14 + 0x4c) = 0;
  *(undefined4 *)(local_14 + 0x1c) = 0;
  *(undefined4 *)(local_14 + 0x20) = 0;
  puVar3 = (undefined4 *)FUN_00578b70(param_1);
  *puVar3 = local_14;
  puVar3 = (undefined4 *)FUN_00578cc0(&param_2);
  *puVar3 = local_14;
  FUN_00578af0(local_28,param_1);
  if (local_14[0x8e] == '\0') {
    FUN_00578af0(local_30,param_1);
  }
  DAT_00918128 = DAT_00918128 + 1;
  FID_conflict_operator_(param_3);
  *local_14 = 1;
  *(undefined4 *)(local_14 + 0x24) = 0;
  *(undefined4 *)(local_14 + 4) = 0;
  *(undefined4 *)(local_14 + 8) = 1;
  *(undefined4 *)(local_14 + 0xc) = 1000000;
  local_14[0x8c] = 0;
  *(undefined4 *)(local_14 + 0x90) = 0;
  *(undefined4 *)(local_14 + 0x94) = 0;
  *(undefined4 *)(local_14 + 0x6c) = 0;
  *(undefined4 *)(local_14 + 0x70) = 0;
  *(undefined4 *)(local_14 + 0x58) = 0;
  *(undefined4 *)(local_14 + 0x5c) = 0;
  *(undefined4 *)(local_14 + 0x60) = 0;
  *(undefined4 *)(local_14 + 100) = 0;
  local_14[0x68] = 0;
  FUN_00577900(param_4);
  *(undefined4 *)(local_14 + 0x1b0) = 0xffffffff;
  if (local_14[0x8e] == '\0') {
    local_1c = (int *)FUN_007647a0();
    (**(code **)(*local_1c + 0x18))(param_1);
  }
  uVar2 = FUN_00416410();
  uVar2 = FUN_0041f870(*(undefined2 *)(local_14 + 0x28),local_14[0x68],uVar2);
  uVar2 = FUN_0081e820("Added Player %s (ID %lu, Team %d) %ld Players Total\n",uVar2);
  FUN_0081e710(uVar2);
  ExceptionList = local_10;
  return local_14;
}

