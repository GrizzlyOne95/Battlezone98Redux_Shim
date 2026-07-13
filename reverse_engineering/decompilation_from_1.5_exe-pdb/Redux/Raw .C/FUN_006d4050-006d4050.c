
/* WARNING: Removing unreachable block (ram,0x006d41ae) */

void FUN_006d4050(undefined4 param_1,undefined4 param_2)

{
  CDataPathProperty *pCVar1;
  undefined1 auStack_11c [40];
  undefined4 uStack_f4;
  undefined1 *puStack_f0;
  undefined1 *puStack_ec;
  undefined1 *puStack_e8;
  uint uStack_e4;
  undefined1 local_e0 [8];
  undefined1 local_d8 [4];
  undefined1 *local_d4;
  undefined1 local_d0 [16];
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b4;
  undefined4 local_a8;
  undefined4 local_a4;
  uint local_9c;
  undefined1 local_98 [8];
  int local_90;
  CDataPathProperty local_8c [120];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085337c;
  local_10 = ExceptionList;
  uStack_e4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_9c = 0;
  local_8 = 0;
  puStack_e8 = (undefined1 *)param_2;
  puStack_ec = local_e0;
  puStack_f0 = (undefined1 *)0x6d40a2;
  local_14 = uStack_e4;
  puStack_e8 = (undefined1 *)FUN_006ba9e0();
  puStack_ec = *(undefined1 **)(local_90 + 100);
  puStack_f0 = local_d8;
  uStack_f4 = 0x6d40bc;
  puStack_ec = (undefined1 *)select_on_container_copy_construction();
  puStack_f0 = local_98;
  uStack_f4 = 0x6d40cc;
  FUN_006dea70();
  local_8._0_1_ = 1;
  puStack_e8 = local_d0;
  puStack_ec = (undefined1 *)0x6d40f2;
  local_b4 = FUN_006d6530();
  local_8._0_1_ = 2;
  local_d4 = auStack_11c;
  local_a4 = local_b4;
  local_c0 = FUN_006deb60(auStack_11c,FUN_006d6580,local_b4,local_98,&stack0x0000000c,_1_exref);
  pCVar1 = local_8c;
  FUN_00421ec0(pCVar1);
  puStack_e8 = (undefined1 *)FUN_006debd0(pCVar1);
  local_8._0_1_ = 3;
  puStack_ec = (undefined1 *)0x6d4184;
  local_bc = puStack_e8;
  local_a8 = puStack_e8;
  FUN_00421ec0();
  puStack_ec = (undefined1 *)0x6d418b;
  FUN_006dec50();
  local_8._0_1_ = 2;
  puStack_e8 = (undefined1 *)0x6d419a;
  CDataPathProperty::~CDataPathProperty(local_8c);
  local_8._0_1_ = 1;
  puStack_e8 = (undefined1 *)0x6d41a9;
  FUN_006ca8c0();
  puStack_e8 = local_98;
  puStack_ec = (undefined1 *)0x6d4259;
  shared_ptr<>();
  local_9c = local_9c | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_e8 = (undefined1 *)0x6d4277;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  puStack_e8 = (undefined1 *)0x6d4286;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x0000000c);
  ExceptionList = local_10;
  uStack_e4 = 0x6d429e;
  FUN_0083e885();
  return;
}

