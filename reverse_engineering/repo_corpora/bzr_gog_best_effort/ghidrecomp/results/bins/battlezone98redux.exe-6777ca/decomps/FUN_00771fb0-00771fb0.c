
void FUN_00771fb0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  iVar1 = FUN_00732ef0(&param_1);
  if (1 < iVar1) {
    uVar2 = _Val_type<>(param_1,param_2);
    uVar2 = _Val_type<>(param_1,param_2,uVar2);
    puVar3 = (undefined4 *)
             FID_conflict__Rechecked<class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>,class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>_>
                       (local_c,param_3,param_4,param_5,uVar2);
    puVar3 = (undefined4 *)
             FID_conflict__Rechecked<class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>,class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>_>
                       (local_14,param_1,param_2,*puVar3,puVar3[1]);
    FUN_00772a00(*puVar3,puVar3[1]);
  }
  return;
}

