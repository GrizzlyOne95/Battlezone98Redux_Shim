
undefined4 __fastcall FUN_004784b0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 local_8 [4];
  
  local_10 = *(int *)(param_1 + 0x104) + 8;
  local_c = param_1;
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_20);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      *(undefined4 *)(local_c + 0xc) = 2;
      return 1;
    }
    local_14 = FUN_0042de50();
    if ((*(int *)(*(int *)(local_14 + 4) + 8) == 0xc) &&
       (local_18 = FUN_00473940(), local_18 == *(int *)(local_c + 0x10))) break;
    FUN_00438c10(local_1c,0);
  }
  return 0;
}

