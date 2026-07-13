
undefined4 * FUN_004d2b10(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a020;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00511720(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = FlareMineClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0x2a1e42e4,0x19d3ebc6,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x5a] = *(undefined4 *)(param_1 + 0x168);
  }
  else {
    uVar2 = FUN_00586c60(local_20,local_1c,uVar1);
    local_14[0x5a] = uVar2;
  }
  FUN_0047b6c0(0x2a1e42e4,0xcfde2fc0,local_14 + 0x5b,param_1 + 0x16c);
  FUN_00589800(0x2a1e42e4,0x682cd2b2,local_14 + 0x5f,*(undefined4 *)(param_1 + 0x17c));
  FUN_00589800(0x2a1e42e4,0xd9356908,local_14 + 0x60,*(undefined4 *)(param_1 + 0x180));
  FUN_00589800(0x2a1e42e4,0x22c3372e,local_14 + 0x61,*(undefined4 *)(param_1 + 0x184));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

