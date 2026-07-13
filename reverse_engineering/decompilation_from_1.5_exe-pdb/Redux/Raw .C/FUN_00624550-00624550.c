
void FUN_00624550(short param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  undefined4 local_8;
  
  if (DAT_00920168 != 0) {
    if (param_1 == 0) {
      if (DAT_008ec708 != 0) {
        FUN_00821390(DAT_00920168,param_2);
        FUN_007a47b0(0,param_2);
      }
    }
    else {
      iVar2 = FUN_00572b50(param_1);
      if (iVar2 == 0) {
        iVar2 = FUN_005779d0(param_1);
        if (iVar2 == 0) {
          local_8 = DAT_008ec710;
        }
        else {
          sVar1 = FUN_00572d90();
          if (param_1 == sVar1) {
            local_8 = DAT_008ec70c;
          }
          else {
            iVar2 = FUN_00577a30(param_1);
            if (iVar2 == 0) {
              iVar2 = FUN_00577a80(param_1);
              if (iVar2 == 0) {
                local_8 = DAT_008ec71c;
              }
              else {
                local_8 = DAT_008ec720;
              }
            }
            else {
              local_8 = DAT_008ec714;
            }
          }
        }
        FUN_00821450(DAT_00920168,param_2,local_8);
        FUN_007a47b0(local_8,param_2);
      }
    }
  }
  return;
}

