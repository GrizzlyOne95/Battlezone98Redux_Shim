
undefined4 *
FUN_00757140(undefined4 *param_1,undefined1 *param_2,undefined1 *param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  while (param_2 != param_3) {
    uVar1 = FUN_00757630(*param_2);
    puVar2 = (undefined1 *)FUN_00421ec0();
    *puVar2 = uVar1;
    param_2 = param_2 + 1;
    FUN_004f5330();
  }
  *param_1 = param_4;
  return param_1;
}

