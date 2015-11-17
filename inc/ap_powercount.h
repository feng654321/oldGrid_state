

#ifndef AP_POWERCOUNT_H
    #define AP_POWERCOUNT_H
    
#ifdef  AP_POWERCOUNT_GLOBALS
    #define AP_POWERCOUNT_EXT
#else
    #define AP_POWERCOUNT_EXT extern
#endif  








#define PT_KWH_TOTAL            (203)
#define BYTES_PER_PT_KWH        (5)
#define BYTES_KWH_TOTAL     (PT_KWH_TOTAL*BYTES_PER_PT_KWH)

#define BYTES_KWH_USE_TOTAL     (25)
#define BYTES_KWH_F_AND_R_TOTAL (25)

#define PT_KWH_ALL_START 0 // dang qian dian liang shu ju qi shi 
#define PT_KWH_C_ALL 0 // dang qian zu he you gong zong dian liang 
#define PT_KWH_C_F1 1 // dang qian zu he you gong jian (fei lv 1)dian liang 
#define PT_KWH_C_F2 2 // dang qian zu he you gong feng (fei lv 2)dian liang 
#define PT_KWH_C_F3 3 // dang qian zu he you gong ping (fei lv 3)dian liang 
#define PT_KWH_C_F4 4 // dang qian zu he you gong gu (fei lv 4)dian liang 
#define PT_KWH_C_F5 5 // dang qian zu he you gong fei lv 5dian liang 
#define PT_KWH_C_F6 6 // dang qian zu he you gong fei lv 6dian liang 
#define PT_KWH_C_F7 7 // dang qian zu he you gong fei lv 7dian liang 
#define PT_KWH_C_F8 8 // dang qian zu he you gong fei lv 8dian liang 
#define PT_KWH_C_F9 9 // dang qian zu he you gong fei lv 9dian liang 
#define PT_KWH_C_F10 10 // dang qian zu he you gong fei lv 10dian liang 
#define PT_KWH_C_F11 11 // dang qian zu he you gong fei lv 11dian liang 
#define PT_KWH_C_F12 12 // dang qian zu he you gong fei lv 12dian liang 
#define PT_KWH_C_F13 13 // dang qian zu he you gong fei lv 13dian liang 
#define PT_KWH_C_F14 14 // dang qian zu he you gong fei lv 14dian liang 
#define PT_KWH_F_ALL 15 // dang qian zheng xiang you gong zong dian liang 
#define PT_KWH_F_F1 16 // dang qian zheng xiang you gong jian (fei lv 1)dian liang 
#define PT_KWH_F_F2 17 // dang qian zheng xiang you gong feng (fei lv 2)dian liang 
#define PT_KWH_F_F3 18 // dang qian zheng xiang you gong ping (fei lv 3)dian liang 
#define PT_KWH_F_F4 19 // dang qian zheng xiang you gong gu (fei lv 4)dian liang 
#define PT_KWH_F_F5 20 // dang qian zheng xiang you gong fei lv 5dian liang 
#define PT_KWH_F_F6 21 // dang qian zheng xiang you gong fei lv 6dian liang 
#define PT_KWH_F_F7 22 // dang qian zheng xiang you gong fei lv 7dian liang 
#define PT_KWH_F_F8 23 // dang qian zheng xiang you gong fei lv 8dian liang 
#define PT_KWH_F_F9 24 // dang qian zheng xiang you gong fei lv 9dian liang 
#define PT_KWH_F_F10 25 // dang qian zheng xiang you gong fei lv 10dian liang 
#define PT_KWH_F_F11 26 // dang qian zheng xiang you gong fei lv 11dian liang 
#define PT_KWH_F_F12 27 // dang qian zheng xiang you gong fei lv 12dian liang 
#define PT_KWH_F_F13 28 // dang qian zheng xiang you gong fei lv 13dian liang 
#define PT_KWH_F_F14 29 // dang qian zheng xiang you gong fei lv 14dian liang 
#define PT_KWH_R_ALL 30 // dang qian fan xiang you gong zong dian liang 
#define PT_KWH_R_F1 31 // dang qian fan xiang you gong jian (fei lv 1)dian liang 
#define PT_KWH_R_F2 32 // dang qian fan xiang you gong feng (fei lv 2)dian liang 
#define PT_KWH_R_F3 33 // dang qian fan xiang you gong ping (fei lv 3)dian liang 
#define PT_KWH_R_F4 34 // dang qian fan xiang you gong gu (fei lv 4)dian liang 
#define PT_KWH_R_F5 35 // dang qian fan xiang you gong fei lv 5dian liang 
#define PT_KWH_R_F6 36 // dang qian fan xiang you gong fei lv 6dian liang 
#define PT_KWH_R_F7 37 // dang qian fan xiang you gong fei lv 7dian liang 
#define PT_KWH_R_F8 38 // dang qian fan xiang you gong fei lv 8dian liang 
#define PT_KWH_R_F9 39 // dang qian fan xiang you gong fei lv 9dian liang 
#define PT_KWH_R_F10 40 // dang qian fan xiang you gong fei lv 10dian liang 
#define PT_KWH_R_F11 41 // dang qian fan xiang you gong fei lv 11dian liang 
#define PT_KWH_R_F12 42 // dang qian fan xiang you gong fei lv 12dian liang 
#define PT_KWH_R_F13 43 // dang qian fan xiang you gong fei lv 13dian liang 
#define PT_KWH_R_F14 44 // dang qian fan xiang you gong fei lv 14dian liang 
#define PT_KVARH_C1_ALL 45 // dang qian zu he wu gong 1zong dian liang 
#define PT_KVARH_C1_F1 46 // dang qian zu he wu gong 1jian (fei lv 1)dian liang 
#define PT_KVARH_C1_F2 47 // dang qian zu he wu gong 1feng (fei lv 2)dian liang 
#define PT_KVARH_C1_F3 48 // dang qian zu he wu gong 1ping (fei lv 3)dian liang 
#define PT_KVARH_C1_F4 49 // dang qian zu he wu gong 1gu (fei lv 4)dian liang 
#define PT_KVARH_C1_F5 50 // dang qian zu he wu gong 1fei lv 5dian liang 
#define PT_KVARH_C1_F6 51 // dang qian zu he wu gong 1fei lv 6dian liang 
#define PT_KVARH_C1_F7 52 // dang qian zu he wu gong 1fei lv 7dian liang 
#define PT_KVARH_C1_F8 53 // dang qian zu he wu gong 1fei lv 8dian liang 
#define PT_KVARH_C1_F9 54 // dang qian zu he wu gong 1fei lv 9dian liang 
#define PT_KVARH_C1_F10 55 // dang qian zu he wu gong 1fei lv 10dian liang 
#define PT_KVARH_C1_F11 56 // dang qian zu he wu gong 1fei lv 11dian liang 
#define PT_KVARH_C1_F12 57 // dang qian zu he wu gong 1fei lv 12dian liang 
#define PT_KVARH_C1_F13 58 // dang qian zu he wu gong 1fei lv 13dian liang 
#define PT_KVARH_C1_F14 59 // dang qian zu he wu gong 1fei lv 14dian liang 
#define PT_KVARH_C2_ALL 60 // dang qian zu he wu gong 2zong dian liang 
#define PT_KVARH_C2_F1 61 // dang qian zu he wu gong 2jian (fei lv 1)dian liang 
#define PT_KVARH_C2_F2 62 // dang qian zu he wu gong 2feng (fei lv 2)dian liang 
#define PT_KVARH_C2_F3 63 // dang qian zu he wu gong 2ping (fei lv 3)dian liang 
#define PT_KVARH_C2_F4 64 // dang qian zu he wu gong 2gu (fei lv 4)dian liang 
#define PT_KVARH_C2_F5 65 // dang qian zu he wu gong 2fei lv 5dian liang 
#define PT_KVARH_C2_F6 66 // dang qian zu he wu gong 2fei lv 6dian liang 
#define PT_KVARH_C2_F7 67 // dang qian zu he wu gong 2fei lv 7dian liang 
#define PT_KVARH_C2_F8 68 // dang qian zu he wu gong 2fei lv 8dian liang 
#define PT_KVARH_C2_F9 69 // dang qian zu he wu gong 2fei lv 9dian liang 
#define PT_KVARH_C2_F10 70 // dang qian zu he wu gong 2fei lv 10dian liang 
#define PT_KVARH_C2_F11 71 // dang qian zu he wu gong 2fei lv 11dian liang 
#define PT_KVARH_C2_F12 72 // dang qian zu he wu gong 2fei lv 12dian liang 
#define PT_KVARH_C2_F13 73 // dang qian zu he wu gong 2fei lv 13dian liang 
#define PT_KVARH_C2_F14 74 // dang qian zu he wu gong 2fei lv 14dian liang 
#define PT_KVARH_Q1_ALL 75 // dang qian 1xiang xian wu gong zong dian liang 
#define PT_KVARH_Q1_F1 76 // dang qian 1xiang xian wu gong jian (fei lv 1)dian liang 
#define PT_KVARH_Q1_F2 77 // dang qian 1xiang xian wu gong feng (fei lv 2)dian liang 
#define PT_KVARH_Q1_F3 78 // dang qian 1xiang xian wu gong ping (fei lv 3)dian liang 
#define PT_KVARH_Q1_F4 79 // dang qian 1xiang xian wu gong gu (fei lv 4)dian liang 
#define PT_KVARH_Q1_F5 80 // dang qian 1xiang xian wu gong fei lv 5dian liang 
#define PT_KVARH_Q1_F6 81 // dang qian 1xiang xian wu gong fei lv 6dian liang 
#define PT_KVARH_Q1_F7 82 // dang qian 1xiang xian wu gong fei lv 7dian liang 
#define PT_KVARH_Q1_F8 83 // dang qian 1xiang xian wu gong fei lv 8dian liang 
#define PT_KVARH_Q1_F9 84 // dang qian 1xiang xian wu gong fei lv 9dian liang 
#define PT_KVARH_Q1_F10 85 // dang qian 1xiang xian wu gong fei lv 10dian liang 
#define PT_KVARH_Q1_F11 86 // dang qian 1xiang xian wu gong fei lv 11dian liang 
#define PT_KVARH_Q1_F12 87 // dang qian 1xiang xian wu gong fei lv 12dian liang 
#define PT_KVARH_Q1_F13 88 // dang qian 1xiang xian wu gong fei lv 13dian liang 
#define PT_KVARH_Q1_F14 89 // dang qian 1xiang xian wu gong fei lv 14dian liang 
#define PT_KVARH_Q2_ALL 90 // dang qian 2xiang xian wu gong zong dian liang 
#define PT_KVARH_Q2_F1 91 // dang qian 2xiang xian wu gong jian (fei lv 1)dian liang 
#define PT_KVARH_Q2_F2 92 // dang qian 2xiang xian wu gong feng (fei lv 2)dian liang 
#define PT_KVARH_Q2_F3 93 // dang qian 2xiang xian wu gong ping (fei lv 3)dian liang 
#define PT_KVARH_Q2_F4 94 // dang qian 2xiang xian wu gong gu (fei lv 4)dian liang 
#define PT_KVARH_Q2_F5 95 // dang qian 2xiang xian wu gong fei lv 5dian liang 
#define PT_KVARH_Q2_F6 96 // dang qian 2xiang xian wu gong fei lv 6dian liang 
#define PT_KVARH_Q2_F7 97 // dang qian 2xiang xian wu gong fei lv 7dian liang 
#define PT_KVARH_Q2_F8 98 // dang qian 2xiang xian wu gong fei lv 8dian liang 
#define PT_KVARH_Q2_F9 99 // dang qian 2xiang xian wu gong fei lv 9dian liang 
#define PT_KVARH_Q2_F10 100 // dang qian 2xiang xian wu gong fei lv 10dian liang 
#define PT_KVARH_Q2_F11 101 // dang qian 2xiang xian wu gong fei lv 11dian liang 
#define PT_KVARH_Q2_F12 102 // dang qian 2xiang xian wu gong fei lv 12dian liang 
#define PT_KVARH_Q2_F13 103 // dang qian 2xiang xian wu gong fei lv 13dian liang 
#define PT_KVARH_Q2_F14 104 // dang qian 2xiang xian wu gong fei lv 14dian liang 
#define PT_KVARH_Q3_ALL 105 // dang qian 3xiang xian wu gong zong dian liang 
#define PT_KVARH_Q3_F1 106 // dang qian 3xiang xian wu gong jian (fei lv 1)dian liang 
#define PT_KVARH_Q3_F2 107 // dang qian 3xiang xian wu gong feng (fei lv 2)dian liang 
#define PT_KVARH_Q3_F3 108 // dang qian 3xiang xian wu gong ping (fei lv 3)dian liang 
#define PT_KVARH_Q3_F4 109 // dang qian 3xiang xian wu gong gu (fei lv 4)dian liang 
#define PT_KVARH_Q3_F5 110 // dang qian 3xiang xian wu gong fei lv 5dian liang 
#define PT_KVARH_Q3_F6 111 // dang qian 3xiang xian wu gong fei lv 6dian liang 
#define PT_KVARH_Q3_F7 112 // dang qian 3xiang xian wu gong fei lv 7dian liang 
#define PT_KVARH_Q3_F8 113 // dang qian 3xiang xian wu gong fei lv 8dian liang 
#define PT_KVARH_Q3_F9 114 // dang qian 3xiang xian wu gong fei lv 9dian liang 
#define PT_KVARH_Q3_F10 115 // dang qian 3xiang xian wu gong fei lv 10dian liang 
#define PT_KVARH_Q3_F11 116 // dang qian 3xiang xian wu gong fei lv 11dian liang 
#define PT_KVARH_Q3_F12 117 // dang qian 3xiang xian wu gong fei lv 12dian liang 
#define PT_KVARH_Q3_F13 118 // dang qian 3xiang xian wu gong fei lv 13dian liang 
#define PT_KVARH_Q3_F14 119 // dang qian 3xiang xian wu gong fei lv 14dian liang 
#define PT_KVARH_Q4_ALL 120 // dang qian 4xiang xian wu gong zong dian liang 
#define PT_KVARH_Q4_F1 121 // dang qian 4xiang xian wu gong jian (fei lv 1)dian liang 
#define PT_KVARH_Q4_F2 122 // dang qian 4xiang xian wu gong feng (fei lv 2)dian liang 
#define PT_KVARH_Q4_F3 123 // dang qian 4xiang xian wu gong ping (fei lv 3)dian liang 
#define PT_KVARH_Q4_F4 124 // dang qian 4xiang xian wu gong gu (fei lv 4)dian liang 
#define PT_KVARH_Q4_F5 125 // dang qian 4xiang xian wu gong fei lv 5dian liang 
#define PT_KVARH_Q4_F6 126 // dang qian 4xiang xian wu gong fei lv 6dian liang 
#define PT_KVARH_Q4_F7 127 // dang qian 4xiang xian wu gong fei lv 7dian liang 
#define PT_KVARH_Q4_F8 128 // dang qian 4xiang xian wu gong fei lv 8dian liang 
#define PT_KVARH_Q4_F9 129 // dang qian 4xiang xian wu gong fei lv 9dian liang 
#define PT_KVARH_Q4_F10 130 // dang qian 4xiang xian wu gong fei lv 10dian liang 
#define PT_KVARH_Q4_F11 131 // dang qian 4xiang xian wu gong fei lv 11dian liang 
#define PT_KVARH_Q4_F12 132 // dang qian 4xiang xian wu gong fei lv 12dian liang 
#define PT_KVARH_Q4_F13 133 // dang qian 4xiang xian wu gong fei lv 13dian liang 
#define PT_KVARH_Q4_F14 134 // dang qian 4xiang xian wu gong fei lv 14dian liang 
#define PT_KVAH_F_ALL 135 // dang qian zheng xiang shi zai zong dian liang 
#define PT_KVAH_F_F1 136 // dang qian zheng xiang shi zai jian (fei lv 1)dian liang 
#define PT_KVAH_F_F2 137 // dang qian zheng xiang shi zai feng (fei lv 2)dian liang 
#define PT_KVAH_F_F3 138 // dang qian zheng xiang shi zai ping (fei lv 3)dian liang 
#define PT_KVAH_F_F4 139 // dang qian zheng xiang shi zai gu (fei lv 4)dian liang 
#define PT_KVAH_F_F5 140 // dang qian zheng xiang shi zai fei lv 5dian liang 
#define PT_KVAH_F_F6 141 // dang qian zheng xiang shi zai fei lv 6dian liang 
#define PT_KVAH_F_F7 142 // dang qian zheng xiang shi zai fei lv 7dian liang 
#define PT_KVAH_F_F8 143 // dang qian zheng xiang shi zai fei lv 8dian liang 
#define PT_KVAH_F_F9 144 // dang qian zheng xiang shi zai fei lv 9dian liang 
#define PT_KVAH_F_F10 145 // dang qian zheng xiang shi zai fei lv 10dian liang 
#define PT_KVAH_F_F11 146 // dang qian zheng xiang shi zai fei lv 11dian liang 
#define PT_KVAH_F_F12 147 // dang qian zheng xiang shi zai fei lv 12dian liang 
#define PT_KVAH_F_F13 148 // dang qian zheng xiang shi zai fei lv 13dian liang 
#define PT_KVAH_F_F14 149 // dang qian zheng xiang shi zai fei lv 14dian liang 
#define PT_KVAH_R_ALL 150 // dang qian fan xiang shi zai zong dian liang 
#define PT_KVAH_R_F1 151 // dang qian fan xiang shi zai jian (fei lv 1)dian liang 
#define PT_KVAH_R_F2 152 // dang qian fan xiang shi zai feng (fei lv 2)dian liang 
#define PT_KVAH_R_F3 153 // dang qian fan xiang shi zai ping (fei lv 3)dian liang 
#define PT_KVAH_R_F4 154 // dang qian fan xiang shi zai gu (fei lv 4)dian liang 
#define PT_KVAH_R_F5 155 // dang qian fan xiang shi zai fei lv 5dian liang 
#define PT_KVAH_R_F6 156 // dang qian fan xiang shi zai fei lv 6dian liang 
#define PT_KVAH_R_F7 157 // dang qian fan xiang shi zai fei lv 7dian liang 
#define PT_KVAH_R_F8 158 // dang qian fan xiang shi zai fei lv 8dian liang 
#define PT_KVAH_R_F9 159 // dang qian fan xiang shi zai fei lv 9dian liang 
#define PT_KVAH_R_F10 160 // dang qian fan xiang shi zai fei lv 10dian liang 
#define PT_KVAH_R_F11 161 // dang qian fan xiang shi zai fei lv 11dian liang 
#define PT_KVAH_R_F12 162 // dang qian fan xiang shi zai fei lv 12dian liang 
#define PT_KVAH_R_F13 163 // dang qian fan xiang shi zai fei lv 13dian liang 
#define PT_KVAH_R_F14 164 // dang qian fan xiang shi zai fei lv 14dian liang 
#define PT_KWH_LOST_COPPER_ALL 165 // tong sun you gong zong dian neng bu chang liang 
#define PT_KWH_LOST_IRON_ALL 166 // tie sun you gong zong dian neng bu chang liang 
#define PT_KWH_A_F_ALL 167 // dang qian Axiang zheng xiang you gong dian liang 
#define PT_KWH_A_R_ALL 168 // dang qian Axiang fan xiang you gong dian liang 
#define PT_KVARH_A_C1_ALL 169 // dang qian Axiang zu he wu gong 1dian liang 
#define PT_KVARH_A_C2_ALL 170 // dang qian Axiang zu he wu gong 2dian liang 
#define PT_KVARH_A_Q1_ALL 171 // dang qian Axiang 1xiang xian wu gong dian liang 
#define PT_KVARH_A_Q2_ALL 172 // dang qian Axiang 2xiang xian wu gong dian liang 
#define PT_KVARH_A_Q3_ALL 173 // dang qian Axiang 3xiang xian wu gong dian liang 
#define PT_KVARH_A_Q4_ALL 174 // dang qian Axiang 4xiang xian wu gong dian liang 
#define PT_KVAH_A_F_ALL 175 // dang qian Axiang zheng xiang shi zai dian liang 
#define PT_KVAH_A_R_ALL 176 // dang qian Axiang fan xiang shi zai dian liang 
#define PT_KWH_A_LOST_COPPER_ALL 177 // dang qian Axiang tong sun you gong dian neng bu chang liang 
#define PT_KWH_A_LOST_IRON_ALL 178 // dang qian Axiang tie sun you gong dian neng bu chang liang 
#define PT_KWH_B_F_ALL 179 // dang qian Bxiang zheng xiang you gong dian liang 
#define PT_KWH_B_R_ALL 180 // dang qian Bxiang fan xiang you gong dian liang 
#define PT_KVARH_B_C1_ALL 181 // dang qian Bxiang zu he wu gong 1dian liang 
#define PT_KVARH_B_C2_ALL 182 // dang qian Bxiang zu he wu gong 2dian liang 
#define PT_KVARH_B_Q1_ALL 183 // dang qian Bxiang 1xiang xian wu gong dian liang 
#define PT_KVARH_B_Q2_ALL 184 // dang qian Bxiang 2xiang xian wu gong dian liang 
#define PT_KVARH_B_Q3_ALL 185 // dang qian Bxiang 3xiang xian wu gong dian liang 
#define PT_KVARH_B_Q4_ALL 186 // dang qian Bxiang 4xiang xian wu gong dian liang 
#define PT_KVAH_B_F_ALL 187 // dang qian Bxiang zheng xiang shi zai dian liang 
#define PT_KVAH_B_R_ALL 188 // dang qian Bxiang fan xiang shi zai dian liang 
#define PT_KWH_B_LOST_COPPER_ALL 189 // dang qian Bxiang tong sun you gong dian neng bu chang liang 
#define PT_KWH_B_LOST_IRON_ALL 190 // dang qian Bxiang tie sun you gong dian neng bu chang liang 
#define PT_KWH_C_F_ALL 191 // dang qian Cxiang zheng xiang you gong dian liang 
#define PT_KWH_C_R_ALL 192 // dang qian Cxiang fan xiang you gong dian liang 
#define PT_KVARH_C_C1_ALL 193 // dang qian Cxiang zu he wu gong 1dian liang 
#define PT_KVARH_C_C2_ALL 194 // dang qian Cxiang zu he wu gong 2dian liang 
#define PT_KVARH_C_Q1_ALL 195 // dang qian Cxiang 1xiang xian wu gong dian liang 
#define PT_KVARH_C_Q2_ALL 196 // dang qian Cxiang 2xiang xian wu gong dian liang 
#define PT_KVARH_C_Q3_ALL 197 // dang qian Cxiang 3xiang xian wu gong dian liang 
#define PT_KVARH_C_Q4_ALL 198 // dang qian Cxiang 4xiang xian wu gong dian liang 
#define PT_KVAH_C_F_ALL 199 // dang qian Cxiang zheng xiang shi zai dian liang 
#define PT_KVAH_C_R_ALL 200 // dang qian Cxiang fan xiang shi zai dian liang 
#define PT_KWH_C_LOST_COPPER_ALL 201 // dang qian Cxiang tong sun you gong dian neng bu chang liang 
#define PT_KWH_C_LOST_IRON_ALL 202 // dang qian Cxiang tie sun you gong dian neng bu chang liang 

