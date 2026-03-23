
void __fastcall FUN_004dba60(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1[0x3f] != 0) {
    if ((undefined4 *)param_1[0x3f] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x3f])(1);
    }
    param_1[0x3f] = 0;
  }
  (**(code **)(*param_1 + 8))();
  uVar1 = FUN_0047e9a0(param_1[0x3d]);
  (**(code **)(*param_1 + 4))(uVar1);
  return;
}

