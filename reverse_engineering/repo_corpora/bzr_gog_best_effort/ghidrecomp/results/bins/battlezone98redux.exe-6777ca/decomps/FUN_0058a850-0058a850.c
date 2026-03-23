
undefined4 FUN_0058a850(void)

{
  int iVar1;
  undefined4 uVar2;
  char *in_stack_00000014;
  undefined4 extraout_var;
  
  if (((in_stack_00000014 != (char *)0x0) && (*in_stack_00000014 != '\0')) &&
     (iVar1 = _stricmp(in_stack_00000014,"NULL"), iVar1 != 0)) {
    uVar2 = FUN_0044e4c0(in_stack_00000014,extraout_var);
    return uVar2;
  }
  return 0;
}

