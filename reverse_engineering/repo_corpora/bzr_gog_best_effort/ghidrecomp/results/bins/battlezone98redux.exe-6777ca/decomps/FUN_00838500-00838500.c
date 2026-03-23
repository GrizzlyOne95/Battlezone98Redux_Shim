
undefined4 FUN_00838500(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = FUN_00838733(param_1,1);
  bVar1 = FUN_00838733(param_1,2);
  FUN_0082cd58(param_1,(double)(iVar2 << (bVar1 & 0x1f)));
  return 1;
}

