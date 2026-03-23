
void __thiscall FUN_006cbf30(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_34 [44];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006ab750(param_1);
  FUN_006cffd0(param_2,&local_3c);
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    FUN_006b5120(local_3c,local_38);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_34,(ThrowInfo *)&DAT_008d8184);
  }
  FUN_0083e885();
  return;
}

