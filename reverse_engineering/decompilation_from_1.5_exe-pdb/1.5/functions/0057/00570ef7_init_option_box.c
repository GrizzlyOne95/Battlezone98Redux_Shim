/*
 * Entry: 00570ef7
 * Name: init_option_box
 * Namespace: Global
 * Signature: int init_option_box(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl init_option_box(void)

{
  read_text_label("option_box","flat",flatOption);
  read_text_label("option_box","full",fullOption);
  read_text_label("option_box","solid",solidOption);
  read_text_label("option_box","smooth",smoothOption);
  read_text_label("option_box","textured",texturedOption);
  read_text_label("option_box","low_res",lowResOption);
  read_text_label("option_box","hi_res",hiResOption);
  read_text_label("option_box","mixed",mixedOption);
  read_text_label("option_box","off",offOption);
  read_text_label("option_box","on",onOption);
  read_text_label("option_box","veryeasy",veryeasyOption);
  read_text_label("option_box","easy",easyOption);
  read_text_label("option_box","med",medOption);
  read_text_label("option_box","hard",hardOption);
  read_text_label("option_box","veryhard",veryhardOption);
  return 1;
}
