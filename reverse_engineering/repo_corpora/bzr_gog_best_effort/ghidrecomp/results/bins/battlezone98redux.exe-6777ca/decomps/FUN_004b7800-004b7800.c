
void FUN_004b7800(undefined2 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  ushort local_8;
  
  iVar2 = FUN_005771b0(param_1);
  if (iVar2 != 0) {
    for (local_8 = 0x200; (uint)local_8 < DAT_008e80b4 + 0x200U; local_8 = local_8 + 1) {
      uVar3 = FUN_00575510(local_8);
      cVar1 = FUN_0041fc90(iVar2,uVar3);
      if (cVar1 == '\0') {
        uVar3 = get();
        uVar3 = FUN_004bb390(local_8,uVar3);
        FUN_004b8fa0(param_1,uVar3);
      }
    }
  }
  return;
}

