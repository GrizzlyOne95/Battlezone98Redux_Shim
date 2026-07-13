
void FUN_006a2200(int param_1,int param_2)

{
  int iVar1;
  char cVar2;
  int *local_1c;
  int local_c;
  int *local_8;
  
  cVar2 = FUN_006a2150(param_1,param_2);
  if (cVar2 == '\0') {
    local_1c = operator_new(8);
    if (local_1c == (int *)0x0) {
      local_1c = (int *)0x0;
    }
    else {
      memset(local_1c,0,8);
    }
    local_8 = local_1c;
    *local_1c = param_1;
    local_1c[1] = param_2;
    cVar2 = FUN_006a0810(param_1);
    if (cVar2 == '\0') {
      FUN_0041fe40(&local_8);
    }
    else {
      FUN_0041fe40(&local_8);
    }
    if ((*(int *)(param_1 + 0x14) == 0x434e5354) ||
       (cVar2 = FUN_006a07e0(*(undefined4 *)(param_1 + 0x14)), cVar2 != '\0')) {
      for (local_c = 0; local_c < 9; local_c = local_c + 1) {
        iVar1 = *(int *)(param_1 + 0x608 + local_c * 4);
        if (((iVar1 != 0) && (*(int *)(iVar1 + 0x1c) != 5)) && (*(int *)(iVar1 + 0x1c) != 7)) {
          FUN_006a2200(iVar1,param_1);
        }
      }
    }
  }
  return;
}

