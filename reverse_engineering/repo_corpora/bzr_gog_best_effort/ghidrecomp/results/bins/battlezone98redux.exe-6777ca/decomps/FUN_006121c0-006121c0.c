
void __thiscall FUN_006121c0(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0062ccc0(param_3,"fun3d\\WeaponClass.cpp");
  *(int *)(iVar1 + 8) = param_1[6];
  *(int *)(iVar1 + 0xc) = param_1[7];
  *(uint *)(iVar1 + 0x14) = *(uint *)(param_2 + 0x14) & 0xf0010;
  *(undefined4 *)(iVar1 + 0x84) = 0x32;
  uVar2 = (**(code **)(*param_1 + 8))(iVar1);
  *(undefined4 *)(iVar1 + 0x88) = uVar2;
  FUN_00583d90(iVar1);
  return;
}

