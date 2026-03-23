
undefined4 FUN_0080e470(undefined4 param_1,undefined4 param_2,double *param_3)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  float10 fVar4;
  
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 == '\0') {
    pcVar3 = (char *)get();
    if ((*pcVar3 != 'i') && (pcVar3 = (char *)get(), *pcVar3 != 'I')) {
      return 0;
    }
    cVar1 = FUN_0080faa0(&DAT_008a1b2c,&DAT_008a1d7c,param_1,param_2,&DAT_0260c0e5);
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
    else {
      FUN_0080faa0("inity","INITY",param_1,param_2,&DAT_0260c0e5);
      fVar4 = (float10)FUN_007face0();
      *param_3 = (double)fVar4;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

