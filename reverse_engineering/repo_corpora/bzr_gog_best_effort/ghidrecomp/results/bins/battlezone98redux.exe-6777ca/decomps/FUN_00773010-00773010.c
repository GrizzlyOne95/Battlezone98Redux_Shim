
void FUN_00773010(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  uVar1 = _Val_type<>(param_1,param_2);
  puVar2 = (undefined4 *)
           FID_conflict__Rechecked<class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>,class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>_>
                     (local_c,param_3,param_4,param_5,uVar1);
  puVar2 = (undefined4 *)
           FID_conflict__Rechecked<class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>,class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>_>
                     (local_14,param_1,param_2,*puVar2,puVar2[1]);
  FUN_007734f0(*puVar2,puVar2[1]);
  return;
}

