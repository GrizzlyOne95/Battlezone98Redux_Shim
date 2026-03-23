
undefined4 __thiscall FUN_004bb410(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_14;
  undefined4 local_c;
  undefined1 local_5;
  
  puVar2 = (undefined4 *)FUN_00422ea0();
  local_c = *puVar2;
  local_14 = *param_1;
  while (pcVar3 = (char *)FUN_004242d0(local_c), *pcVar3 == '\0') {
    uVar4 = FUN_00422f10(local_c);
    uVar5 = param_2;
    FUN_00422f60(&local_5);
    cVar1 = FUN_0046b460(uVar5,uVar4);
    if (cVar1 == '\0') {
      puVar2 = (undefined4 *)FUN_004242f0(local_c);
      local_c = *puVar2;
    }
    else {
      local_14 = local_c;
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      local_c = *puVar2;
    }
  }
  return local_14;
}

