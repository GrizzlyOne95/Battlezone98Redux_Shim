
void FUN_0074d060(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00578c20(&local_8,param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    local_c = local_8;
    FUN_006d6800(local_18,local_8);
  }
  uVar2 = FUN_00416410();
  FUN_00740e70(uVar2);
  return;
}

