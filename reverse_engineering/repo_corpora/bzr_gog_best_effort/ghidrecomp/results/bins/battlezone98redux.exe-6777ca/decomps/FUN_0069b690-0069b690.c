
void FUN_0069b690(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 *param_5,undefined4 *param_6)

{
  undefined4 uVar1;
  void *_Memory;
  int iVar2;
  undefined4 local_e0;
  undefined1 local_d0 [200];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _Memory = malloc(1);
  iVar2 = FUN_00699ec0(param_1,param_2,param_3,param_4,local_d0);
  free(_Memory);
  uVar1 = *param_2;
  if (iVar2 == 0xd) {
    local_e0 = FUN_0069b610(param_1,uVar1,param_3);
  }
  *param_5 = uVar1;
  *param_6 = local_e0;
  FUN_0083e885();
  return;
}