#define PT_KWH_USE_ALL  203  
#define PT_KWH_USE_ZJF  204  



#define PTADDFLG_KWH_ALL_START 49 // dang qian dian liang shu ju qi shi    
#define PTADDFLG_KWH_C_ALL 0 // dang qian zu he you gong zong dian liang   
#define PTADDFLG_KWH_F_ALL 1 // dang qian zheng xiang you gong zong dian liang   
#define PTADDFLG_KWH_R_ALL 2 // dang qian fan xiang you gong zong dian liang   
#define PTADDFLG_KVARH_C1_ALL 3 // dang qian zu he wu gong 1zong dian liang   
#define PTADDFLG_KVARH_C2_ALL 4 // dang qian zu he wu gong 2zong dian liang   
#define PTADDFLG_KVARH_Q1_ALL 5 // dang qian 1xiang xian wu gong zong dian liang   
#define PTADDFLG_KVARH_Q2_ALL 6 // dang qian 2xiang xian wu gong zong dian liang   
#define PTADDFLG_KVARH_Q3_ALL 7 // dang qian 3xiang xian wu gong zong dian liang   
#define PTADDFLG_KVARH_Q4_ALL 8 // dang qian 4xiang xian wu gong zong dian liang   
#define PTADDFLG_KVAH_F_ALL 9 // dang qian zheng xiang shi zai zong dian liang   
#define PTADDFLG_KVAH_R_ALL 10 // dang qian fan xiang shi zai zong dian liang   
#define PTADDFLG_KWH_LOST_COPPER_ALL 11 // tong sun you gong zong dian neng bu chang liang  
#define PTADDFLG_KWH_LOST_IRON_ALL 12 // tie sun you gong zong dian neng bu chang liang  
#define PTADDFLG_KWH_A_F_ALL 13 // dang qian Axiang zheng xiang you gong dian liang   
#define PTADDFLG_KWH_A_R_ALL 14 // dang qian Axiang fan xiang you gong dian liang   
#define PTADDFLG_KVARH_A_C1_ALL 15 // dang qian Axiang zu he wu gong 1dian liang   
#define PTADDFLG_KVARH_A_C2_ALL 16 // dang qian Axiang zu he wu gong 2dian liang   
#define PTADDFLG_KVARH_A_Q1_ALL 17 // dang qian Axiang 1xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_A_Q2_ALL 18 // dang qian Axiang 2xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_A_Q3_ALL 19 // dang qian Axiang 3xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_A_Q4_ALL 20 // dang qian Axiang 4xiang xian wu gong dian liang   
#define PTADDFLG_KVAH_A_F_ALL 21 // dang qian Axiang zheng xiang shi zai dian liang   
#define PTADDFLG_KVAH_A_R_ALL 22 // dang qian Axiang fan xiang shi zai dian liang   
#define PTADDFLG_KWH_A_LOST_COPPER_ALL 23 // dang qian Axiang tong sun you gong dian neng bu chang liang
#define PTADDFLG_KWH_A_LOST_IRON_ALL 24 // dang qian Axiang tie sun you gong dian neng bu chang liang
#define PTADDFLG_KWH_B_F_ALL 25 // dang qian Bxiang zheng xiang you gong dian liang   
#define PTADDFLG_KWH_B_R_ALL 26 // dang qian Bxiang fan xiang you gong dian liang   
#define PTADDFLG_KVARH_B_C1_ALL 27 // dang qian Bxiang zu he wu gong 1dian liang   
#define PTADDFLG_KVARH_B_C2_ALL 28 // dang qian Bxiang zu he wu gong 2dian liang   
#define PTADDFLG_KVARH_B_Q1_ALL 29 // dang qian Bxiang 1xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_B_Q2_ALL 30 // dang qian Bxiang 2xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_B_Q3_ALL 31 // dang qian Bxiang 3xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_B_Q4_ALL 32 // dang qian Bxiang 4xiang xian wu gong dian liang   
#define PTADDFLG_KVAH_B_F_ALL 33 // dang qian Bxiang zheng xiang shi zai dian liang   
#define PTADDFLG_KVAH_B_R_ALL 34 // dang qian Bxiang fan xiang shi zai dian liang   
#define PTADDFLG_KWH_B_LOST_COPPER_ALL 35 // dang qian Bxiang tong sun you gong dian neng bu chang liang
#define PTADDFLG_KWH_B_LOST_IRON_ALL 36 // dang qian Bxiang tie sun you gong dian neng bu chang liang
#define PTADDFLG_KWH_C_F_ALL 37 // dang qian Cxiang zheng xiang you gong dian liang   
#define PTADDFLG_KWH_C_R_ALL 38 // dang qian Cxiang fan xiang you gong dian liang   
#define PTADDFLG_KVARH_C_C1_ALL 39 // dang qian Cxiang zu he wu gong 1dian liang   
#define PTADDFLG_KVARH_C_C2_ALL 40 // dang qian Cxiang zu he wu gong 2dian liang   
#define PTADDFLG_KVARH_C_Q1_ALL 41 // dang qian Cxiang 1xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_C_Q2_ALL 42 // dang qian Cxiang 2xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_C_Q3_ALL 43 // dang qian Cxiang 3xiang xian wu gong dian liang   
#define PTADDFLG_KVARH_C_Q4_ALL 44 // dang qian Cxiang 4xiang xian wu gong dian liang   
#define PTADDFLG_KVAH_C_F_ALL 45 // dang qian Cxiang zheng xiang shi zai dian liang   
#define PTADDFLG_KVAH_C_R_ALL 46 // dang qian Cxiang fan xiang shi zai dian liang   
#define PTADDFLG_KWH_C_LOST_COPPER_ALL 47 // dang qian Cxiang tong sun you gong dian neng bu chang liang
#define PTADDFLG_KWH_C_LOST_IRON_ALL 48 // dang qian Cxiang tie sun you gong dian neng bu chang liang
  

