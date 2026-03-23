
void FUN_00696d10(undefined4 param_1,int param_2)

{
  if ((*(byte *)(param_2 + 0x78) & 1) != 0) {
    FUN_00696c90(param_1,param_2,0xffffffff,0xffffffff,1);
  }
  if ((*(byte *)(param_2 + 0x78) & 8) != 0) {
    FUN_00696c90(param_1,param_2,0xffffffff,0,8);
  }
  if ((*(byte *)(param_2 + 0x78) & 0x20) != 0) {
    FUN_00696c90(param_1,param_2,0xffffffff,1,0x20);
  }
  if ((*(byte *)(param_2 + 0x78) & 2) != 0) {
    FUN_00696c90(param_1,param_2,0,0xffffffff,2);
  }
  if ((*(byte *)(param_2 + 0x78) & 0x40) != 0) {
    FUN_00696c90(param_1,param_2,0,1,0x40);
  }
  if ((*(byte *)(param_2 + 0x78) & 4) != 0) {
    FUN_00696c90(param_1,param_2,1,0xffffffff,4);
  }
  if ((*(byte *)(param_2 + 0x78) & 0x10) != 0) {
    FUN_00696c90(param_1,param_2,1,0,0x10);
  }
  if ((*(byte *)(param_2 + 0x78) & 0x80) != 0) {
    FUN_00696c90(param_1,param_2,1,1,0x80);
  }
  *(undefined1 *)(param_2 + 0x78) = 0;
  return;
}

