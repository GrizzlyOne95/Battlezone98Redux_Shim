
exception * FUN_007bb000(void)

{
  char *local_c;
  exception *local_8;
  
  local_c = (char *)FUN_0041f870();
  std::exception::exception(local_8,&local_c);
  *(undefined ***)local_8 = std::runtime_error::vftable;
  return local_8;
}

