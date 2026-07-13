
void __fastcall FUN_005d1dd0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0068bed0("shockwave.0");
  *(undefined4 *)(param_1 + 0x28) = uVar1;
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x28) + 0x10;
  return;
}

