
undefined4 __thiscall FUN_0057b3b0(int *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *this;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  int *local_8;
  
  local_c = param_3 - *param_1;
  local_8 = param_1;
  uVar1 = FUN_00417780(param_4);
  FUN_0057e7f0(uVar1);
  puVar2 = (undefined4 *)FID_conflict_end(local_10);
  uVar1 = *puVar2;
  puVar3 = local_14;
  this = (_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *)
         FID_conflict_end(local_18);
  puVar2 = (undefined4 *)
           std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_>::
           operator-(this,(int)puVar3);
  uVar5 = *puVar2;
  puVar3 = local_1c;
  iVar4 = local_c;
  FID_conflict_begin(local_20);
  puVar2 = (undefined4 *)FID_conflict_operator_(puVar3,iVar4);
  FUN_0057e870(local_24,*puVar2,uVar5,uVar1);
  uVar1 = param_2;
  iVar4 = local_c;
  FID_conflict_begin(local_28);
  FID_conflict_operator_(uVar1,iVar4);
  return param_2;
}

