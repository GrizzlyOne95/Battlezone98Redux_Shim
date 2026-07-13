
void __fastcall FUN_0046f210(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  uint local_14;
  int local_10;
  uint local_c;
  undefined1 local_8 [4];
  
  local_c = *(uint *)(param_1 + 4);
  local_18 = param_1;
  local_10 = param_1;
  FUN_0045e290(&local_18);
  local_14 = local_c;
  if (0xf < local_c) {
    ___report_rangecheckfailure();
  }
  (&DAT_0260d6c4)[local_14] = 0;
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_20);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      return;
    }
    piVar3 = (int *)FUN_0042de50();
    if (*(uint *)(*piVar3 + 4) == local_c) break;
    FUN_00438c10(local_1c,0);
  }
  (&DAT_0260d6c4)[local_c] = 1;
  return;
}

