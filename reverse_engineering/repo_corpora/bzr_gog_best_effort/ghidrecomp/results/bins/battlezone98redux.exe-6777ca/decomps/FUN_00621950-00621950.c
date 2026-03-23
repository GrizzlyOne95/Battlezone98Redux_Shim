
undefined4 FUN_00621950(undefined4 param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  iVar1 = FUN_0061e420(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (*(int *)(iVar1 + 8) == 0) {
    uVar2 = 0;
  }
  else {
    if (param_2 != (uint *)0x0) {
      local_c = (uint)(*(int *)(iVar1 + 8) == 2);
      *param_2 = local_c;
    }
    uVar2 = *(undefined4 *)(iVar1 + 4);
  }
  return uVar2;
}

