
undefined4 * __thiscall FUN_00592380(undefined4 *param_1,int param_2,undefined4 param_3,int param_4)

{
  longlong lVar1;
  undefined4 uVar2;
  
  *param_1 = Heap_Class<struct_Strip*,float>::vftable;
  if (param_4 == 0) {
    *(undefined1 *)(param_1 + 3) = 1;
    lVar1 = (ulonglong)(param_2 + 1) * 8;
    uVar2 = FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
    param_1[4] = uVar2;
  }
  else {
    *(undefined1 *)(param_1 + 3) = 0;
    param_1[4] = param_4;
  }
  param_1[2] = param_2;
  *(undefined4 *)param_1[4] = param_3;
  FUN_00592750();
  return param_1;
}

