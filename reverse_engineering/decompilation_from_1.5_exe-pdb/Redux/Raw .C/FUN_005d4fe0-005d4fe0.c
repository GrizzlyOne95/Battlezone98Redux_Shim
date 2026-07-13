
bool FUN_005d4fe0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  bool bVar2;
  
  if (DAT_00918320 == 0) {
    bVar2 = false;
  }
  else {
    cVar1 = FUN_007c6c40(param_1,param_2,param_3);
    bVar2 = cVar1 != '\0';
  }
  return bVar2;
}

