
/* WARNING: Removing unreachable block (ram,0x006e129f) */

void FUN_006e1210(void)

{
  CDataPathProperty *pCVar1;
  undefined1 auStack_64 [16];
  undefined4 uStack_54;
  undefined4 uStack_50;
  uint uStack_4c;
  undefined1 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  CDataPathProperty local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853f10;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_48 = auStack_64;
  local_14 = uStack_4c;
  local_44 = function<>(&stack0x00000008);
  pCVar1 = local_34;
  FUN_00421ec0(pCVar1);
  uStack_50 = FUN_006f09f0(pCVar1);
  local_8._0_1_ = 1;
  uStack_54 = 0x6e1291;
  local_40 = uStack_50;
  local_3c = uStack_50;
  FUN_006f0a70();
  local_8 = (uint)local_8._1_3_ << 8;
  uStack_50 = 0x6e129d;
  CDataPathProperty::~CDataPathProperty(local_34);
  uStack_50 = 0x6e12b6;
  FUN_006ab750();
  local_8 = 0xffffffff;
  uStack_50 = 0x6e12c5;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000008);
  ExceptionList = local_10;
  uStack_4c = 0x6e12dd;
  FUN_0083e885();
  return;
}