//目前不支持的电量类型定义
//#define RAM_KVARH_A_C1_ALL RAM_DLT_UNSUPPORT_DATA // 5 byte XXXXXX.XXXX BCD 当前A相组合无功1电量
//#define RAM_KVARH_A_C2_ALL RAM_DLT_UNSUPPORT_DATA // 5 byte XXXXXX.XXXX BCD 当前A相组合无功2电量
//#define RAM_KVARH_B_C1_ALL RAM_DLT_UNSUPPORT_DATA // 5 byte XXXXXX.XXXX BCD 当前B相组合无功1电量
//#define RAM_KVARH_B_C2_ALL RAM_DLT_UNSUPPORT_DATA // 5 byte XXXXXX.XXXX BCD 当前B相组合无功2电量
//#define RAM_KVARH_C_C1_ALL RAM_DLT_UNSUPPORT_DATA // 5 byte XXXXXX.XXXX BCD 当前C相组合无功1电量
//#define RAM_KVARH_C_C2_ALL RAM_DLT_UNSUPPORT_DATA // 5 byte XXXXXX.XXXX BCD 当前C相组合无功2电量





#if 0

#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
AP_POWERCOUNT_EXT UN_U8_PARAM PowerAddFlg[16];
#else
AP_POWERCOUNT_EXT UN_U8_PARAM PowerAddFlg[13];
#endif 

