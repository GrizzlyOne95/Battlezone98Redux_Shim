
undefined4 FUN_007c5690(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 *local_10;
  undefined4 local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  puVar2 = (undefined4 *)FUN_00422ea0();
  local_c = *puVar2;
  local_1c = *local_10;
  local_14 = *local_10;
  while (pcVar3 = (char *)FUN_004242d0(local_c), *pcVar3 == '\0') {
    uVar5 = param_2;
    uVar4 = FUN_00422f10(local_c);
    FUN_00422f60(&local_5);
    cVar1 = FUN_0046b460(uVar4,uVar5);
    if (cVar1 == '\0') {
      pcVar3 = (char *)FUN_004242d0(local_14);
      if (*pcVar3 != '\0') {
        uVar4 = FUN_00422f10(local_c);
        uVar5 = param_2;
        FUN_00422f60(&local_6);
        cVar1 = FUN_0046b460(uVar5,uVar4);
        if (cVar1 != '\0') {
          local_14 = local_c;
        }
      }
      local_1c = local_c;
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      local_c = *puVar2;
    }
    else {
      puVar2 = (undefined4 *)FUN_004242f0(local_c);
      local_c = *puVar2;
    }
  }
  pcVar3 = (char *)FUN_004242d0(local_14);
  if (*pcVar3 == '\0') {
    puVar2 = (undefined4 *)FUN_00417780(local_14);
    local_18 = *puVar2;
  }
  else {
    puVar2 = (undefined4 *)FUN_00422ea0();
    local_18 = *puVar2;
  }
  local_c = local_18;
  while (pcVar3 = (char *)FUN_004242d0(local_c), *pcVar3 == '\0') {
    uVar4 = FUN_00422f10(local_c);
    uVar5 = param_2;
    FUN_00422f60(&local_7);
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
  _Vector_iterator<>(local_1c,local_10);
  _Vector_iterator<>(local_14,local_10);
  FUN_004bcb60(local_24,local_20);
  return param_1;
}

