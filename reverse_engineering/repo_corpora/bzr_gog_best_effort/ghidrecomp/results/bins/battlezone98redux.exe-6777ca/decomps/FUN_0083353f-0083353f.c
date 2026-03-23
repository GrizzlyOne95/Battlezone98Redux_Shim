
undefined4 FUN_0083353f(undefined4 param_1)

{
  int iVar1;
  char *_Str;
  FILE *pFVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = FUN_0082c8f6(param_1);
  FUN_0082c82c(param_1,0xffffd8ee,"tostring");
  iVar4 = 1;
  if (0 < iVar1) {
    do {
      FUN_0082cdd2(param_1,0xffffffff);
      FUN_0082cdd2(param_1,iVar4);
      FUN_0082c585(param_1,1,1);
      _Str = (char *)FUN_0082d377(param_1,0xffffffff,0);
      if (_Str == (char *)0x0) {
        uVar3 = FUN_0082bc39(param_1,"\'tostring\' must return a string to \'print\'");
        return uVar3;
      }
      if (1 < iVar4) {
        pFVar2 = __iob_func();
        fputs("\t",pFVar2 + 1);
      }
      pFVar2 = __iob_func();
      fputs(_Str,pFVar2 + 1);
      FUN_0082d226(param_1,0xfffffffe);
      iVar4 = iVar4 + 1;
    } while (iVar4 <= iVar1);
  }
  pFVar2 = __iob_func();
  fputs("\n",pFVar2 + 1);
  return 0;
}

