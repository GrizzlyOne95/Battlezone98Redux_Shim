
undefined4 FUN_00705ea0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  cVar1 = FUN_006ba470(&stack0x00000008);
  uVar3 = FUN_006ba6b0(&stack0x00000008,&stack0x0000000c);
  iVar2 = (int)((ulonglong)uVar3 >> 0x20);
  if (((cVar1 == '~') && (iVar2 == 0)) && ((uint)uVar3 < 0x7e)) {
    make_error_code(param_1,0xe);
  }
  else if (((cVar1 == '\x7f') && (iVar2 == 0)) && ((uint)uVar3 < 0x10000)) {
    make_error_code(param_1,0xe);
  }
  else {
    lVar4 = __aullshr();
    if (lVar4 == 0) {
      FUN_006ab750();
    }
    else {
      make_error_code(param_1,0xf);
    }
  }
  return param_1;
}

