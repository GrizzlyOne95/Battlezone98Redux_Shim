
undefined4 FUN_0074b910(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [8];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int local_8;
  
  uVar2 = FID_conflict_begin(local_18);
  FUN_00578c20(local_1c,param_2);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    puVar3 = local_c;
    FUN_006cc5c0(param_2);
    FUN_00420260(puVar3);
    puVar3 = local_10;
    FUN_006cc5c0(param_2);
    FID_conflict_begin(puVar3);
    local_8 = 0;
    while (cVar1 = FUN_00420f10(local_10), cVar1 != '\0') {
      if (local_8 == param_3) {
        uVar2 = FUN_00422150();
        FUN_0073a740(uVar2);
        return param_1;
      }
      local_8 = local_8 + 1;
      FUN_00428570();
    }
    FUN_0073a6b0();
  }
  else {
    FUN_0073a6b0();
  }
  return param_1;
}

