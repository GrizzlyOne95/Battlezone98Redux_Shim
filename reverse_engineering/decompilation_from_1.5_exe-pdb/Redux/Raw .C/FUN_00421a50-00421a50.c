
undefined4 __fastcall FUN_00421a50(int *param_1)

{
  char cVar1;
  int iVar2;
  int in_stack_ffffffec;
  undefined4 local_10 [2];
  int *local_8;
  
  if (param_1[0x14] != 0) {
    local_8 = param_1;
    iVar2 = eof(in_stack_ffffffec);
    local_10[0] = (**(code **)(*local_8 + 0xc))();
    eof(iVar2);
    cVar1 = eq_int_type(&stack0xffffffec,local_10);
    if ((cVar1 == '\0') && (iVar2 = fflush((FILE *)local_8[0x14]), iVar2 < 0)) {
      return 0xffffffff;
    }
  }
  return 0;
}

