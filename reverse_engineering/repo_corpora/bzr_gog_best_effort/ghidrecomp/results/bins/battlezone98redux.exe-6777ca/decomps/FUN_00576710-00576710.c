
void FUN_00576710(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_20 [8];
  int local_18;
  int local_14;
  undefined1 local_10 [4];
  int *local_c;
  int local_8;
  
  FUN_00578c20(local_10,param_1);
  local_8 = 0;
  uVar2 = FID_conflict_begin(local_20);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    iVar3 = FUN_00422150();
    local_8 = *(int *)(iVar3 + 0x10);
  }
  if (local_8 != 0) {
    local_c = (int *)FUN_0045ca50();
    if (local_c != (int *)0x0) {
      (**(code **)(*local_c + 0x2c))(local_8);
    }
    local_18 = local_8;
    local_14 = local_8;
    if (local_8 != 0) {
      FUN_005715a0(1);
    }
  }
  return;
}

