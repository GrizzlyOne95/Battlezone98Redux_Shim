
void __fastcall FUN_00589530(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_2c [4];
  undefined1 local_28 [8];
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  int *local_8;
  
  local_c = *(int *)*param_1 + -1;
  *(int *)*param_1 = local_c;
  if (local_c < 1) {
    local_8 = param_1;
    local_18 = FUN_00446460(*param_1 + 4,0x811c9dc5);
    FUN_0044eb20(&local_10,&local_18);
    uVar2 = FUN_0044eaa0(local_28);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 != '\0') {
      local_1c = local_10;
      FUN_0044eac0(local_2c,local_10);
    }
    local_20 = *local_8;
    if (local_20 != 0) {
      local_14 = local_20;
      FUN_005895f0(1);
    }
  }
  return;
}

