
void __thiscall
FUN_0050b310(int param_1,undefined4 param_2,undefined2 param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  uint local_10;
  int local_c;
  int local_8;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    local_8 = param_1;
    FUN_0082c82c(*(undefined4 *)(param_1 + 4),0xffffd8ee,"Receive",0);
    iVar1 = FUN_0082d490(*(undefined4 *)(local_8 + 4),0xffffffff);
    if (iVar1 == 6) {
      FUN_0082ccca(*(undefined4 *)(local_8 + 4),param_3);
      FUN_0082cd08(*(undefined4 *)(local_8 + 4),param_4 + 1,1);
      local_c = 2;
      local_10 = param_4 + 2;
      while (local_10 < (uint)(param_4 + param_5)) {
        local_c = local_c + 1;
        FUN_00506010(&local_10,*(undefined4 *)(local_8 + 4));
      }
      uVar2 = FUN_0082cb8c(*(undefined4 *)(local_8 + 4),local_c,1,0,*(undefined4 *)(local_8 + 4),
                           "Lua script Receive error:\n%s");
      FUN_004ff600(uVar2);
      uVar2 = FUN_0082d2e8(*(undefined4 *)(local_8 + 4),0xffffffff);
    }
    FUN_0082d226(*(undefined4 *)(local_8 + 4),0xfffffffe,uVar2);
  }
  return;
}

