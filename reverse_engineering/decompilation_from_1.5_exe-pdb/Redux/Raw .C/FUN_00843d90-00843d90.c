
void __thiscall
FUN_00843d90(HCRYPTPROV *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> bVar1;
  uint uVar2;
  uint uVar3;
  BOOL BVar4;
  DWORD DVar5;
  uint uVar6;
  uint uVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar9;
  bool bVar10;
  DWORD local_74;
  DWORD local_70;
  HCRYPTPROV *local_6c;
  DWORD local_68;
  HCRYPTPROV *local_64;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_60 [80];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865e4b;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_74;
  ExceptionList = &local_c;
  this = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
         (param_1 + 1);
  param_1[6] = 0xf;
  param_1[5] = 0;
  *this = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  local_6c = param_1;
  local_64 = param_1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            (this,param_2,0,0xffffffff);
  local_4 = 0;
  local_74 = 0;
  do {
    local_68 = 0x50;
    BVar4 = CryptEnumProvidersA(local_74,(DWORD *)0x0,0,&local_70,(LPSTR)local_60,&local_68);
    if (BVar4 == 0) {
      DVar5 = GetLastError();
      bVar10 = DVar5 == 0x103;
LAB_00843edd:
      if (bVar10) {
        if (0xf < param_1[6]) {
          this = *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
                  this;
        }
        BVar4 = CryptAcquireContextA(local_6c,(LPCSTR)0x0,(LPCSTR)this,local_70,0xf0000040);
        if (BVar4 == 0) {
          FUN_008440f0("Could not acquire CSP context");
        }
        ExceptionList = local_c;
        FUN_0083e885();
        return;
      }
    }
    else {
      if (local_60[0] ==
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0) {
        uVar7 = 0;
      }
      else {
        pbVar8 = local_60;
        do {
          bVar1 = *pbVar8;
          pbVar8 = pbVar8 + 1;
        } while (bVar1 != (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           )0x0);
        uVar7 = (int)pbVar8 - (int)(local_60 + 1);
      }
      uVar2 = param_1[5];
      pbVar8 = this;
      if (0xf < param_1[6]) {
        pbVar8 = *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
                  this;
      }
      uVar6 = uVar7;
      if (uVar2 < uVar7) {
        uVar6 = uVar2;
      }
      if (uVar6 == 0) {
LAB_00843ed0:
        if (uVar7 <= uVar2) {
          bVar10 = uVar2 == uVar7;
          goto LAB_00843edd;
        }
      }
      else {
        pbVar9 = local_60;
        while (uVar3 = uVar6 - 4, 3 < uVar6) {
          if (*(int *)pbVar8 != *(int *)pbVar9) goto LAB_00843e96;
          pbVar8 = pbVar8 + 4;
          pbVar9 = pbVar9 + 4;
          uVar6 = uVar3;
        }
        if (uVar3 == 0xfffffffc) {
LAB_00843eca:
          uVar6 = 0;
        }
        else {
LAB_00843e96:
          bVar10 = (byte)*pbVar8 < (byte)*pbVar9;
          if ((*pbVar8 == *pbVar9) &&
             ((uVar3 == 0xfffffffd ||
              ((bVar10 = (byte)pbVar8[1] < (byte)pbVar9[1], pbVar8[1] == pbVar9[1] &&
               ((uVar3 == 0xfffffffe ||
                ((bVar10 = (byte)pbVar8[2] < (byte)pbVar9[2], pbVar8[2] == pbVar9[2] &&
                 ((uVar3 == 0xffffffff ||
                  (bVar10 = (byte)pbVar8[3] < (byte)pbVar9[3], pbVar8[3] == pbVar9[3]))))))))))))
          goto LAB_00843eca;
          uVar6 = -(uint)bVar10 | 1;
        }
        if (uVar6 == 0) goto LAB_00843ed0;
      }
    }
    local_74 = local_74 + 1;
  } while( true );
}

