
void __fastcall FUN_0078e390(int param_1)

{
  undefined4 uVar1;
  
  FUN_0078c4a0();
  *(undefined4 *)(param_1 + 0x148) = 0;
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x154));
  if (*(undefined4 **)(param_1 + 0x154) == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)**(undefined4 **)(param_1 + 0x154))(1);
  }
  FUN_0078c4b0(0x4097700000000000,FUN_0078e000,uVar1);
  return;
}

