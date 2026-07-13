
undefined4 FUN_00625070(undefined4 param_1,int param_2)

{
  short sVar1;
  short sVar2;
  
  if (param_2 == 0) {
    DAT_0092016c = DAT_0092016c + 1;
    if (DAT_00920164 <= DAT_0092016c) {
      DAT_0092016c = 0;
    }
    sVar1 = (&DAT_02ceb882)[DAT_0092016c * 0x12];
    sVar2 = FUN_00572d90();
    if ((sVar1 == sVar2) && (DAT_0092016c = DAT_0092016c + 1, DAT_00920164 <= DAT_0092016c)) {
      DAT_0092016c = 0;
    }
  }
  else {
    DAT_0092016c = DAT_0092016c + -1;
    if (DAT_0092016c < 0) {
      DAT_0092016c = DAT_00920164 + -1;
    }
    sVar1 = (&DAT_02ceb882)[DAT_0092016c * 0x12];
    sVar2 = FUN_00572d90();
    if ((sVar1 == sVar2) && (DAT_0092016c = DAT_0092016c + -1, DAT_0092016c < 0)) {
      DAT_0092016c = DAT_00920164 + -1;
    }
  }
  FUN_00823470(DAT_02a1748c,&DAT_02ceb860 + DAT_0092016c * 0x24);
  return 1;
}

