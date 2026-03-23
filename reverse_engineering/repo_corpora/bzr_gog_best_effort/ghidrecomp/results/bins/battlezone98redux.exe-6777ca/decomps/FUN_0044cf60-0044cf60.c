
void __thiscall FUN_0044cf60(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  char local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846680;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00448f90(param_2,param_3);
  local_8 = 0;
  *param_1 = LightRenderClass::vftable;
  if (param_2 == 0) {
    param_1[0x3d] = 2;
    param_1[0x5f] = 0;
    param_1[0x60] = 0x40c90fdb;
    param_1[0x61] = 0x40c90fdb;
  }
  else {
    FUN_00589430(param_1 + 0x25);
    local_8 = CONCAT31(local_8._1_3_,1);
    uVar2 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar1);
    FUN_00449f30(uVar2,0x57a9a9f1,local_54,0);
    iVar3 = _strnicmp(local_54,"point",5);
    if (iVar3 == 0) {
      param_1[0x5f] = 0;
    }
    else {
      iVar3 = _strnicmp(local_54,"spot",4);
      if (iVar3 == 0) {
        param_1[0x5f] = 2;
      }
      else {
        param_1[0x5f] = *(undefined4 *)(param_2 + 0x17c);
      }
    }
    FUN_00589800(uVar2,0xce3ae5c,param_1 + 0x60,*(undefined4 *)(param_2 + 0x180));
    FUN_00589800(uVar2,0xc07a1044,param_1 + 0x61,*(undefined4 *)(param_2 + 0x184));
    local_8 = local_8 & 0xffffff00;
    FUN_00589530();
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

