
void FUN_0073b130(char param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085a879;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  if (param_1 == '\0') {
    FUN_0073ad10(PTR_s_48798785219391894_008eda30,PTR_s_07d88685731696d31e7f21d49e1ccd9e_008eda2c,1)
    ;
    FUN_007d6a70("galaxy::api::Init\n");
  }
  else {
    FUN_0073ad40(PTR_s_48798785219391894_008eda30,PTR_s_07d88685731696d31e7f21d49e1ccd9e_008eda2c,
                 &DAT_02cedf80,1);
    FUN_007d6a70("galaxy::api::InitLocal\n");
  }
  FUN_0073b423();
  return;
}

