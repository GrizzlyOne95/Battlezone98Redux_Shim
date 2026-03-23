
_Ref_count_base * __thiscall
FUN_0071a430(_Ref_count_base *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008547ec;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = std::_Ref_count_obj<class_websocketpp::uri>::vftable;
  iVar2 = forward<>(0x4c,param_1 + 0xc,uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (iVar2 != 0) {
    uVar3 = FUN_00417780(param_5);
    uVar4 = FUN_00417780(param_4,uVar3);
    uVar5 = FUN_00417780(param_3,uVar4);
    puVar6 = (undefined1 *)FUN_00417780(param_2,uVar5);
    FUN_006b5810(*puVar6,uVar5,uVar4,uVar3);
  }
  ExceptionList = local_10;
  return param_1;
}

