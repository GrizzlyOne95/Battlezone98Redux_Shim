
undefined4
FUN_006cfe00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [12];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00852ed0;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  local_8 = 0;
  local_18 = begin(local_2c);
  FUN_006dcc30(local_24,local_18,uVar3);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_006ca8c0();
  cVar2 = FUN_006ab7d0();
  if (cVar2 == '\0') {
    puVar4 = (undefined4 *)make_error_code(local_34,0xf);
    uVar1 = puVar4[1];
    *param_4 = *puVar4;
    param_4[1] = uVar1;
  }
  shared_ptr<>(local_24);
  local_14 = local_14 | 1;
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return param_1;
}

