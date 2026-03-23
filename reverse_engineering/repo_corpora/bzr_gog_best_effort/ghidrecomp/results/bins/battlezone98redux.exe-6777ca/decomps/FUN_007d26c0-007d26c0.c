
undefined4 FUN_007d26c0(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_10;
  int local_c;
  
  local_c = 0;
  do {
    iVar2 = size();
    if (iVar2 <= local_c) {
      local_10 = 0;
      do {
        iVar2 = size();
        if (iVar2 <= local_10) {
          cVar1 = FUN_007d3360();
          if (cVar1 != '\0') {
            cVar1 = FUN_007d2810((float)param_1,(float)param_2);
            if (cVar1 != '\0') {
              return 1;
            }
          }
          return 0;
        }
        FUN_004200d0(local_10);
        iVar2 = FUN_007d2250();
        if (iVar2 == 0) {
          puVar3 = (undefined4 *)FUN_004200d0(local_10);
          cVar1 = (**(code **)(*(int *)*puVar3 + 0x20))(param_1,param_2,param_3);
          if (cVar1 != '\0') {
            return 1;
          }
        }
        local_10 = local_10 + 1;
      } while( true );
    }
    FUN_004200d0(local_c);
    iVar2 = FUN_007d2250();
    if (iVar2 != 0) {
      puVar3 = (undefined4 *)FUN_004200d0(local_c);
      cVar1 = (**(code **)(*(int *)*puVar3 + 0x20))(param_1,param_2,param_3);
      if (cVar1 != '\0') {
        return 1;
      }
    }
    local_c = local_c + 1;
  } while( true );
}

