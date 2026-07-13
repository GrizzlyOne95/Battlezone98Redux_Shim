
undefined4 FUN_00833605(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  byte *_Str;
  ulong uVar3;
  float10 fVar4;
  double dVar5;
  byte *local_8;
  
  iVar2 = FUN_0082c1fd(param_1,2);
  if (iVar2 == 10) {
    FUN_0082b9f2(param_1,1);
    iVar2 = FUN_0082c9c5(param_1,1);
    if (iVar2 != 0) {
      fVar4 = (float10)FUN_0082d3e1(param_1,1);
      dVar5 = (double)fVar4;
LAB_00833649:
      FUN_0082cd58(param_1,dVar5);
      return 1;
    }
  }
  else {
    _Str = (byte *)FUN_0082ba59(param_1,1);
    if ((iVar2 < 2) || (0x24 < iVar2)) {
      FUN_0082b8e4(param_1,2);
    }
    uVar3 = strtoul((char *)_Str,(char **)&local_8,iVar2);
    if (_Str != local_8) {
      bVar1 = *local_8;
      while (iVar2 = isspace((uint)bVar1), iVar2 != 0) {
        local_8 = local_8 + 1;
        bVar1 = *local_8;
      }
      if (*local_8 == 0) {
        dVar5 = (double)(int)uVar3 + (double)(&DAT_008a2fd0)[-((int)uVar3 >> 0x1f)];
        goto LAB_00833649;
      }
    }
  }
  FUN_0082cd45();
  return 1;
}

