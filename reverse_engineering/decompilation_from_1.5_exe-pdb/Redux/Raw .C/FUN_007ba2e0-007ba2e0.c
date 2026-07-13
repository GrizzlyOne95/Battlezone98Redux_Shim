
void __fastcall FUN_007ba2e0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004fdc80(*(int *)(param_1 + 0x2f4) + 1,param_1 + 0x188,
                       *(undefined4 *)(param_1 + 0x150 + *(int *)(param_1 + 0x2f4) * 4));
  if (iVar1 == 0) {
    FUN_004fdf00(*(int *)(param_1 + 0x2f4) + 1);
    uVar2 = FUN_0081cb40("multi_error","empty");
    FUN_007c2950(uVar2);
  }
  else {
    FUN_007c2950(param_1 + 0x188);
  }
  return;
}

