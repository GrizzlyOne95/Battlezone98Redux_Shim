
void FUN_00573930(short param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  char *local_10;
  
  if (param_2 == 0x14) {
    iVar1 = FUN_005771b0(param_1);
    if (iVar1 == 0) {
      pcVar4 = FUN_004bc8c0;
      FUN_0081e820(" Received game info from unknown player.  DataSize:");
      uVar2 = FUN_0081e660();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,param_2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
    }
    else {
      if ((DAT_00917f48 == 0) || (*(short *)(DAT_00917f48 + 4) == param_1)) {
        local_10 = "";
      }
      else {
        local_10 = " (HOST CHANGED)";
      }
      pcVar4 = FUN_004bc8c0;
      FUN_0081e820(" Received game info from player \'",iVar1 + 0x74,&DAT_0088406c,local_10,
                   ". DataSize:");
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_00574730(uVar2);
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_004bc590(uVar2);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,param_2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
    }
    if (DAT_00917f48 != 0) {
      *(short *)(DAT_00917f48 + 4) = param_1;
    }
    DAT_00917f44 = *param_3;
    DAT_00917f54 = param_3[1];
    DAT_00917f70 = param_3[2];
    if (DAT_00917fa4 != param_3[3]) {
      DAT_008e8d04 = param_3[3];
    }
    DAT_00917fa4 = param_3[3];
    if (DAT_008e8d04 == -1) {
      DAT_008e8d04 = param_3[3];
    }
    DAT_009175bf = *(char *)(param_3 + 4) != '\0';
    DAT_008e8c0d = *(char *)((int)param_3 + 0x11) != '\0';
  }
  return;
}

