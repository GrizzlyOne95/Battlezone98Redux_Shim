
void FUN_0062d200(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_10;
  undefined2 local_8;
  
  if (param_1 != 0) {
    local_8 = 1;
    iVar1 = *(int *)(param_1 + 0x78);
    if (iVar1 != 0) {
      local_8 = *(undefined2 *)(iVar1 + 0x12);
      if (*(int *)(iVar1 + 0x80) == param_1) {
        *(undefined4 *)(iVar1 + 0x80) = *(undefined4 *)(param_1 + 0x7c);
      }
      else {
        for (local_10 = *(int *)(iVar1 + 0x80); local_10 != 0; local_10 = *(int *)(local_10 + 0x7c))
        {
          if (*(int *)(local_10 + 0x7c) == param_1) {
            *(undefined4 *)(local_10 + 0x7c) = *(undefined4 *)(param_1 + 0x7c);
            break;
          }
        }
      }
    }
    *(undefined4 *)(param_1 + 0x78) = 0;
    *(undefined4 *)(param_1 + 0x7c) = 0;
    FUN_0062d150(param_1,1,local_8,iVar1,param_2);
  }
  return;
}

