
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_007d43e0(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  
  if (*(int *)(param_1 + 0x140) == 0) {
    basic_string<>(&DAT_008a1ad8);
  }
  else {
    pbVar1 = Ogre::OgreTheoraVideoClip::getName(*(OgreTheoraVideoClip **)(param_1 + 0x140));
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_2,pbVar1);
  }
  return param_2;
}

