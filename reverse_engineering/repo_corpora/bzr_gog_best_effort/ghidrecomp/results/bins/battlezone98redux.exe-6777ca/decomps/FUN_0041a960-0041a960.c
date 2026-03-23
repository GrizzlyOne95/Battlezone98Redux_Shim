
void __fastcall FUN_0041a960(int *param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(*param_1 + 0x14))();
  if (cVar1 != '\0') {
    if (param_1[0x1f] != 0) {
      FUN_00417990(param_1[0x1d]);
      FUN_0068ca30(DAT_00917580,DAT_009469c8,param_1[0x1f],param_1[0x20],param_1[0x21],
                   (param_1[0x22] - param_1[0x20]) + 1,(param_1[0x23] - param_1[0x21]) + 1,5,0);
    }
    FUN_00418fb0();
  }
  return;
}

