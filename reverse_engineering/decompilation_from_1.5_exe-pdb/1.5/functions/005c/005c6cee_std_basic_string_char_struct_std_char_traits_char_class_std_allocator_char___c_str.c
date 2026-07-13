/*
 * Entry: 005c6cee
 * Name: std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::c_str
 * Namespace: std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
 * Signature: char * c_str(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * this)
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* public: char const * __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::c_str(void)const  */

char * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::c_str
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c6cee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::c_str
                     (this);
  return pcVar1;
}
