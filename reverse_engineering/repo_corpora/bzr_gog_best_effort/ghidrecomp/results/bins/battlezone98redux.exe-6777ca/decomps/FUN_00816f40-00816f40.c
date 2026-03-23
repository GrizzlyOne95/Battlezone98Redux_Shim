
undefined4 __thiscall
FUN_00816f40(allocator<char> *param_1,undefined4 param_2,undefined4 *param_3,uint param_4,
            undefined4 param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = (int *)FUN_004b4350();
  if ((uint)(*piVar1 - *(int *)(param_1 + 4)) < param_4) {
    FUN_00817210(param_2,param_3,param_4,param_5,0);
  }
  else {
    iVar2 = FUN_00417780(*param_3);
    iVar3 = FUN_006d0da0();
    iVar3 = iVar2 - iVar3 >> 5;
    FUN_008172c0(iVar2,param_4,param_5,iVar3);
    piVar1 = (int *)std::allocator<char>::allocator<char>(param_1);
    FUN_00447eb0(iVar3 * 0x20 + *piVar1);
  }
  return param_2;
}