#define RFLAG_KWH_C_ADD     PowerAddFlg[0].Bits.b0  // ZZ 组合有功增加 aa
#define RFLAG_KWH_C_SUB     PowerAddFlg[0].Bits.b1  // ZZ 组合有功减少 aa

#define RFLAG_KWH_F_ADD     PowerAddFlg[1].Bits.b0  // ZZ 正向有功 aa
#define RFLAG_KWH_R_ADD     PowerAddFlg[1].Bits.b1  // ZZ 反向有功 aa

#define RFLAG_KVARH_C1_ADD  PowerAddFlg[1].Bits.b2  // ZZ  组合1无功增加     aa
#define RFLAG_KVARH_C1_SUB  PowerAddFlg[1].Bits.b3  // ZZ  组合1无功减少     aa
#define RFLAG_KVARH_C2_ADD  PowerAddFlg[1].Bits.b4  // ZZ  组合2无功增加     aa
#define RFLAG_KVARH_C2_SUB  PowerAddFlg[1].Bits.b5  // ZZ  组合2无功减少     aa

#define RFLAG_KVARH_Q1_ADD       PowerAddFlg[2].Bits.b0 // ZZ  1象限无功增加     aa
#define RFLAG_KVARH_Q2_ADD       PowerAddFlg[2].Bits.b1 // ZZ  2象限无功增加     aa
#define RFLAG_KVARH_Q3_ADD       PowerAddFlg[2].Bits.b2 // ZZ  3象限无功增加     aa
#define RFLAG_KVARH_Q4_ADD       PowerAddFlg[2].Bits.b3     // ZZ  4象限无功增加     aa

