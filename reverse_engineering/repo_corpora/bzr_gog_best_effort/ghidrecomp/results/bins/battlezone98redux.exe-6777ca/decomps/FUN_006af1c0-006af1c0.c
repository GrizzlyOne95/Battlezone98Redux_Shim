
undefined4
FUN_006af1c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_8;
  
  FUN_006ae8d0();
  local_8 = 0;
  puVar4 = param_5;
  uVar1 = WSASend(param_1,param_2,param_3,&local_8,param_4,0,0);
  iVar2 = FUN_006d8d90(uVar1,puVar4);
  iVar3 = get();
  if (iVar3 == 0x40) {
    FUN_006d8cf0(0x2746);
  }
  else {
    iVar3 = get();
    if (iVar3 == 0x4d2) {
      FUN_006d8cf0(0x274d);
    }
  }
  if (iVar2 == 0) {
    puVar4 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar4[1];
    *param_5 = *puVar4;
    param_5[1] = uVar1;
  }
  else {
    local_8 = 0xffffffff;
  }
  return local_8;
}

