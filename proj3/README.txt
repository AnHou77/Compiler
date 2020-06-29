My Parser change:

1. 創一個jasm檔存產生的 java-bytecode
2. 於 Rule 中產生對應的 bytecode
3. 新增判斷 Global variable 的 Flag
4. 新增兩個 Stack，以紀錄 IF & WHILE 對應的 Label
5. st.h & st.cpp 實做數個產生 bytecode 的 function