#define RFLAG_KVAH_F_ADD        PowerAddFlg[3].Bits.b0  // ZZ  正向视在     aa
#define RFLAG_KVAH_R_ADD        PowerAddFlg[3].Bits.b1  // ZZ  反向视在     aa

#define RFLAG_KWH_LOST_COPPER       PowerAddFlg[3].Bits.b2  // ZZ  铜损电量     aa
#define RFLAG_KWH_LOST_IRON     PowerAddFlg[3].Bits.b3  // ZZ  铁损电量     aa





#define RFLAG_KWH_A_F_ADD           PowerAddFlg[4].Bits.b0  // ZZ       aa
#define RFLAG_KWH_A_R_ADD           PowerAddFlg[4].Bits.b1  // ZZ       aa
    
#define RFLAG_KVARH_A_C1_ADD        PowerAddFlg[4].Bits.b2  // ZZ       aa
#define RFLAG_KVARH_A_C1_SUB        PowerAddFlg[4].Bits.b3  // ZZ       aa
#define RFLAG_KVARH_A_C2_ADD        PowerAddFlg[4].Bits.b4  // ZZ       aa
#define RFLAG_KVARH_A_C2_SUB        PowerAddFlg[4].Bits.b5  // ZZ       aa

#define RFLAG_KVARH_A_Q1_ADD        PowerAddFlg[5].Bits.b0  // ZZ       aa
#define RFLAG_KVARH_A_Q2_ADD        PowerAddFlg[5].Bits.b1  // ZZ       aa
#define RFLAG_KVARH_A_Q3_ADD        PowerAddFlg[5].Bits.b2  // ZZ       aa
#define RFLAG_KVARH_A_Q4_ADD        PowerAddFlg[5].Bits.b3  // ZZ       aa

#define RFLAG_KVAH_A_F_ADD      PowerAddFlg[6].Bits.b0  // ZZ       aa
#define RFLAG_KVAH_A_R_ADD      PowerAddFlg[6].Bits.b1  // ZZ       aa
#define RFLAG_KWH_A_LOST_COPPER PowerAddFlg[6].Bits.b2  // ZZ       aa
#define RFLAG_KWH_A_LOST_IRON       PowerAddFlg[6].Bits.b3  // ZZ       aa


#define RFLAG_KWH_B_F_ADD           PowerAddFlg[7].Bits.b0  // ZZ       aa
#define RFLAG_KWH_B_R_ADD           PowerAddFlg[7].Bits.b1  // ZZ       aa
    
#define RFLAG_KVARH_B_C1_ADD        PowerAddFlg[7].Bits.b2  // ZZ       aa
#define RFLAG_KVARH_B_C1_SUB        PowerAddFlg[7].Bits.b3  // ZZ       aa
#define RFLAG_KVARH_B_C2_ADD        PowerAddFlg[7].Bits.b4  // ZZ       aa
#define RFLAG_KVARH_B_C2_SUB        PowerAddFlg[7].Bits.b5  // ZZ       aa

#define RFLAG_KVARH_B_Q1_ADD        PowerAddFlg[8].Bits.b0  // ZZ       aa
#define RFLAG_KVARH_B_Q2_ADD        PowerAddFlg[8].Bits.b1  // ZZ       aa
#define RFLAG_KVARH_B_Q3_ADD        PowerAddFlg[8].Bits.b2  // ZZ       aa
#define RFLAG_KVARH_B_Q4_ADD        PowerAddFlg[8].Bits.b3  // ZZ       aa

#define RFLAG_KVAH_B_F_ADD      PowerAddFlg[9].Bits.b0  // ZZ       aa
#define RFLAG_KVAH_B_R_ADD      PowerAddFlg[9].Bits.b1  // ZZ       aa
#define RFLAG_KWH_B_LOST_COPPER PowerAddFlg[9].Bits.b2  // ZZ       aa
#define RFLAG_KWH_B_LOST_IRON       PowerAddFlg[9].Bits.b3  // ZZ       aa



#define RFLAG_KWH_C_F_ADD           PowerAddFlg[10].Bits.b0     // ZZ       aa
#define RFLAG_KWH_C_R_ADD           PowerAddFlg[10].Bits.b1     // ZZ       aa
    
#define RFLAG_KVARH_C_C1_ADD        PowerAddFlg[10].Bits.b2     // ZZ       aa
#define RFLAG_KVARH_C_C1_SUB        PowerAddFlg[10].Bits.b3 // ZZ       aa
#define RFLAG_KVARH_C_C2_ADD        PowerAddFlg[10].Bits.b4     // ZZ       aa
#define RFLAG_KVARH_C_C2_SUB        PowerAddFlg[10].Bits.b5 // ZZ       aa

#define RFLAG_KVARH_C_Q1_ADD        PowerAddFlg[11].Bits.b0 // ZZ       aa
#define RFLAG_KVARH_C_Q2_ADD        PowerAddFlg[11].Bits.b1     // ZZ       aa
#define RFLAG_KVARH_C_Q3_ADD        PowerAddFlg[11].Bits.b2     // ZZ       aa
#define RFLAG_KVARH_C_Q4_ADD        PowerAddFlg[11].Bits.b3     // ZZ       aa

#define RFLAG_KVAH_C_F_ADD      PowerAddFlg[12].Bits.b0 // ZZ       aa
#define RFLAG_KVAH_C_R_ADD      PowerAddFlg[12].Bits.b1 // ZZ       aa
#define RFLAG_KWH_C_LOST_COPPER PowerAddFlg[12].Bits.b2 // ZZ       aa
#define RFLAG_KWH_C_LOST_IRON       PowerAddFlg[12].Bits.b3 // ZZ       aa

#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
#define RFLAG_KWH_F_P1_ADD      PowerAddFlg[13].Bits.b0     // ZZ 正向有功费率1 aa
#define RFLAG_KWH_F_P2_ADD      PowerAddFlg[13].Bits.b1     // ZZ 正向有功费率2 aa
#define RFLAG_KWH_F_P3_ADD      PowerAddFlg[13].Bits.b2     // ZZ 正向有功费率3 aa
#define RFLAG_KWH_F_P4_ADD      PowerAddFlg[13].Bits.b3     // ZZ 正向有功费率4 aa

#define RFLAG_KWH_R_P1_ADD      PowerAddFlg[14].Bits.b0     // ZZ 反向有功费率1 aa
#define RFLAG_KWH_R_P2_ADD      PowerAddFlg[14].Bits.b1     // ZZ 反向有功费率2 aa
#define RFLAG_KWH_R_P3_ADD      PowerAddFlg[14].Bits.b2     // ZZ 反向有功费率3 aa
#define RFLAG_KWH_R_P4_ADD      PowerAddFlg[14].Bits.b3     // ZZ 反向有功费率4 aa

#define RFLAG_KWH_C_P1_ADD      PowerAddFlg[15].Bits.b0     // ZZ 组合有功费率1增加 aa
#define RFLAG_KWH_C_P2_ADD      PowerAddFlg[15].Bits.b1     // ZZ 组合有功费率2增加 aa
#define RFLAG_KWH_C_P3_ADD      PowerAddFlg[15].Bits.b2     // ZZ 组合有功费率3增加 aa
#define RFLAG_KWH_C_P4_ADD      PowerAddFlg[15].Bits.b3     // ZZ 组合有功费率4增加 aa

#define RFLAG_KWH_C_P1_SUB      PowerAddFlg[15].Bits.b4     // ZZ 组合有功费率1减少 aa
#define RFLAG_KWH_C_P2_SUB      PowerAddFlg[15].Bits.b5     // ZZ 组合有功费率2减少 aa
#define RFLAG_KWH_C_P3_SUB      PowerAddFlg[15].Bits.b6     // ZZ 组合有功费率3减少 aa
#define RFLAG_KWH_C_P4_SUB      PowerAddFlg[15].Bits.b7     // ZZ 组合有功费率4减少 aa
#endif

#endif


#if 0
AP_POWERCOUNT_EXT uchar PowerAddFlg[PTADDFLG_KWH_ALL_START];
 

#define RFLAG_KWH_C_ADD     PowerAddFlg[PTADDFLG_KWH_C_ALL]     // ZZ 组合有功增加 aa
#define RFLAG_KWH_C_SUB     PowerAddFlg[0]  // ZZ 组合有功减少 aa

