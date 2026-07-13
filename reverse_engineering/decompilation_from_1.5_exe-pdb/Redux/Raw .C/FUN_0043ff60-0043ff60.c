
undefined4 FUN_0043ff60(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_28 [28];
  undefined8 local_c;
  
  local_c = FUN_00437330();
  puVar1 = (undefined4 *)FUN_00689f10(local_28,local_c);
  puVar3 = param_1;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00689fa0(param_1,0,0,(int)local_c + -1,local_c._4_4_ + -1);
  return 1;
}

