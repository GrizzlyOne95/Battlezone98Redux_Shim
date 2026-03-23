
void FUN_00497200(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  if (param_1 != param_2) {
    local_c = param_1;
    while (local_c = local_c + 2, local_c != param_2) {
      local_8 = local_c;
      puVar3 = (undefined4 *)FUN_00417780(local_c);
      local_18 = *puVar3;
      local_14 = puVar3[1];
      cVar2 = FUN_00497100(&local_18,param_1);
      if (cVar2 == '\0') {
        while( true ) {
          local_10 = local_8 + -2;
          cVar2 = FUN_00497100(&local_18,local_10);
          if (cVar2 == '\0') break;
          puVar3 = (undefined4 *)FUN_00417780(local_10);
          uVar1 = puVar3[1];
          *local_8 = *puVar3;
          local_8[1] = uVar1;
          local_8 = local_10;
        }
        puVar3 = (undefined4 *)FUN_00417780(&local_18);
        uVar1 = puVar3[1];
        *local_8 = *puVar3;
        local_8[1] = uVar1;
      }
      else {
        local_8 = local_8 + 2;
        _Move<>(param_1,local_c,local_8);
        puVar3 = (undefined4 *)FUN_00417780(&local_18);
        uVar1 = puVar3[1];
        *param_1 = *puVar3;
        param_1[1] = uVar1;
      }
    }
  }
  return;
}

