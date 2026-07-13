
undefined4 FUN_0083810b(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = strchr(param_2,0x2d);
  if (pcVar1 != (char *)0x0) {
    param_2 = pcVar1 + 1;
  }
  uVar2 = FUN_0082bd93(param_1,param_2,&DAT_008752b0,&DAT_00892134);
  uVar2 = FUN_0082cc9e(param_1,"luaopen_%s",uVar2);
  FUN_0082cf99(param_1,0xfffffffe);
  return uVar2;
}

