
uint FUN_00831e54(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  char *_Str2;
  int iVar6;
  char *_Str1;
  
  iVar6 = *(int *)(param_1 + 0xc);
  _Str1 = (char *)(param_1 + 0x10);
  _Str2 = (char *)(param_2 + 0x10);
  iVar2 = *(int *)(param_2 + 0xc);
  while( true ) {
    uVar3 = strcoll(_Str1,_Str2);
    if (uVar3 != 0) {
      return uVar3;
    }
    pcVar4 = _Str1;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar5 = (int)pcVar4 - (int)(_Str1 + 1);
    if (iVar5 == iVar2) break;
    if (iVar5 == iVar6) {
      return 0xffffffff;
    }
    iVar5 = iVar5 + 1;
    _Str1 = _Str1 + iVar5;
    iVar6 = iVar6 - iVar5;
    _Str2 = _Str2 + iVar5;
    iVar2 = iVar2 - iVar5;
  }
  return (uint)(iVar5 != iVar6);
}

