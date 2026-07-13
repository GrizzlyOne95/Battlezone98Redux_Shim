
void FUN_004d7af0(undefined4 *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  if (param_1 != param_2) {
    local_c = param_1;
    while (local_c = local_c + 1, local_c != param_2) {
      local_8 = local_c;
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      local_14 = *puVar2;
      cVar1 = FUN_004d4120(local_14,*param_1);
      if (cVar1 == '\0') {
        while( true ) {
          local_10 = local_8 + -1;
          cVar1 = FUN_004d4120(local_14,*local_10);
          if (cVar1 == '\0') break;
          puVar2 = (undefined4 *)FUN_00417780(local_10);
          *local_8 = *puVar2;
          local_8 = local_10;
        }
        puVar2 = (undefined4 *)FUN_00417780(&local_14);
        *local_8 = *puVar2;
      }
      else {
        local_8 = local_8 + 1;
        _Move<>(param_1,local_c,local_8);
        puVar2 = (undefined4 *)FUN_00417780(&local_14);
        *param_1 = *puVar2;
      }
    }
  }
  return;
}

