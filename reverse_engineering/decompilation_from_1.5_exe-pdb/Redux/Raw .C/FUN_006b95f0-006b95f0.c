
void __thiscall
FUN_006b95f0(uint param_1,basic_istream<char,struct_std::char_traits<char>_> *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  __int64 _Var4;
  undefined4 local_20c;
  char local_208 [512];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20c = 0;
  do {
    while( true ) {
      bVar1 = std::ios_base::good((ios_base *)(param_2 + *(int *)(*(int *)param_2 + 4)));
      if (!bVar1) goto LAB_006b973c;
      std::basic_istream<char,struct_std::char_traits<char>_>::getline
                (param_2,local_208,(ulonglong)param_1 << 0x20);
      _Var4 = std::basic_istream<char,struct_std::char_traits<char>_>::gcount(param_2);
      iVar2 = (int)_Var4;
      bVar1 = std::ios_base::fail((ios_base *)(param_2 + *(int *)(*(int *)param_2 + 4)));
      if ((bVar1) ||
         (bVar1 = std::ios_base::eof((ios_base *)(param_2 + *(int *)(*(int *)param_2 + 4))), bVar1))
      break;
      bVar1 = std::ios_base::bad((ios_base *)(param_2 + *(int *)(*(int *)param_2 + 4)));
      if (bVar1) goto LAB_006b973c;
      local_208[iVar2 + -1] = '\n';
      iVar3 = FUN_006b8f70(local_208,iVar2);
      local_20c = local_20c + iVar3;
      if (iVar3 != iVar2) goto LAB_006b973c;
    }
    iVar3 = FUN_006b8f70(local_208,iVar2);
    local_20c = local_20c + iVar3;
  } while (iVar3 == iVar2);
LAB_006b973c:
  FUN_0083e885();
  return;
}

