
void FUN_0083e610(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1,DWORD param_2)

{
  char cVar1;
  char *hMem;
  DWORD DVar2;
  undefined4 ****ppppuVar3;
  uint uVar4;
  char *pcVar5;
  char *local_38;
  undefined4 local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_30;
  char *local_2c;
  undefined4 ***local_28 [4];
  uint local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_008654a9;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_38;
  ExceptionList = &local_c;
  local_34 = 0;
  local_30 = param_1;
  local_38 = (char *)0x0;
  DVar2 = FormatMessageA(0x1300,(LPCVOID)0x0,param_2,0x400,(LPSTR)&local_38,0,(va_list *)0x0);
  hMem = local_38;
  local_2c = local_38;
  local_4 = 1;
  if (DVar2 == 0) {
    *(undefined4 *)(param_1 + 0x14) = 0xf;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *param_1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              (param_1,"Unknown error",0xd);
    local_34 = 1;
  }
  else {
    local_14 = 0xf;
    local_18 = 0;
    local_28[0] = (undefined4 ***)((uint)local_28[0] & 0xffffff00);
    if (*local_38 == '\0') {
      uVar4 = 0;
    }
    else {
      pcVar5 = local_38;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      uVar4 = (int)pcVar5 - (int)(local_38 + 1);
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               local_28,local_38,uVar4);
    local_4 = CONCAT31(local_4._1_3_,2);
    while (local_18 != 0) {
      ppppuVar3 = local_28;
      if (0xf < local_14) {
        ppppuVar3 = (undefined4 ****)local_28[0];
      }
      if (*(char *)((int)ppppuVar3 + (local_18 - 1)) != '\n') {
        ppppuVar3 = local_28;
        if (0xf < local_14) {
          ppppuVar3 = (undefined4 ****)local_28[0];
        }
        if (*(char *)((int)ppppuVar3 + (local_18 - 1)) != '\r') {
          if (local_18 != 0) {
            ppppuVar3 = local_28;
            if (0xf < local_14) {
              ppppuVar3 = (undefined4 ****)local_28[0];
            }
            if (*(char *)((int)ppppuVar3 + (local_18 - 1)) == '.') {
              std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
              erase((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_28,local_18 - 1);
            }
          }
          break;
        }
      }
      uVar4 = local_18 - 1;
      if (local_18 < uVar4) {
                    /* WARNING: Subroutine does not return */
        std::_Xout_of_range("invalid string position");
      }
      local_18 = uVar4;
      ppppuVar3 = local_28;
      if (0xf < local_14) {
        ppppuVar3 = (undefined4 ****)local_28[0];
      }
      *(undefined1 *)((int)ppppuVar3 + uVar4) = 0;
    }
    basic_string<>(local_28);
    local_34 = 1;
    if (0xf < local_14) {
      operator_delete(local_28[0]);
    }
    local_14 = 0xf;
    local_18 = 0;
    local_28[0] = (undefined4 ***)((uint)local_28[0] & 0xffffff00);
  }
  local_4 = local_4 & 0xffffff00;
  LocalFree(hMem);
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

