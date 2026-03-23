
int * __thiscall FUN_004cb7b0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *local_10;
  
  if (*(int *)(param_1[0xb] + 0x80) == 0) {
    iVar1 = FUN_0062ccc0(0,"fun3d\\ExplosionClass.cpp");
    *(int *)(iVar1 + 8) = param_1[4];
    *(int *)(iVar1 + 0xc) = param_1[5];
    *(undefined4 *)(iVar1 + 0x84) = 0x34;
    uVar2 = (**(code **)(*param_1 + 8))(iVar1);
    *(undefined4 *)(iVar1 + 0x88) = uVar2;
    local_10 = (int *)FUN_004c9840(iVar1);
  }
  else {
    uVar2 = *(undefined4 *)(param_1[0xb] + 0x80);
    FUN_0062d4b0(uVar2);
    local_10 = (int *)FUN_004c9840(uVar2);
  }
  (**(code **)(*local_10 + 4))(param_2,param_3);
  return local_10;
}

