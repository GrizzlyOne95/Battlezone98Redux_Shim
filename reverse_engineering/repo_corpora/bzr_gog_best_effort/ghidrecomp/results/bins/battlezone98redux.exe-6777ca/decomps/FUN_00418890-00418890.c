
bool FUN_00418890(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  
  FID_conflict_operator_(param_2);
  local_1c = 0;
  local_10 = -1;
  local_14 = 1;
  local_20 = 0;
  local_18 = 0;
  uVar2 = FUN_0041f870(&local_1c,&local_10,&local_14,&local_20,&local_18);
  uVar2 = FUN_006218c0(uVar2);
  *(undefined4 *)(local_c + 0x18) = uVar2;
  *(undefined4 *)(local_c + 0x1c) = param_3;
  *(int *)(local_c + 0x20) = local_14 - local_10;
  *(int *)(local_c + 0x24) = local_10 << 0x10;
  *(undefined1 *)(local_c + 0x28) = (undefined1)local_18;
  *(int *)(local_c + 0x2c) = local_1c << 0x10;
  *(int *)(local_c + 0x2c) = *(int *)(local_c + 0x2c) - local_10;
  *(int *)(local_c + 0x2c) = *(int *)(local_c + 0x2c) << 1;
  *(int *)(local_c + 0x2c) = *(int *)(local_c + 0x2c) / *(int *)(local_c + 0x20);
  *(int *)(local_c + 0x2c) = *(int *)(local_c + 0x2c) + -0x10000;
  *(undefined4 *)(local_c + 0x30) = local_20;
  cVar1 = FUN_004187f0();
  if ((cVar1 != '\0') && (*(int *)(local_c + 0x18) != 0)) {
    FUN_00421e00(local_24,param_2);
    uVar2 = FID_conflict_begin(local_28);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      **(undefined4 **)(local_c + 0x18) = 0;
    }
    else {
      iVar3 = FUN_00421ea0();
      **(undefined4 **)(local_c + 0x18) = *(undefined4 *)(iVar3 + 0x18);
    }
  }
  return *(int *)(local_c + 0x18) != 0;
}

