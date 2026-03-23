
undefined4 FUN_00837948(undefined4 param_1)

{
  char *_Str;
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  _Str = (char *)FUN_0082ba59(param_1,1,0);
  pcVar1 = strchr(_Str,0x2e);
  uVar2 = 0;
  if (pcVar1 != (char *)0x0) {
    FUN_0082cd08(param_1,_Str,(int)pcVar1 - (int)_Str);
    uVar2 = FUN_0082d377(param_1,0xffffffff,0,"cpath");
    iVar3 = FUN_00837d46(param_1,uVar2);
    if (iVar3 != 0) {
      uVar2 = FUN_0083810b(param_1,_Str);
      iVar4 = FUN_00837e92(param_1,iVar3,uVar2);
      if (iVar4 != 0) {
        if (iVar4 != 2) {
          FUN_00837f99(param_1,iVar3);
        }
        FUN_0082cc9e(param_1,"\n\tno module \'%s\' in file \'%s\'",_Str,iVar3);
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

