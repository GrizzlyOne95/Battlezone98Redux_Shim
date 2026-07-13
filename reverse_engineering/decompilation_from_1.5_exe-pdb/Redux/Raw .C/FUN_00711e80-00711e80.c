
void FUN_00711e80(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  CAtlBaseModule local_6c [88];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857c18;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_00417780(param_2 + 0x20,uVar1);
  local_8 = 0;
  iVar3 = param_2;
  FUN_006ff7b0(param_2 + 0x20);
  local_8._0_1_ = 1;
  uVar2 = FUN_00417780(local_6c,uVar1,uVar2,param_2,iVar3);
  FUN_00713610(uVar1,uVar2);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_00717cc0(local_6c,local_6c);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  ATL::CAtlBaseModule::~CAtlBaseModule(local_6c);
  local_8 = 0xffffffff;
  FUN_00711f70();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