#define RFLAG_KWH_F_ADD     PowerAddFlg[PTADDFLG_KWH_F_ALL]     // ZZ 正向有功 aa
#define RFLAG_KWH_R_ADD     PowerAddFlg[PTADDFLG_KWH_R_ALL]     // ZZ 反向有功 aa

#define RFLAG_KVARH_C1_ADD  PowerAddFlg[PTADDFLG_KVARH_C1_ALL]  // ZZ  组合1无功增加     aa
#define RFLAG_KVARH_C1_SUB  PowerAddFlg[1]  // ZZ  组合1无功减少     aa
#define RFLAG_KVARH_C2_ADD  PowerAddFlg[PTADDFLG_KVARH_C2_ALL]  // ZZ  组合2无功增加     aa
#define RFLAG_KVARH_C2_SUB  PowerAddFlg[1]  // ZZ  组合2无功减少     aa

#define RFLAG_KVARH_Q1_ADD       PowerAddFlg[PTADDFLG_KVARH_Q1_ALL] // ZZ  1象限无功增加     aa
#define RFLAG_KVARH_Q2_ADD       PowerAddFlg[PTADDFLG_KVARH_Q2_ALL] // ZZ  2象限无功增加     aa
#define RFLAG_KVARH_Q3_ADD       PowerAddFlg[PTADDFLG_KVARH_Q3_ALL] // ZZ  3象限无功增加     aa
#define RFLAG_KVARH_Q4_ADD       PowerAddFlg[PTADDFLG_KVARH_Q4_ALL]     // ZZ  4象限无功增加     aa

#define RFLAG_KVAH_F_ADD        PowerAddFlg[PTADDFLG_KVAH_F_ALL]    // ZZ  正向视在     aa
#define RFLAG_KVAH_R_ADD        PowerAddFlg[PTADDFLG_KVAH_R_ALL]    // ZZ  反向视在     aa

#define RFLAG_KWH_LOST_COPPER       PowerAddFlg[PTADDFLG_KWH_LOST_COPPER_ALL]   // ZZ  铜损电量     aa
#define RFLAG_KWH_LOST_IRON     PowerAddFlg[PTADDFLG_KWH_LOST_IRON_ALL] // ZZ  铁损电量     aa


#define RFLAG_KWH_A_F_ADD           PowerAddFlg[PTADDFLG_KWH_A_F_ALL]   // ZZ       aa
#define RFLAG_KWH_A_R_ADD           PowerAddFlg[PTADDFLG_KWH_A_R_ALL]   // ZZ       aa
    
#define RFLAG_KVARH_A_C1_ADD        PowerAddFlg[PTADDFLG_KVARH_A_C1_ALL]    // ZZ       aa
#define RFLAG_KVARH_A_C1_SUB        PowerAddFlg[4]  // ZZ       aa
#define RFLAG_KVARH_A_C2_ADD        PowerAddFlg[PTADDFLG_KVARH_A_C2_ALL]    // ZZ       aa
#define RFLAG_KVARH_A_C2_SUB        PowerAddFlg[4]  // ZZ       aa

#define RFLAG_KVARH_A_Q1_ADD        PowerAddFlg[PTADDFLG_KVARH_A_Q1_ALL]    // ZZ       aa
#define RFLAG_KVARH_A_Q2_ADD        PowerAddFlg[PTADDFLG_KVARH_A_Q2_ALL]    // ZZ       aa
#define RFLAG_KVARH_A_Q3_ADD        PowerAddFlg[PTADDFLG_KVARH_A_Q3_ALL]    // ZZ       aa
#define RFLAG_KVARH_A_Q4_ADD        PowerAddFlg[PTADDFLG_KVARH_A_Q4_ALL]    // ZZ       aa

#define RFLAG_KVAH_A_F_ADD      PowerAddFlg[PTADDFLG_KVAH_A_F_ALL]  // ZZ       aa
#define RFLAG_KVAH_A_R_ADD      PowerAddFlg[PTADDFLG_KVAH_A_R_ALL]  // ZZ       aa
#define RFLAG_KWH_A_LOST_COPPER PowerAddFlg[PTADDFLG_KWH_A_LOST_COPPER_ALL] // ZZ       aa
#define RFLAG_KWH_A_LOST_IRON       PowerAddFlg[PTADDFLG_KWH_A_LOST_IRON_ALL]   // ZZ       aa


#define RFLAG_KWH_B_F_ADD           PowerAddFlg[PTADDFLG_KWH_B_F_ALL]   // ZZ       aa
#define RFLAG_KWH_B_R_ADD           PowerAddFlg[PTADDFLG_KWH_B_R_ALL]   // ZZ       aa
    
#define RFLAG_KVARH_B_C1_ADD        PowerAddFlg[PTADDFLG_KVARH_B_C1_ALL]    // ZZ       aa
#define RFLAG_KVARH_B_C1_SUB        PowerAddFlg[4]  // ZZ       aa
#define RFLAG_KVARH_B_C2_ADD        PowerAddFlg[PTADDFLG_KVARH_B_C2_ALL]    // ZZ       aa
#define RFLAG_KVARH_B_C2_SUB        PowerAddFlg[4]  // ZZ       aa

#define RFLAG_KVARH_B_Q1_ADD        PowerAddFlg[PTADDFLG_KVARH_B_Q1_ALL]    // ZZ       aa
#define RFLAG_KVARH_B_Q2_ADD        PowerAddFlg[PTADDFLG_KVARH_B_Q2_ALL]    // ZZ       aa
#define RFLAG_KVARH_B_Q3_ADD        PowerAddFlg[PTADDFLG_KVARH_B_Q3_ALL]    // ZZ       aa
#define RFLAG_KVARH_B_Q4_ADD        PowerAddFlg[PTADDFLG_KVARH_B_Q4_ALL]    // ZZ       aa

#define RFLAG_KVAH_B_F_ADD      PowerAddFlg[PTADDFLG_KVAH_B_F_ALL]  // ZZ       aa
#define RFLAG_KVAH_B_R_ADD      PowerAddFlg[PTADDFLG_KVAH_B_R_ALL]  // ZZ       aa
#define RFLAG_KWH_B_LOST_COPPER PowerAddFlg[PTADDFLG_KWH_B_LOST_COPPER_ALL] // ZZ       aa
#define RFLAG_KWH_B_LOST_IRON       PowerAddFlg[PTADDFLG_KWH_B_LOST_IRON_ALL]   // ZZ       aa


#define RFLAG_KWH_C_F_ADD           PowerAddFlg[PTADDFLG_KWH_C_F_ALL]   // ZZ       aa
#define RFLAG_KWH_C_R_ADD           PowerAddFlg[PTADDFLG_KWH_C_R_ALL]   // ZZ       aa
    
#define RFLAG_KVARH_C_C1_ADD        PowerAddFlg[PTADDFLG_KVARH_C_C1_ALL]    // ZZ       aa
#define RFLAG_KVARH_C_C1_SUB        PowerAddFlg[4]  // ZZ       aa
#define RFLAG_KVARH_C_C2_ADD        PowerAddFlg[PTADDFLG_KVARH_C_C2_ALL]    // ZZ       aa
#define RFLAG_KVARH_C_C2_SUB        PowerAddFlg[4]  // ZZ       aa

#define RFLAG_KVARH_C_Q1_ADD        PowerAddFlg[PTADDFLG_KVARH_C_Q1_ALL]    // ZZ       aa
#define RFLAG_KVARH_C_Q2_ADD        PowerAddFlg[PTADDFLG_KVARH_C_Q2_ALL]    // ZZ       aa
#define RFLAG_KVARH_C_Q3_ADD        PowerAddFlg[PTADDFLG_KVARH_C_Q3_ALL]    // ZZ       aa
#define RFLAG_KVARH_C_Q4_ADD        PowerAddFlg[PTADDFLG_KVARH_C_Q4_ALL]    // ZZ       aa

