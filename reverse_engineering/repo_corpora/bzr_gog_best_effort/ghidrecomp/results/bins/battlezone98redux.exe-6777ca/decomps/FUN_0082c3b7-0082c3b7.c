
undefined4 FUN_0082c3b7(undefined4 param_1)

{
  undefined4 uVar1;
  FILE *pFVar2;
  char *_Format;
  
  uVar1 = FUN_0082d377(param_1,0xffffffff,0);
  _Format = "PANIC: unprotected error in call to Lua API (%s)\n";
  pFVar2 = __iob_func();
  fprintf(pFVar2 + 2,_Format,uVar1);
  return 0;
}

