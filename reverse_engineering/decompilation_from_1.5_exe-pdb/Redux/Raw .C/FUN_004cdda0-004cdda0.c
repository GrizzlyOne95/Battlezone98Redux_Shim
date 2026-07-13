
undefined1 FUN_004cdda0(undefined4 param_1,size_t param_2,void *param_3)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  char *pcVar4;
  
  FUN_004cc300(0,param_1,param_2);
  pcVar4 = DAT_0260db08;
  if (*(ushort *)(DAT_0260db08 + 2) != param_2) {
    FUN_007d6b70("in_data type=%d size=%d @%d: data larger than 65535:\n",param_1,param_2,
                 (int)DAT_0260db08 - DAT_0260db14);
  }
  if ((*pcVar4 == (char)param_1) && (*(short *)(pcVar4 + 2) == (short)param_2)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    pcVar4 = DAT_0260db08 + 4;
    if (DAT_0260db00 < pcVar4 + param_2) {
      iVar3 = (int)DAT_0260db08 - DAT_0260db14;
      DAT_0260db08 = pcVar4;
      FUN_007d6c70("in_data type=%d size=%d @%d: tried to read %d bytes past the end of the file\n",
                   param_1,param_2,iVar3,pcVar4 + (param_2 - (int)DAT_0260db00));
      uVar2 = 0;
    }
    else {
      DAT_0260db08 = pcVar4;
      memcpy(param_3,pcVar4,param_2);
      DAT_0260db08 = DAT_0260db08 + param_2;
      uVar2 = 1;
    }
  }
  else {
    FUN_007d6c70("in_data type=%d size=%d @%d: found type=%d size=%d\n",param_1,param_2,
                 (int)DAT_0260db08 - DAT_0260db14,*pcVar4,*(undefined2 *)(pcVar4 + 2));
    uVar2 = 0;
  }
  return uVar2;
}