#define RFLAG_KVAH_C_F_ADD      PowerAddFlg[PTADDFLG_KVAH_C_F_ALL]  // ZZ       aa
#define RFLAG_KVAH_C_R_ADD      PowerAddFlg[PTADDFLG_KVAH_C_R_ALL]  // ZZ       aa
#define RFLAG_KWH_C_LOST_COPPER PowerAddFlg[PTADDFLG_KWH_C_LOST_COPPER_ALL] // ZZ       aa
#define RFLAG_KWH_C_LOST_IRON       PowerAddFlg[PTADDFLG_KWH_C_LOST_IRON_ALL]   // ZZ       aa


#endif










AP_POWERCOUNT_EXT uchar TestKwhBCD(uchar *ucPoint,uchar ucFlagSub);

AP_POWERCOUNT_EXT uchar Kwh3CopySafeCheck(uchar ucFlagSub);

//AP_POWERCOUNT_EXT void KwhErrEventRecord(void);

AP_POWERCOUNT_EXT void KwhRamAdd(ulong i);

AP_POWERCOUNT_EXT void KwhPointSub(uchar *ucDPoint);

AP_POWERCOUNT_EXT void KwhRamAddHaveSub(ulong ulRamAddr);

AP_POWERCOUNT_EXT void KwhRamSubHaveSub(ulong ulRamAddr);

AP_POWERCOUNT_EXT void KwhFmAddHaveSubWith5Byte(ulong ulFmAddr);

AP_POWERCOUNT_EXT void KwhFmSubHaveSubWith5Byte(ulong ulFmAddr);

AP_POWERCOUNT_EXT void KwhFmAddWith5Byte(ulong ulFmAddr);

AP_POWERCOUNT_EXT uchar KwhPowerOnSafeCheck(uchar ucKwhType,uchar ucFlagSub);

AP_POWERCOUNT_EXT uchar KwhPowerOnResume(uchar ucKwhType,uchar ucFlagSub);

AP_POWERCOUNT_EXT void KwhUsePowerOnResume(void);

AP_POWERCOUNT_EXT void KwhResume(void);


AP_POWERCOUNT_EXT uchar WritePower3Copy(uchar ucKwhType);
AP_POWERCOUNT_EXT uchar WritePower2rom(uchar ucKwhType);
AP_POWERCOUNT_EXT uchar WriteAlluse2rom(void);

AP_POWERCOUNT_EXT void KwhSubHaveSubDataFromType(uchar ucKwhType);

AP_POWERCOUNT_EXT void KwhAddHaveSubDataFromType(uchar ucKwhType);

AP_POWERCOUNT_EXT void KwhAddDataFromType(uchar ucKwhType);
 
AP_POWERCOUNT_EXT void KwhAddMode(void);

#if 0
AP_POWERCOUNT_EXT void EnergyPulseOutEnable(uchar ucEnableFlg);
AP_POWERCOUNT_EXT void PluseAddKvarhInt(void);
AP_POWERCOUNT_EXT void PluseAddKwhInt(void);
#endif

AP_POWERCOUNT_EXT void KwhAllDataClr(void);

AP_POWERCOUNT_EXT void KwhRamAdd10Data(ulong ulRamAddr,u16 uiData);

AP_POWERCOUNT_EXT void KwhAddIntDataFromType(uchar ucKwhType,u16 uiData);

//AP_POWERCOUNT_EXT uchar uKwhBCopyData[PT_KWH_TOTAL][6];
//AP_POWERCOUNT_EXT uchar uKwhCCopyData[PT_KWH_TOTAL][6];
AP_POWERCOUNT_EXT uchar uKwhACopyCheck[PT_KWH_TOTAL];


#define KWH_CHECK_ALL_OK    0
#define KWH_CHECK_A_ERR     3
#define KWH_CHECK_B_ERR     2
#define KWH_CHECK_C_ERR     1
#define KWH_CHECK_ALL_ERR   4

#define CON_KWH_ERR_EVENT_RECORD_START  0xAA
#define CON_KWH_ERR_EVENT_RECORD_END    0xDD

//AP_POWERCOUNT_EXT uchar ucKwhErrEventRecordMode;


AP_POWERCOUNT_EXT uchar KwhAddModeAddEnd;

