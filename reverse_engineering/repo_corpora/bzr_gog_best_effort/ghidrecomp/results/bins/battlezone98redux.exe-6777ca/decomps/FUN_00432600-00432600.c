
void __thiscall FUN_00432600(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  if (param_1 != param_3) {
    local_8 = param_1;
    cVar1 = FUN_0042d8f0();
    if (cVar1 == '\0') {
      puVar2 = (undefined4 *)FID_conflict_begin(local_14);
      local_c = *puVar2;
      puVar2 = (undefined4 *)FUN_0042d8c0(local_18);
      local_10 = *puVar2;
      FUN_00432ac0(param_2,param_3,local_10,local_c,*(undefined4 *)(param_3 + 4));
    }
  }
  return;
}

