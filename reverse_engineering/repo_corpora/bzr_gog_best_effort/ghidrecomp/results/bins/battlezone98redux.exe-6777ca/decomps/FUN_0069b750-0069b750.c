
void FUN_0069b750(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  void *_Memory;
  int iVar1;
  undefined4 uVar2;
  undefined1 local_d0 [200];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = 6;
  _Memory = malloc(1);
  iVar1 = FUN_00699ec0(param_1,param_2,param_3,param_4,local_d0,_Memory,uVar2);
  free(_Memory);
  if (iVar1 == 0xe) {
    FUN_0069b690(param_1,param_2,param_3,param_4,param_5,param_6);
  }
  FUN_0083e885();
  return;
}

