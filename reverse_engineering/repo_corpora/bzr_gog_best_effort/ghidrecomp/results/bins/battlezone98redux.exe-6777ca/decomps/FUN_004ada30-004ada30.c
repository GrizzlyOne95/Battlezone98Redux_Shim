
void __fastcall FUN_004ada30(int param_1)

{
  if ((*(int *)(param_1 + 0xec) != 0) && (*(int *)(*(int *)(param_1 + 0xf4) + 0x84) != 4)) {
    *(undefined4 *)(param_1 + 0xec) = 0;
    if (*(int *)(param_1 + 0xfc) != 0) {
      if (*(undefined4 **)(param_1 + 0xfc) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0xfc))(1);
      }
      *(undefined4 *)(param_1 + 0xfc) = 0;
    }
    memset((void *)(*(int *)(param_1 + 0x230) + 0xc4),0,0x2c);
    if (*(int *)(param_1 + 0x1a0) != 0) {
      FUN_004a7800();
    }
    *(undefined4 *)(param_1 + 0x298) = 0;
  }
  return;
}

