
undefined4 * __thiscall FUN_006a0fa0(undefined4 *param_1,int param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084faa8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006a0de0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = UnitAttachment::vftable;
  memset(param_1 + 1,0,0x6c);
  param_1[1] = param_2;
  uVar2 = FUN_00477590(param_2);
  param_1[2] = uVar2;
  iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
  uVar2 = FUN_006a0a20(iVar3);
  param_1[3] = uVar2;
  uVar1 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
  *(undefined1 *)(param_1 + 5) = uVar1;
  if (*(int *)(iVar3 + 0x14) == 0x54554700) {
    local_20 = 2;
  }
  else {
    local_20 = 3;
  }
  param_1[0x16] = local_20;
  uVar1 = FUN_006a0f70(param_1 + 1);
  *(undefined1 *)(param_1 + 9) = uVar1;
  if ((DAT_00920f04 != 0) && (-1 < *(char *)(param_1 + 5))) {
    *(int *)(&DAT_02ce9b0c + *(char *)(param_1 + 5) * 0x1e0) =
         *(int *)(&DAT_02ce9b0c + *(char *)(param_1 + 5) * 0x1e0) + 1;
    FUN_0069fff0(*(undefined2 *)(param_1[3] + 0x5a),*(undefined1 *)(param_1 + 5));
    if (((&DAT_02ce9b18)[*(char *)(param_1 + 5) * 0x1e0] != '\0') &&
       (*(int *)(*(int *)(&DAT_00930fc0 + *(char *)(param_1 + 5) * 4) +
                (uint)*(ushort *)(param_1[3] + 0x5a) * 4) == 0)) {
      *(int *)(*(int *)(&DAT_00930fc0 + *(char *)(param_1 + 5) * 4) +
              (uint)*(ushort *)(param_1[3] + 0x5a) * 4) =
           *(int *)(*(int *)(&DAT_00930fc0 + *(char *)(param_1 + 5) * 4) +
                   (uint)*(ushort *)(param_1[3] + 0x5a) * 4) + 1;
    }
    if (*(char *)(param_1 + 9) == '\0') {
      FUN_0068fac0(param_1 + 1,0);
    }
  }
  ExceptionList = local_10;
  return param_1;
}

