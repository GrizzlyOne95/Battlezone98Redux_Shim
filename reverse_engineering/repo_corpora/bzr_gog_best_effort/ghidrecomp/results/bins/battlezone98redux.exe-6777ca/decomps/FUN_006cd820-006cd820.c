
undefined4 FUN_006cd820(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_10 [8];
  int local_8;
  
  uVar2 = FUN_006cd9f0(local_10);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    while( true ) {
      FUN_0042da60();
      local_8 = get();
      if (local_8 == 0) break;
      uVar2 = param_3[1];
      *(undefined4 *)(local_8 + 0x20) = *param_3;
      *(undefined4 *)(local_8 + 0x24) = uVar2;
      FUN_0042da60();
      FUN_006c8fb0();
      FUN_006c9000(local_8);
    }
    FUN_006cdcc0(param_1);
    uVar2 = 1;
  }
  return uVar2;
}

