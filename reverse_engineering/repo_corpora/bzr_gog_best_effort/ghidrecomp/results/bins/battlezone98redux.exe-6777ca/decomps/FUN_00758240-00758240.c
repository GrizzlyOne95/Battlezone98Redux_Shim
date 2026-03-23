
void FUN_00758240(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_1c [12];
  int local_10;
  int *local_c;
  int local_8;
  
  FUN_00764760(param_1);
  local_10 = FUN_00746690(param_1);
  local_8 = local_10 + 0x18;
  iVar2 = FUN_006aa1d0();
  if (iVar2 != 0) {
    cVar1 = FUN_0073a900();
    if (cVar1 != '\0') {
      local_c = (int *)FUN_006aa1d0();
      puVar3 = (undefined4 *)FUN_0073a970(local_1c);
      (**(code **)(*local_c + 0x80))(*puVar3,puVar3[1]);
    }
  }
  return;
}

