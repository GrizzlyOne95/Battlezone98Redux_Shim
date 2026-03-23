
undefined4 * __thiscall FUN_0043ac70(undefined4 param_1,char *param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)FUN_0043bc50(param_1);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (puVar1[0x16] == param_3) {
      if (param_2 == (char *)0x0) {
        return puVar1;
      }
      iVar2 = _stricmp((char *)(puVar1 + 1),param_2);
      if (iVar2 == 0) {
        return puVar1;
      }
    }
    puVar1 = (undefined4 *)*puVar1;
  } while( true );
}

