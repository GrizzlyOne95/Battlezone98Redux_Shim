
void FUN_006bb790(void)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_24 [8];
  undefined1 local_1c [12];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851338;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_004fbb60(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  puVar3 = local_1c;
  uVar2 = 2;
  puVar1 = local_24;
  FUN_00421ec0(puVar1,2,puVar3);
  FUN_006cad70(puVar1,uVar2,puVar3);
  FUN_006cadd0(local_1c);
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

