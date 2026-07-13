
undefined4 FUN_0074bde0(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int local_8;
  
  FUN_00420260(local_c);
  uVar2 = extraout_var;
  FID_conflict_begin(local_10);
  local_8 = 0;
  while( true ) {
    cVar1 = FUN_00420f10(local_10);
    if (cVar1 == '\0') {
      FUN_0073a6b0(uVar2);
      return param_1;
    }
    if (local_8 == param_2) break;
    local_8 = local_8 + 1;
    FUN_00428570();
  }
  uVar2 = FUN_00422150();
  FUN_0073a740(uVar2);
  return param_1;
}

