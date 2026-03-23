
undefined4 FUN_006dc3e0(longlong *param_1,byte *param_2,uint param_3)

{
  undefined4 uVar1;
  longlong lVar2;
  int local_8;
  
  if ((param_3 == 0) || (7 < param_3)) {
    *(undefined4 *)param_1 = 0;
    *(undefined4 *)((int)param_1 + 4) = 0;
    local_8 = 8;
    while (local_8 != 0) {
      local_8 = local_8 + -1;
      lVar2 = __allshl();
      *param_1 = lVar2 + (ulonglong)*param_2;
      param_2 = param_2 + 1;
    }
    uVar1 = 8;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

