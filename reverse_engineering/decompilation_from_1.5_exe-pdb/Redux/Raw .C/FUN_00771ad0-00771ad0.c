
void FUN_00771ad0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  undefined4 *puVar1;
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  puVar1 = (undefined4 *)
           FID_conflict__Rechecked<class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>,class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>_>
                     (local_c,param_3,param_4,param_5);
  puVar1 = (undefined4 *)
           FID_conflict__Rechecked<class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>,class_std::ostreambuf_iterator<wchar_t,struct_std::char_traits<wchar_t>_>_>
                     (local_14,param_1,param_2,*puVar1,puVar1[1]);
  FUN_00772610(*puVar1,puVar1[1]);
  return;
}

