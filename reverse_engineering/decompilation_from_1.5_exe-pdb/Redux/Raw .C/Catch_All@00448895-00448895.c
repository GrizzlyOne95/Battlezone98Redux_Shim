
undefined * Catch_All_00448895(void)

{
  char *pcVar1;
  int unaff_EBP;
  
  pcVar1 = std::exception::what(*(exception **)(unaff_EBP + -0x30));
  *(char **)(unaff_EBP + -0x38) = pcVar1;
  return &DAT_004488b6;
}

