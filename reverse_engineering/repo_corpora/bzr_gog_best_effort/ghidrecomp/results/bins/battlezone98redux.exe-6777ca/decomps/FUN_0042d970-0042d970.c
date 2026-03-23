
undefined4 FUN_0042d970(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  uVar2 = FUN_0042d8c0(local_c);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 != '\0') {
      FUN_00428a90();
      FID_conflict_begin(param_1);
      return param_1;
    }
  }
  while (cVar1 = FUN_00420f10(&param_3), cVar1 != '\0') {
    puVar3 = (undefined4 *)FUN_0042d920(local_14,param_2);
    param_2 = *puVar3;
  }
  FID_conflict__Make_iter(param_1,param_3);
  return param_1;
}

