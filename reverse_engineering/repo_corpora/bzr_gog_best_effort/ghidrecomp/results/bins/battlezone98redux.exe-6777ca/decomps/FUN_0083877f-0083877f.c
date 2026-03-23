
undefined4 FUN_0083877f(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  FUN_0082cd58(param_1,0x41d56a8cddc00000);
  iVar1 = FUN_00838733(param_1,0xffffffff);
  if (iVar1 != 0x55aa3377) {
    pcVar3 = "use D3DCREATE_FPU_PRESERVE with DirectX";
    if (iVar1 != 0x60000000) {
      pcVar3 = "compiled with incompatible luaconf.h";
    }
    pcVar2 = "not compiled with SWAPPED_DOUBLE";
    if (iVar1 != 0x43380000) {
      pcVar2 = pcVar3;
    }
    FUN_0082bc39(param_1,"bit library self-test failed (%s)",pcVar2);
  }
  FUN_0082c2f0(param_1,&DAT_0086ebf8,&PTR_s_tobit_008701b0);
  return 1;
}