#define KWH_WILL_SUB 1
#define KWH_WILL_NOSUB 0
#ifdef  AP_POWERCOUNT_GLOBALS

 const ST_KWH_RESUME_CANSUB_PARAM TB_KWH_RESUME_CAN_SUB[PT_KWH_TOTAL]=
{
    {PT_KWH_C_ALL,KWH_WILL_SUB},
    {PT_KWH_C_F1,KWH_WILL_SUB},
    {PT_KWH_C_F2,KWH_WILL_SUB},
    {PT_KWH_C_F3,KWH_WILL_SUB},
    {PT_KWH_C_F4,KWH_WILL_SUB},
	{PT_KWH_C_F5,KWH_WILL_SUB},
	{PT_KWH_C_F6,KWH_WILL_SUB},
	{PT_KWH_C_F7,KWH_WILL_SUB},
	{PT_KWH_C_F8,KWH_WILL_SUB},
	{PT_KWH_C_F9,KWH_WILL_SUB},
	{PT_KWH_C_F10,KWH_WILL_SUB},
	{PT_KWH_C_F11,KWH_WILL_SUB},
	{PT_KWH_C_F12,KWH_WILL_SUB},
	{PT_KWH_C_F13,KWH_WILL_SUB},
	{PT_KWH_C_F14,KWH_WILL_SUB},
    {PT_KWH_F_ALL,KWH_WILL_NOSUB},
    {PT_KWH_F_F1,KWH_WILL_NOSUB},
    {PT_KWH_F_F2,KWH_WILL_NOSUB},
    {PT_KWH_F_F3,KWH_WILL_NOSUB},
    {PT_KWH_F_F4,KWH_WILL_NOSUB},
	{PT_KWH_F_F5,KWH_WILL_NOSUB},
	{PT_KWH_F_F6,KWH_WILL_NOSUB},
	{PT_KWH_F_F7,KWH_WILL_NOSUB},
	{PT_KWH_F_F8,KWH_WILL_NOSUB},
	{PT_KWH_F_F9,KWH_WILL_NOSUB},
	{PT_KWH_F_F10,KWH_WILL_NOSUB},
	{PT_KWH_F_F11,KWH_WILL_NOSUB},
	{PT_KWH_F_F12,KWH_WILL_NOSUB},
	{PT_KWH_F_F13,KWH_WILL_NOSUB},
	{PT_KWH_F_F14,KWH_WILL_NOSUB},
    {PT_KWH_R_ALL,KWH_WILL_NOSUB},
    {PT_KWH_R_F1,KWH_WILL_NOSUB},
    {PT_KWH_R_F2,KWH_WILL_NOSUB},
    {PT_KWH_R_F3,KWH_WILL_NOSUB},
    {PT_KWH_R_F4,KWH_WILL_NOSUB},
	{PT_KWH_R_F5,KWH_WILL_NOSUB},
	{PT_KWH_R_F6,KWH_WILL_NOSUB},
	{PT_KWH_R_F7,KWH_WILL_NOSUB},
	{PT_KWH_R_F8,KWH_WILL_NOSUB},
	{PT_KWH_R_F9,KWH_WILL_NOSUB},
	{PT_KWH_R_F10,KWH_WILL_NOSUB},
	{PT_KWH_R_F11,KWH_WILL_NOSUB},
	{PT_KWH_R_F12,KWH_WILL_NOSUB},
	{PT_KWH_R_F13,KWH_WILL_NOSUB},
	{PT_KWH_R_F14,KWH_WILL_NOSUB},
    {PT_KVARH_C1_ALL,KWH_WILL_SUB},
    {PT_KVARH_C1_F1,KWH_WILL_SUB},
    {PT_KVARH_C1_F2,KWH_WILL_SUB},
    {PT_KVARH_C1_F3,KWH_WILL_SUB},
    {PT_KVARH_C1_F4,KWH_WILL_SUB},
	{PT_KVARH_C1_F5,KWH_WILL_SUB},
	{PT_KVARH_C1_F6,KWH_WILL_SUB},
	{PT_KVARH_C1_F7,KWH_WILL_SUB},
	{PT_KVARH_C1_F8,KWH_WILL_SUB},
	{PT_KVARH_C1_F9,KWH_WILL_SUB},
	{PT_KVARH_C1_F10,KWH_WILL_SUB},
	{PT_KVARH_C1_F11,KWH_WILL_SUB},
	{PT_KVARH_C1_F12,KWH_WILL_SUB},
	{PT_KVARH_C1_F13,KWH_WILL_SUB},
	{PT_KVARH_C1_F14,KWH_WILL_SUB},
    {PT_KVARH_C2_ALL,KWH_WILL_SUB},
    {PT_KVARH_C2_F1,KWH_WILL_SUB},
    {PT_KVARH_C2_F2,KWH_WILL_SUB},
    {PT_KVARH_C2_F3,KWH_WILL_SUB},
    {PT_KVARH_C2_F4,KWH_WILL_SUB},
	{PT_KVARH_C2_F5,KWH_WILL_SUB},
	{PT_KVARH_C2_F6,KWH_WILL_SUB},
	{PT_KVARH_C2_F7,KWH_WILL_SUB},
	{PT_KVARH_C2_F8,KWH_WILL_SUB},
	{PT_KVARH_C2_F9,KWH_WILL_SUB},
	{PT_KVARH_C2_F10,KWH_WILL_SUB},
	{PT_KVARH_C2_F11,KWH_WILL_SUB},
	{PT_KVARH_C2_F12,KWH_WILL_SUB},
	{PT_KVARH_C2_F13,KWH_WILL_SUB},
	{PT_KVARH_C2_F14,KWH_WILL_SUB},
    {PT_KVARH_Q1_ALL,KWH_WILL_NOSUB},
    {PT_KVARH_Q1_F1,KWH_WILL_NOSUB},
    {PT_KVARH_Q1_F2,KWH_WILL_NOSUB},
    {PT_KVARH_Q1_F3,KWH_WILL_NOSUB},
    {PT_KVARH_Q1_F4,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F5,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F6,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F7,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F8,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F9,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F10,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F11,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F12,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F13,KWH_WILL_NOSUB},
	{PT_KVARH_Q1_F14,KWH_WILL_NOSUB},
    {PT_KVARH_Q2_ALL,KWH_WILL_NOSUB},
    {PT_KVARH_Q2_F1,KWH_WILL_NOSUB},
    {PT_KVARH_Q2_F2,KWH_WILL_NOSUB},
    {PT_KVARH_Q2_F3,KWH_WILL_NOSUB},
    {PT_KVARH_Q2_F4,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F5,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F6,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F7,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F8,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F9,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F10,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F11,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F12,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F13,KWH_WILL_NOSUB},
	{PT_KVARH_Q2_F14,KWH_WILL_NOSUB},
    {PT_KVARH_Q3_ALL,KWH_WILL_NOSUB},
    {PT_KVARH_Q3_F1,KWH_WILL_NOSUB},
    {PT_KVARH_Q3_F2,KWH_WILL_NOSUB},
    {PT_KVARH_Q3_F3,KWH_WILL_NOSUB},
    {PT_KVARH_Q3_F4,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F5,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F6,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F7,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F8,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F9,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F10,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F11,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F12,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F13,KWH_WILL_NOSUB},
	{PT_KVARH_Q3_F14,KWH_WILL_NOSUB},
    {PT_KVARH_Q4_ALL,KWH_WILL_NOSUB},
    {PT_KVARH_Q4_F1,KWH_WILL_NOSUB},
    {PT_KVARH_Q4_F2,KWH_WILL_NOSUB},
    {PT_KVARH_Q4_F3,KWH_WILL_NOSUB},
    {PT_KVARH_Q4_F4,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F5,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F6,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F7,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F8,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F9,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F10,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F11,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F12,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F13,KWH_WILL_NOSUB},
	{PT_KVARH_Q4_F14,KWH_WILL_NOSUB},
	{PT_KVAH_F_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_F_F1,KWH_WILL_NOSUB},
	{PT_KVAH_F_F2,KWH_WILL_NOSUB},
	{PT_KVAH_F_F3,KWH_WILL_NOSUB},
	{PT_KVAH_F_F4,KWH_WILL_NOSUB},
	{PT_KVAH_F_F5,KWH_WILL_NOSUB},
	{PT_KVAH_F_F6,KWH_WILL_NOSUB},
	{PT_KVAH_F_F7,KWH_WILL_NOSUB},
	{PT_KVAH_F_F8,KWH_WILL_NOSUB},
	{PT_KVAH_F_F9,KWH_WILL_NOSUB},
	{PT_KVAH_F_F10,KWH_WILL_NOSUB},
	{PT_KVAH_F_F11,KWH_WILL_NOSUB},
	{PT_KVAH_F_F12,KWH_WILL_NOSUB},
	{PT_KVAH_F_F13,KWH_WILL_NOSUB},
	{PT_KVAH_F_F14,KWH_WILL_NOSUB},
	{PT_KVAH_R_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_R_F1,KWH_WILL_NOSUB},
	{PT_KVAH_R_F2,KWH_WILL_NOSUB},
	{PT_KVAH_R_F3,KWH_WILL_NOSUB},
	{PT_KVAH_R_F4,KWH_WILL_NOSUB},
	{PT_KVAH_R_F5,KWH_WILL_NOSUB},
	{PT_KVAH_R_F6,KWH_WILL_NOSUB},
	{PT_KVAH_R_F7,KWH_WILL_NOSUB},
	{PT_KVAH_R_F8,KWH_WILL_NOSUB},
	{PT_KVAH_R_F9,KWH_WILL_NOSUB},
	{PT_KVAH_R_F10,KWH_WILL_NOSUB},
	{PT_KVAH_R_F11,KWH_WILL_NOSUB},
	{PT_KVAH_R_F12,KWH_WILL_NOSUB},
	{PT_KVAH_R_F13,KWH_WILL_NOSUB},
	{PT_KVAH_R_F14,KWH_WILL_NOSUB},
	{PT_KWH_LOST_COPPER_ALL,KWH_WILL_NOSUB},
	{PT_KWH_LOST_IRON_ALL,KWH_WILL_NOSUB},
    {PT_KWH_A_F_ALL,KWH_WILL_NOSUB},
    {PT_KWH_A_R_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_A_C1_ALL,KWH_WILL_SUB},
	{PT_KVARH_A_C2_ALL,KWH_WILL_SUB},
	{PT_KVARH_A_Q1_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_A_Q2_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_A_Q3_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_A_Q4_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_A_F_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_A_R_ALL,KWH_WILL_NOSUB},
	{PT_KWH_A_LOST_COPPER_ALL,KWH_WILL_NOSUB},
	{PT_KWH_A_LOST_IRON_ALL,KWH_WILL_NOSUB},
    {PT_KWH_B_F_ALL,KWH_WILL_NOSUB},
    {PT_KWH_B_R_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_B_C1_ALL,KWH_WILL_SUB},
	{PT_KVARH_B_C2_ALL,KWH_WILL_SUB},
	{PT_KVARH_B_Q1_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_B_Q2_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_B_Q3_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_B_Q4_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_B_F_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_B_R_ALL,KWH_WILL_NOSUB},
	{PT_KWH_B_LOST_COPPER_ALL,KWH_WILL_NOSUB},
	{PT_KWH_B_LOST_IRON_ALL,KWH_WILL_NOSUB},
    {PT_KWH_C_F_ALL,KWH_WILL_NOSUB},
    {PT_KWH_C_R_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_C_C1_ALL,KWH_WILL_SUB},
	{PT_KVARH_C_C2_ALL,KWH_WILL_SUB},
	{PT_KVARH_C_Q1_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_C_Q2_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_C_Q3_ALL,KWH_WILL_NOSUB},
	{PT_KVARH_C_Q4_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_C_F_ALL,KWH_WILL_NOSUB},
	{PT_KVAH_C_R_ALL,KWH_WILL_NOSUB},
	{PT_KWH_C_LOST_COPPER_ALL,KWH_WILL_NOSUB},
	{PT_KWH_C_LOST_IRON_ALL,KWH_WILL_NOSUB}

};
#else
 extern const ST_KWH_RESUME_CANSUB_PARAM TB_KWH_RESUME_CAN_SUB[];
#endif


















#endif



































