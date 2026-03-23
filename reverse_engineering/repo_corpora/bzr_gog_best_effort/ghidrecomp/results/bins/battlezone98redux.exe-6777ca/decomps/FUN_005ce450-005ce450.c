
bool FUN_005ce450(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  undefined4 local_14 [2];
  int local_c;
  int local_8;
  
  if (DAT_02a13c7b == '\0') {
    DAT_009182a4 = DAT_009182a4 + 1;
    local_c = FUN_00460fc0(param_1);
    if (local_c == 0) {
      FUN_007d6a70("Path not found %s",param_1);
      bVar2 = true;
    }
    else {
      local_8 = FUN_00460fc0(param_4);
      if (local_8 == 0) {
        FUN_007d6a70("Path not found %s",param_4);
        bVar2 = true;
      }
      else {
        local_14[0] = 0;
        FUN_00822290(local_c,&param_2,&param_3,local_8,local_14,0);
        iVar1 = FUN_00821fb0();
        bVar2 = iVar1 == 1;
      }
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}

