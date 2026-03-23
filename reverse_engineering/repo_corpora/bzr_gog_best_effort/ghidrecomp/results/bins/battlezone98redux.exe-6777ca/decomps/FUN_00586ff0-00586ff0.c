
int * __thiscall FUN_00586ff0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *local_10;
  
  if (*(int *)(param_1[0xe] + 0x80) == 0) {
    iVar2 = FUN_0062ccc0(0,"fun3d\\OrdnanceClass.cpp");
    *(int *)(iVar2 + 8) = param_1[6];
    *(int *)(iVar2 + 0xc) = param_1[7];
    *(undefined4 *)(iVar2 + 100) = 0;
    if (*(int *)(param_1[0xc] + 100) != 0) {
      FUN_004e3430(param_1[0xc],iVar2);
      iVar1 = param_1[0xc];
      *(undefined4 *)(iVar2 + 0xb0) = *(undefined4 *)(iVar1 + 0xb0);
      *(undefined4 *)(iVar2 + 0xb4) = *(undefined4 *)(iVar1 + 0xb4);
      *(undefined4 *)(iVar2 + 0xb8) = *(undefined4 *)(iVar1 + 0xb8);
      *(undefined4 *)(iVar2 + 0xbc) = *(undefined4 *)(iVar1 + 0xbc);
      *(undefined4 *)(iVar2 + 0xc0) = *(undefined4 *)(iVar1 + 0xc0);
      *(undefined4 *)(iVar2 + 0xc4) = *(undefined4 *)(iVar1 + 0xc4);
      iVar1 = param_1[0xc];
      *(undefined4 *)(iVar2 + 0xa0) = *(undefined4 *)(iVar1 + 0xa0);
      *(undefined4 *)(iVar2 + 0xa4) = *(undefined4 *)(iVar1 + 0xa4);
      *(undefined4 *)(iVar2 + 0xa8) = *(undefined4 *)(iVar1 + 0xa8);
      *(undefined4 *)(iVar2 + 0xac) = *(undefined4 *)(iVar1 + 0xac);
    }
    *(undefined4 *)(iVar2 + 0x84) = 0x33;
    uVar3 = (**(code **)(*param_1 + 8))(iVar2);
    *(undefined4 *)(iVar2 + 0x88) = uVar3;
    local_10 = (int *)FUN_00583d90(iVar2);
  }
  else {
    uVar3 = *(undefined4 *)(param_1[0xe] + 0x80);
    FUN_0062d4b0(uVar3);
    local_10 = (int *)FUN_00583d90(uVar3);
  }
  (**(code **)(*local_10 + 4))(param_2,param_3);
  return local_10;
}

