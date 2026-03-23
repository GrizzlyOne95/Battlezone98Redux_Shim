
int __thiscall FUN_0056a970(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00435a40(param_2);
  iVar2 = FUN_004da060(*(undefined4 *)(param_1 + 0xf0));
  if (iVar2 == 0) {
    *(undefined4 *)(param_2 + iVar1) = 0;
  }
  else {
    uVar3 = FUN_004b9a90();
    *(undefined4 *)(param_2 + iVar1) = uVar3;
  }
  return iVar1 + 4;
}

