
undefined4 __thiscall
FUN_006ef220(allocator<char> *param_1,undefined4 param_2,int *param_3,undefined4 param_4,
            undefined4 param_5)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  
  piVar1 = (int *)std::allocator<char>::allocator<char>(param_1);
  iVar6 = *param_3 - *piVar1 >> 5;
  uVar2 = FUN_00417780(*param_3,iVar6);
  uVar3 = FUN_006f31b0(param_4);
  uVar5 = *(undefined4 *)param_1;
  uVar7 = uVar3;
  uVar4 = std::allocator<char>::allocator<char>(param_1);
  uVar5 = FUN_006f31f0(uVar4,uVar7,uVar5);
  uVar5 = FUN_00417780(uVar5);
  FUN_006fc430(uVar5,uVar3,uVar2,param_4,param_5);
  piVar1 = (int *)std::allocator<char>::allocator<char>(param_1);
  FUN_00447eb0(iVar6 * 0x20 + *piVar1);
  return param_2;
}

