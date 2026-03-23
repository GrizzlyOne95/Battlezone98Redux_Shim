
undefined1 FUN_004cf350(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  undefined1 local_10;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,0xfe,0);
    FUN_004ce0b0();
    iVar2 = sscanf(DAT_0260db08,"%*s =");
    bVar3 = iVar2 == 0;
    FUN_004ce100();
  }
  else {
    bVar3 = true;
  }
  if ((((((bVar3) && (cVar1 = FUN_004ceb10(param_1,param_2,4), cVar1 != '\0')) &&
        (cVar1 = FUN_004ceb10(param_1,param_2 + 4,4), cVar1 != '\0')) &&
       ((cVar1 = FUN_004ceb10(param_1,param_2 + 8,4), cVar1 != '\0' &&
        (cVar1 = FUN_004ceb10(param_1,param_2 + 0xc,4), cVar1 != '\0')))) &&
      ((cVar1 = FUN_004ceb10(param_1,param_2 + 0x10,4), cVar1 != '\0' &&
       ((cVar1 = FUN_004ceb10(param_1,param_2 + 0x14,4), cVar1 != '\0' &&
        (cVar1 = FUN_004ced10(param_1,param_2 + 0x18,0xc), cVar1 != '\0')))))) &&
     ((cVar1 = FUN_004ced10(param_1,param_2 + 0x24,0xc), cVar1 != '\0' &&
      (cVar1 = FUN_004ced10(param_1,param_2 + 0x30,0xc), cVar1 != '\0')))) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  return local_10;
}

