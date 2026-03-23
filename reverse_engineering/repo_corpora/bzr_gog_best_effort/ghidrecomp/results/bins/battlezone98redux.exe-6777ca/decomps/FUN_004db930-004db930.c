
void __fastcall FUN_004db930(int *param_1)

{
  int *piVar1;
  void *pvVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a10c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_1[0x3f] != 0) {
    if ((undefined4 *)param_1[0x3f] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x3f])(1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
    }
    param_1[0x3f] = 0;
  }
  (**(code **)(*param_1 + 8))();
  piVar1 = DAT_00917afc;
  FUN_0062c190(param_1[0x3c]);
  DAT_00917afc = param_1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))();
  }
  (**(code **)(*param_1 + 4))(DAT_00917b00);
  pvVar2 = operator_new(200);
  local_8 = 0;
  if (pvVar2 != (void *)0x0) {
    uVar3 = FUN_0045ca50(param_1);
    FUN_00608d40(uVar3,param_1);
  }
  ExceptionList = local_10;
  return;
}

