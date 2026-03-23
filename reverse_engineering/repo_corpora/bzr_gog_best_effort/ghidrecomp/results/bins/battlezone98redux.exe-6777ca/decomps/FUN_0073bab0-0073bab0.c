
void FUN_0073bab0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c [2];
  
  FUN_00578c20(local_c,param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    iVar3 = FUN_00422150();
    FUN_00578d70(iVar3 + 0x10);
    local_10 = local_c[0];
    FUN_00429560(local_18,local_c[0]);
  }
  return;
}

