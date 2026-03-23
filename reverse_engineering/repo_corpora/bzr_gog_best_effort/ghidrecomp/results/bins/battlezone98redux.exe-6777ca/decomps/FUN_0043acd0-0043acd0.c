
undefined4 * __thiscall FUN_0043acd0(undefined4 param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)FUN_0043bc50(param_1);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (param_2 == (char *)0x0) break;
    iVar2 = _stricmp((char *)(puVar1 + 1),param_2);
    if (iVar2 == 0) {
      return puVar1;
    }
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}

