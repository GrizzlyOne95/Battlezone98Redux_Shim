
undefined1 FUN_004cdf10(undefined4 param_1,uint param_2,int param_3)

{
  bool bVar1;
  undefined1 uVar2;
  char *pcVar3;
  int iVar4;
  int local_14;
  short local_c;
  
  FUN_004cc300(0,param_1,param_2);
  pcVar3 = DAT_0260db08;
  if (*(ushort *)(DAT_0260db08 + 2) != param_2) {
    FUN_007d6b70("in_data type=%d size=%d @%d: data larger than 65535:\n",param_1,param_2,
                 (int)DAT_0260db08 - DAT_0260db14);
  }
  if ((*pcVar3 == (char)param_1) && (local_c = (short)param_2, *(short *)(pcVar3 + 2) == local_c)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    pcVar3 = DAT_0260db08 + 4;
    if (DAT_0260db00 < pcVar3 + param_2) {
      iVar4 = (int)DAT_0260db08 - DAT_0260db14;
      DAT_0260db08 = pcVar3;
      FUN_007d6c70("in_data type=%d size=%d @%d: tried to read %d bytes past the end of the file\n",
                   param_1,param_2,iVar4,pcVar3 + (param_2 - (int)DAT_0260db00));
      uVar2 = 0;
    }
    else {
      DAT_0260db08 = pcVar3;
      for (local_14 = 0; local_14 < (int)param_2; local_14 = local_14 + 1) {
        *(bool *)(param_3 + local_14) = *DAT_0260db08 != '\0';
        DAT_0260db08 = DAT_0260db08 + 1;
      }
      uVar2 = 1;
    }
  }
  else {
    FUN_007d6c70("in_data type=%d size=%d @%d: found type=%d size=%d\n",param_1,param_2,
                 (int)DAT_0260db08 - DAT_0260db14,*pcVar3,*(undefined2 *)(pcVar3 + 2));
    uVar2 = 0;
  }
  return uVar2;
}

