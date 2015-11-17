#define EPL_KWH_ALL_START 0x05000000 // 0 byte   ��ǰ����������ʼ
#define EPL_KWH_ALL_DATA 0x05000000 // 1015 byte   ��ǰ�����������ݣ�����������RAM
#define EPL_KWH_ALL_END 0x050003F7 // 0 byte   ��ǰ�������ݽ���
// #define  0x050003F7 // 5 byte   �������ݱ���,�����������������ܻ���
#define EPL_DEMAND_DATA_START 0x050003FC // 0 byte   ����������ʼ
#define EPL_DEMAND_ALL_DATA 0x050003FC // 1620 byte   �������ݣ�����������RAM
#define EPL_DEMAND_DATA_END 0x05000A50 //  byte   �������ݽ���
// #define  0x05000A50 // 24 byte   �������ݱ���
#define EPL_KWH_ALL_USE_START 0x05000A68 // 0 byte   ��ǰ�������õ�����ʼ
#define EPL_KWH_C_USE_ALL 0x05000A68 // 5 byte XXXXXX.XXXX BCD ��ǰ����������й����õ���
#define EPL_KWH_C_USE_F1 0x05000A6D // 5 byte XXXXXX.XXXX BCD ��ǰ����������й����õ���
#define EPL_KWH_C_USE_F2 0x05000A72 // 5 byte XXXXXX.XXXX BCD ��ǰ����������й����õ���
#define EPL_KWH_C_USE_F3 0x05000A77 // 5 byte XXXXXX.XXXX BCD ��ǰ����������й�ƽ�õ���
#define EPL_KWH_C_USE_F4 0x05000A7C // 5 byte XXXXXX.XXXX BCD ��ǰ����������й����õ���
#define EPL_KWH_F_AND_R_START 0x05000A81 // 0 byte   ��ǰ�й�(��+��)�ۼƵ�����ʼ
#define EPL_KWH_F_AND_R_ALL 0x05000A81 // 5 byte XXXXXX.XXXX BCD ��ǰ�й�(��+��)�ۼ��ܵ���
#define EPL_KWH_F_AND_R_F1 0x05000A86 // 5 byte XXXXXX.XXXX BCD ��ǰ�й�(��+��)�ۼƼ����
#define EPL_KWH_F_AND_R_F2 0x05000A8B // 5 byte XXXXXX.XXXX BCD ��ǰ�й�(��+��)�ۼƷ����
#define EPL_KWH_F_AND_R_F3 0x05000A90 // 5 byte XXXXXX.XXXX BCD ��ǰ�й�(��+��)�ۼ�ƽ����
#define EPL_KWH_F_AND_R_F4 0x05000A95 // 5 byte XXXXXX.XXXX BCD ��ǰ�й�(��+��)�ۼƹȵ���
// #define  0x05000A9A // 14 byte   ��������
#define EPL_COEF_DATA_START 0x05000AA8 // 0 byte   ����������ʼ
#define EPL_COEF_DAYTABLE_START 0x05000AA8 // 0 byte   ʱ��������ʼ
#define EPL_SEASON1_DAYTABLE_CHANGE01 0x05000AA8 // 3 byte MMDDNN BCD ��һ�׵�1ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE02 0x05000AAB // 3 byte MMDDNN BCD ��һ�׵�2ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE03 0x05000AAE // 3 byte MMDDNN BCD ��һ�׵�3ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE04 0x05000AB1 // 3 byte MMDDNN BCD ��һ�׵�4ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE05 0x05000AB4 // 3 byte MMDDNN BCD ��һ�׵�5ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE06 0x05000AB7 // 3 byte MMDDNN BCD ��һ�׵�6ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE07 0x05000ABA // 3 byte MMDDNN BCD ��һ�׵�7ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE08 0x05000ABD // 3 byte MMDDNN BCD ��һ�׵�8ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE09 0x05000AC0 // 3 byte MMDDNN BCD ��һ�׵�9ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE10 0x05000AC3 // 3 byte MMDDNN BCD ��һ�׵�10ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE11 0x05000AC6 // 3 byte MMDDNN BCD ��һ�׵�11ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE12 0x05000AC9 // 3 byte MMDDNN BCD ��һ�׵�12ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE13 0x05000ACC // 3 byte MMDDNN BCD ��һ�׵�13ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE_CHANGE14 0x05000ACF // 3 byte MMDDNN BCD ��һ�׵�14ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON1_DAYTABLE1_PERIOD01 0x05000AD2 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD02 0x05000AD5 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD03 0x05000AD8 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD04 0x05000ADB // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD05 0x05000ADE // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD06 0x05000AE1 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD07 0x05000AE4 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD08 0x05000AE7 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD09 0x05000AEA // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD10 0x05000AED // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD11 0x05000AF0 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD12 0x05000AF3 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD13 0x05000AF6 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE1_PERIOD14 0x05000AF9 // 3 byte hhmmNN BCD ��һ�׵�1��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD01 0x05000AFC // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD02 0x05000AFF // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD03 0x05000B02 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD04 0x05000B05 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD05 0x05000B08 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD06 0x05000B0B // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD07 0x05000B0E // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD08 0x05000B11 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD09 0x05000B14 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD10 0x05000B17 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD11 0x05000B1A // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD12 0x05000B1D // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD13 0x05000B20 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE2_PERIOD14 0x05000B23 // 3 byte hhmmNN BCD ��һ�׵�2��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD01 0x05000B26 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD02 0x05000B29 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD03 0x05000B2C // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD04 0x05000B2F // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD05 0x05000B32 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD06 0x05000B35 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD07 0x05000B38 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD08 0x05000B3B // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD09 0x05000B3E // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD10 0x05000B41 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD11 0x05000B44 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD12 0x05000B47 // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD13 0x05000B4A // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE3_PERIOD14 0x05000B4D // 3 byte hhmmNN BCD ��һ�׵�3��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD01 0x05000B50 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD02 0x05000B53 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD03 0x05000B56 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD04 0x05000B59 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD05 0x05000B5C // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD06 0x05000B5F // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD07 0x05000B62 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD08 0x05000B65 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD09 0x05000B68 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD10 0x05000B6B // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD11 0x05000B6E // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD12 0x05000B71 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD13 0x05000B74 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE4_PERIOD14 0x05000B77 // 3 byte hhmmNN BCD ��һ�׵�4��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD01 0x05000B7A // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD02 0x05000B7D // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD03 0x05000B80 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD04 0x05000B83 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD05 0x05000B86 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD06 0x05000B89 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD07 0x05000B8C // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD08 0x05000B8F // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD09 0x05000B92 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD10 0x05000B95 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD11 0x05000B98 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD12 0x05000B9B // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD13 0x05000B9E // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE5_PERIOD14 0x05000BA1 // 3 byte hhmmNN BCD ��һ�׵�5��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD01 0x05000BA4 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD02 0x05000BA7 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD03 0x05000BAA // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD04 0x05000BAD // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD05 0x05000BB0 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD06 0x05000BB3 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD07 0x05000BB6 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD08 0x05000BB9 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD09 0x05000BBC // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD10 0x05000BBF // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD11 0x05000BC2 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD12 0x05000BC5 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD13 0x05000BC8 // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE6_PERIOD14 0x05000BCB // 3 byte hhmmNN BCD ��һ�׵�6��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD01 0x05000BCE // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD02 0x05000BD1 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD03 0x05000BD4 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD04 0x05000BD7 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD05 0x05000BDA // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD06 0x05000BDD // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD07 0x05000BE0 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD08 0x05000BE3 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD09 0x05000BE6 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD10 0x05000BE9 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD11 0x05000BEC // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD12 0x05000BEF // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD13 0x05000BF2 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE7_PERIOD14 0x05000BF5 // 3 byte hhmmNN BCD ��һ�׵�7��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD01 0x05000BF8 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD02 0x05000BFB // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD03 0x05000BFE // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD04 0x05000C01 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD05 0x05000C04 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD06 0x05000C07 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD07 0x05000C0A // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD08 0x05000C0D // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD09 0x05000C10 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD10 0x05000C13 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD11 0x05000C16 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD12 0x05000C19 // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD13 0x05000C1C // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON1_DAYTABLE8_PERIOD14 0x05000C1F // 3 byte hhmmNN BCD ��һ�׵�8��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE_CHANGE01 0x05000C22 // 3 byte MMDDNN BCD �ڶ��׵�1ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE02 0x05000C25 // 3 byte MMDDNN BCD �ڶ��׵�2ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE03 0x05000C28 // 3 byte MMDDNN BCD �ڶ��׵�3ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE04 0x05000C2B // 3 byte MMDDNN BCD �ڶ��׵�4ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE05 0x05000C2E // 3 byte MMDDNN BCD �ڶ��׵�5ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE06 0x05000C31 // 3 byte MMDDNN BCD �ڶ��׵�6ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE07 0x05000C34 // 3 byte MMDDNN BCD �ڶ��׵�7ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE08 0x05000C37 // 3 byte MMDDNN BCD �ڶ��׵�8ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE09 0x05000C3A // 3 byte MMDDNN BCD �ڶ��׵�9ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE10 0x05000C3D // 3 byte MMDDNN BCD �ڶ��׵�10ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE11 0x05000C40 // 3 byte MMDDNN BCD �ڶ��׵�11ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE12 0x05000C43 // 3 byte MMDDNN BCD �ڶ��׵�12ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE13 0x05000C46 // 3 byte MMDDNN BCD �ڶ��׵�13ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE_CHANGE14 0x05000C49 // 3 byte MMDDNN BCD �ڶ��׵�14ʱ����ʼ���ڼ���ʱ�α��
#define EPL_SEASON2_DAYTABLE1_PERIOD01 0x05000C4C // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD02 0x05000C4F // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD03 0x05000C52 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD04 0x05000C55 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD05 0x05000C58 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD06 0x05000C5B // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD07 0x05000C5E // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD08 0x05000C61 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD09 0x05000C64 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD10 0x05000C67 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD11 0x05000C6A // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD12 0x05000C6D // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD13 0x05000C70 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE1_PERIOD14 0x05000C73 // 3 byte hhmmNN BCD �ڶ��׵�1��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD01 0x05000C76 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD02 0x05000C79 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD03 0x05000C7C // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD04 0x05000C7F // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD05 0x05000C82 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD06 0x05000C85 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD07 0x05000C88 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD08 0x05000C8B // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD09 0x05000C8E // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD10 0x05000C91 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD11 0x05000C94 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD12 0x05000C97 // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD13 0x05000C9A // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE2_PERIOD14 0x05000C9D // 3 byte hhmmNN BCD �ڶ��׵�2��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD01 0x05000CA0 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD02 0x05000CA3 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD03 0x05000CA6 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD04 0x05000CA9 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD05 0x05000CAC // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD06 0x05000CAF // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD07 0x05000CB2 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD08 0x05000CB5 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD09 0x05000CB8 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD10 0x05000CBB // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD11 0x05000CBE // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD12 0x05000CC1 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD13 0x05000CC4 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE3_PERIOD14 0x05000CC7 // 3 byte hhmmNN BCD �ڶ��׵�3��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD01 0x05000CCA // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD02 0x05000CCD // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD03 0x05000CD0 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD04 0x05000CD3 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD05 0x05000CD6 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD06 0x05000CD9 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD07 0x05000CDC // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD08 0x05000CDF // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD09 0x05000CE2 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD10 0x05000CE5 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD11 0x05000CE8 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD12 0x05000CEB // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD13 0x05000CEE // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE4_PERIOD14 0x05000CF1 // 3 byte hhmmNN BCD �ڶ��׵�4��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD01 0x05000CF4 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD02 0x05000CF7 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD03 0x05000CFA // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD04 0x05000CFD // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD05 0x05000D00 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD06 0x05000D03 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD07 0x05000D06 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD08 0x05000D09 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD09 0x05000D0C // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD10 0x05000D0F // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD11 0x05000D12 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD12 0x05000D15 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD13 0x05000D18 // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE5_PERIOD14 0x05000D1B // 3 byte hhmmNN BCD �ڶ��׵�5��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD01 0x05000D1E // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD02 0x05000D21 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD03 0x05000D24 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD04 0x05000D27 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD05 0x05000D2A // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD06 0x05000D2D // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD07 0x05000D30 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD08 0x05000D33 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD09 0x05000D36 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD10 0x05000D39 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD11 0x05000D3C // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD12 0x05000D3F // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD13 0x05000D42 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE6_PERIOD14 0x05000D45 // 3 byte hhmmNN BCD �ڶ��׵�6��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD01 0x05000D48 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD02 0x05000D4B // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD03 0x05000D4E // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD04 0x05000D51 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD05 0x05000D54 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD06 0x05000D57 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD07 0x05000D5A // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD08 0x05000D5D // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD09 0x05000D60 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD10 0x05000D63 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD11 0x05000D66 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD12 0x05000D69 // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD13 0x05000D6C // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE7_PERIOD14 0x05000D6F // 3 byte hhmmNN BCD �ڶ��׵�7��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD01 0x05000D72 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��1ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD02 0x05000D75 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��2ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD03 0x05000D78 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��3ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD04 0x05000D7B // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��4ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD05 0x05000D7E // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��5ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD06 0x05000D81 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��6ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD07 0x05000D84 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��7ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD08 0x05000D87 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��8ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD09 0x05000D8A // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��9ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD10 0x05000D8D // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��10ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD11 0x05000D90 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��11ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD12 0x05000D93 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��12ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD13 0x05000D96 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��13ʱ����ʼʱ�估���ʺ�
#define EPL_SEASON2_DAYTABLE8_PERIOD14 0x05000D99 // 3 byte hhmmNN BCD �ڶ��׵�8��ʱ�α��14ʱ����ʼʱ�估���ʺ�
#define EPL_PERIODPRICE01_PRICE01 0x05000D9C // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��1
#define EPL_PERIODPRICE01_PRICE02 0x05000DA0 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��2
#define EPL_PERIODPRICE01_PRICE03 0x05000DA4 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��3
#define EPL_PERIODPRICE01_PRICE04 0x05000DA8 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��4
#define EPL_PERIODPRICE01_PRICE05 0x05000DAC // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��5
#define EPL_PERIODPRICE01_PRICE06 0x05000DB0 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��6
#define EPL_PERIODPRICE01_PRICE07 0x05000DB4 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��7
#define EPL_PERIODPRICE01_PRICE08 0x05000DB8 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��8
#define EPL_PERIODPRICE01_PRICE09 0x05000DBC // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��9
#define EPL_PERIODPRICE01_PRICE10 0x05000DC0 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��10
#define EPL_PERIODPRICE01_PRICE11 0x05000DC4 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��11
#define EPL_PERIODPRICE01_PRICE12 0x05000DC8 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��12
#define EPL_PERIODPRICE01_PRICE13 0x05000DCC // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��13
#define EPL_PERIODPRICE01_PRICE14 0x05000DD0 // 4 byte NNNN.NNNN BCD ��һ�׷��ʵ��14
#define EPL_PERIODPRICE02_PRICE01 0x05000DD4 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��1
#define EPL_PERIODPRICE02_PRICE02 0x05000DD8 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��2
#define EPL_PERIODPRICE02_PRICE03 0x05000DDC // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��3
#define EPL_PERIODPRICE02_PRICE04 0x05000DE0 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��4
#define EPL_PERIODPRICE02_PRICE05 0x05000DE4 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��5
#define EPL_PERIODPRICE02_PRICE06 0x05000DE8 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��6
#define EPL_PERIODPRICE02_PRICE07 0x05000DEC // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��7
#define EPL_PERIODPRICE02_PRICE08 0x05000DF0 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��8
#define EPL_PERIODPRICE02_PRICE09 0x05000DF4 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��9
#define EPL_PERIODPRICE02_PRICE10 0x05000DF8 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��10
#define EPL_PERIODPRICE02_PRICE11 0x05000DFC // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��11
#define EPL_PERIODPRICE02_PRICE12 0x05000E00 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��12
#define EPL_PERIODPRICE02_PRICE13 0x05000E04 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��13
#define EPL_PERIODPRICE02_PRICE14 0x05000E08 // 4 byte NNNN.NNNN BCD �ڶ��׷��ʵ��14
#define EPL_STEP01_DATA01 0x05000E0C // 4 byte NNNNNN.NN BCD ��һ�׵�01����ֵ
#define EPL_STEP01_DATA02 0x05000E10 // 4 byte NNNNNN.NN BCD ��һ�׵�02����ֵ
#define EPL_STEP01_DATA03 0x05000E14 // 4 byte NNNNNN.NN BCD ��һ�׵�03����ֵ
#define EPL_STEP01_DATA04 0x05000E18 // 4 byte NNNNNN.NN BCD ��һ�׵�04����ֵ
#define EPL_STEP01_DATA05 0x05000E1C // 4 byte NNNNNN.NN BCD ��һ�׵�05����ֵ
#define EPL_STEP01_DATA06 0x05000E20 // 4 byte NNNNNN.NN BCD ��һ�׵�06����ֵ
#define EPL_STEP01_DATA07 0x05000E24 // 4 byte NNNNNN.NN BCD ��һ�׵�07����ֵ
#define EPL_STEP01_DATA08 0x05000E28 // 4 byte NNNNNN.NN BCD ��һ�׵�08����ֵ
#define EPL_STEP01_DATA09 0x05000E2C // 4 byte NNNNNN.NN BCD ��һ�׵�09����ֵ
#define EPL_STEP01_DATA10 0x05000E30 // 4 byte NNNNNN.NN BCD ��һ�׵�10����ֵ
#define EPL_STEP01_DATA11 0x05000E34 // 4 byte NNNNNN.NN BCD ��һ�׵�11����ֵ
#define EPL_STEP01_DATA12 0x05000E38 // 4 byte NNNNNN.NN BCD ��һ�׵�12����ֵ
#define EPL_STEP01_DATA13 0x05000E3C // 4 byte NNNNNN.NN BCD ��һ�׵�13����ֵ
#define EPL_STEP01_DATA14 0x05000E40 // 4 byte NNNNNN.NN BCD ��һ�׵�14����ֵ
#define EPL_STEPPRICE01_PRICE01 0x05000E44 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��01
#define EPL_STEPPRICE01_PRICE02 0x05000E48 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��02
#define EPL_STEPPRICE01_PRICE03 0x05000E4C // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��03
#define EPL_STEPPRICE01_PRICE04 0x05000E50 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��04
#define EPL_STEPPRICE01_PRICE05 0x05000E54 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��05
#define EPL_STEPPRICE01_PRICE06 0x05000E58 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��06
#define EPL_STEPPRICE01_PRICE07 0x05000E5C // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��07
#define EPL_STEPPRICE01_PRICE08 0x05000E60 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��08
#define EPL_STEPPRICE01_PRICE09 0x05000E64 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��09
#define EPL_STEPPRICE01_PRICE10 0x05000E68 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��10
#define EPL_STEPPRICE01_PRICE11 0x05000E6C // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��11
#define EPL_STEPPRICE01_PRICE12 0x05000E70 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��12
#define EPL_STEPPRICE01_PRICE13 0x05000E74 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��13
#define EPL_STEPPRICE01_PRICE14 0x05000E78 // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��14
#define EPL_STEPPRICE01_PRICE15 0x05000E7C // 4 byte NNNN.NNNN BCD ��һ�׽��ݵ��15
#define EPL_STEP02_DATA01 0x05000E80 // 4 byte NNNNNN.NN BCD �ڶ��׵�01����ֵ
#define EPL_STEP02_DATA02 0x05000E84 // 4 byte NNNNNN.NN BCD �ڶ��׵�02����ֵ
#define EPL_STEP02_DATA03 0x05000E88 // 4 byte NNNNNN.NN BCD �ڶ��׵�03����ֵ
#define EPL_STEP02_DATA04 0x05000E8C // 4 byte NNNNNN.NN BCD �ڶ��׵�04����ֵ
#define EPL_STEP02_DATA05 0x05000E90 // 4 byte NNNNNN.NN BCD �ڶ��׵�05����ֵ
#define EPL_STEP02_DATA06 0x05000E94 // 4 byte NNNNNN.NN BCD �ڶ��׵�06����ֵ
#define EPL_STEP02_DATA07 0x05000E98 // 4 byte NNNNNN.NN BCD �ڶ��׵�07����ֵ
#define EPL_STEP02_DATA08 0x05000E9C // 4 byte NNNNNN.NN BCD �ڶ��׵�08����ֵ
#define EPL_STEP02_DATA09 0x05000EA0 // 4 byte NNNNNN.NN BCD �ڶ��׵�09����ֵ
#define EPL_STEP02_DATA10 0x05000EA4 // 4 byte NNNNNN.NN BCD �ڶ��׵�10����ֵ
#define EPL_STEP02_DATA11 0x05000EA8 // 4 byte NNNNNN.NN BCD �ڶ��׵�11����ֵ
#define EPL_STEP02_DATA12 0x05000EAC // 4 byte NNNNNN.NN BCD �ڶ��׵�12����ֵ
#define EPL_STEP02_DATA13 0x05000EB0 // 4 byte NNNNNN.NN BCD �ڶ��׵�13����ֵ
#define EPL_STEP02_DATA14 0x05000EB4 // 4 byte NNNNNN.NN BCD �ڶ��׵�14����ֵ
#define EPL_STEPPRICE02_PRICE01 0x05000EB8 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��01
#define EPL_STEPPRICE02_PRICE02 0x05000EBC // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��02
#define EPL_STEPPRICE02_PRICE03 0x05000EC0 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��03
#define EPL_STEPPRICE02_PRICE04 0x05000EC4 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��04
#define EPL_STEPPRICE02_PRICE05 0x05000EC8 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��05
#define EPL_STEPPRICE02_PRICE06 0x05000ECC // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��06
#define EPL_STEPPRICE02_PRICE07 0x05000ED0 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��07
#define EPL_STEPPRICE02_PRICE08 0x05000ED4 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��08
#define EPL_STEPPRICE02_PRICE09 0x05000ED8 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��09
#define EPL_STEPPRICE02_PRICE10 0x05000EDC // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��10
#define EPL_STEPPRICE02_PRICE11 0x05000EE0 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��11
#define EPL_STEPPRICE02_PRICE12 0x05000EE4 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��12
#define EPL_STEPPRICE02_PRICE13 0x05000EE8 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��13
#define EPL_STEPPRICE02_PRICE14 0x05000EEC // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��14
#define EPL_STEPPRICE02_PRICE15 0x05000EF0 // 4 byte NNNN.NNNN BCD �ڶ��׽��ݵ��15
// #define  0x05000EF4 // 4 byte   ����
#define EPL_USER_NUMBER 0x05000EF8 // 6 byte   �û���
#define EPL_USER_COMM_ADDR 0x05000EFE // 6 byte   �û���ַ(ͨѶ��ַ)
#define EPL_USER_ID 0x05000F04 // 6 byte   �û��ֺ�(���)
#define EPL_USER_ASSET 0x05000F0A // 32 byte   �ʲ�������(ASCII��)
#define EPL_USER_CLIENT 0x05000F2A // 6 byte NNNNNNNNNNNN  �ͻ����
#define EPL_CHARACTER_METER_RUN 0x05000F30 // 1 byte   �������������
#define EPL_CHARACTER_ACTIVE 0x05000F31 // 1 byte   �й���Ϸ�ʽ������
#define EPL_CHARACTER_REACTIVE01 0x05000F32 // 1 byte   �޹���Ϸ�ʽ1������
#define EPL_CHARACTER_REACTIVE02 0x05000F33 // 1 byte   �޹���Ϸ�ʽ2������
#define EPL_IR_MODULATOR_BAUDRATE 0x05000F34 // 1 byte   �����ͺ�����ͨ������������
#define EPL_IR_CONTACT_BAUDRATE 0x05000F35 // 1 byte   �Ӵ�ʽ������ͨ������������
#define EPL_COMM485_01_BAUDRATE 0x05000F36 // 1 byte   ͨѶ��1ͨ������������
#define EPL_COMM485_02_BAUDRATE 0x05000F37 // 1 byte   ͨѶ��2ͨ������������
#define EPL_COMM485_03_BAUDRATE 0x05000F38 // 1 byte   ͨѶ��3ͨ������������
#define EPL_CHARACTER_REST_DAY 0x05000F39 // 1 byte   ������������
#define EPL_CHARACTER_REST_DAYNO 0x05000F3A // 1 byte   �����ղ��õ���ʱ�α��
#define EPL_CHARACTER_CHARGE_MODE 0x05000F3B // 1 byte   ���ɼ�¼ģʽ��
#define EPL_CHARACTER_FREEZE_EVERYTIME_MODE 0x05000F3C // 1 byte   ��ʱ��������ģʽ��
#define EPL_CHARACTER_FREEZE_INSTANT_MODE 0x05000F3D // 1 byte   ˲ʱ��������ģʽ��
#define EPL_CHARACTER_FREEZE_RESTORE_MODE 0x05000F3E // 1 byte   Լ����������ģʽ��
#define EPL_CHARACTER_FREEZE_EVERYHOUR_MODE 0x05000F3F // 1 byte   ���㶳������ģʽ��
#define EPL_CHARACTER_FREEZE_EVERYDAY_MODE 0x05000F40 // 1 byte   �ն�������ģʽ��
#define EPL_CHARACTER_FREEZE_EVERYHOUR_STARTTIME 0x05000F41 // 5 byte YYMMDDhhmm BCD ���㶳����ʼʱ��
#define EPL_CHARACTER_FREEZE_EVERYHOUR_INTERVAL 0x05000F46 // 1 byte NN BCD ���㶳��ʱ����
#define EPL_CHARACTER_FREEZE_EVERYDAY_TIME 0x05000F47 // 2 byte hhmm BCD �ն���ʱ��
#define EPL_CHARGE_RECORD_START_TIME 0x05000F49 // 4 byte MMDDHHMM BCD ���ɼ�¼��ʼʱ��
#define EPL_CHARGE_RECORD_1_TIME 0x05000F4D // 2 byte MM BCD ��1�ฺ�ɼ�¼���ʱ��
#define EPL_CHARGE_RECORD_2_TIME 0x05000F4F // 2 byte MM BCD ��2�ฺ�ɼ�¼���ʱ��
#define EPL_CHARGE_RECORD_3_TIME 0x05000F51 // 2 byte MM BCD ��3�ฺ�ɼ�¼���ʱ��
#define EPL_CHARGE_RECORD_4_TIME 0x05000F53 // 2 byte MM BCD ��4�ฺ�ɼ�¼���ʱ��
#define EPL_CHARGE_RECORD_5_TIME 0x05000F55 // 2 byte MM BCD ��5�ฺ�ɼ�¼���ʱ��
#define EPL_CHARGE_RECORD_6_TIME 0x05000F57 // 2 byte MM BCD ��6�ฺ�ɼ�¼���ʱ��
#define EPL_BALANCE_DAY_NUM 0x05000F59 // 1 byte NN BCD ÿ�½���������
#define EPL_BALANCE_DAY_01 0x05000F5A // 2 byte DDHH BCD ÿ�µ�1������(9999����δ���ô˽�����)
#define EPL_BALANCE_DAY_02 0x05000F5C // 2 byte DDHH BCD ÿ�µ�2������(9999����δ���ô˽�����)
#define EPL_BALANCE_DAY_03 0x05000F5E // 2 byte DDHH BCD ÿ�µ�3������(9999����δ���ô˽�����)
#define EPL_COEF_MAX_KWH_F 0x05000F60 // 3 byte XX.XXXX BCD �����й���������ֵ
#define EPL_COEF_MAX_KWH_R 0x05000F63 // 3 byte XX.XXXX BCD �����й���������ֵ
#define EPL_COEF_VOLTAGE_LIMIT_UPPER 0x05000F66 // 2 byte XXX.X BCD ��ѹ����ֵ

#define EPL_COEF_VOLTAGE_LIMIT_LOWER 0x05000F68 // 2 byte XXX.X BCD ��ѹ����ֵ
#define EPL_COEF_FREEZE_TIME 0x05000F6A // 4 byte mmhhDDMM BCD ԤԼ����ʱ��
#define EPL_COEF_LOSS_VOLTAGE_CONDITION 0x05000F6E // 0 byte   ʧѹ�ж�����
#define EPL_COEF_LOSS_VOLTAGE_V_START 0x05000F6E // 2 byte NNN.N BCD ʧѹ�¼���ѹ��������
#define EPL_COEF_LOSS_VOLTAGE_V_END 0x05000F70 // 2 byte NNN.N BCD ʧѹ�¼���ѹ�ָ�����
#define EPL_COEF_LOSS_VOLTAGE_I_START 0x05000F72 // 3 byte NN.NNNN BCD ʧѹ�¼�������������
#define EPL_COEF_LOSS_VOLTAGE_TIME 0x05000F75 // 1 byte NN BCD ʧѹ�¼��ж���ʱʱ��
#define EPL_COEF_DOWN_VOLTAGE_CONDITION 0x05000F76 // 0 byte   Ƿѹ�ж�����
#define EPL_COEF_DOWN_VOLTAGE_V_START 0x05000F76 // 2 byte NNN.N BCD Ƿѹ�¼���ѹ��������
#define EPL_COEF_DOWN_VOLTAGE_TIME 0x05000F78 // 1 byte NN BCD Ƿѹ�¼��ж���ʱʱ��
#define EPL_COEF_OVER_VOLTAGE_CONDITION 0x05000F79 // 0 byte   ��ѹ�ж�����
#define EPL_COEF_OVER_VOLTAGE_V_START 0x05000F79 // 2 byte NNN.N BCD ��ѹ�¼���ѹ��������
#define EPL_COEF_OVER_VOLTAGE_TIME 0x05000F7B // 1 byte NN BCD ��ѹ�¼��ж���ʱʱ��
#define EPL_COEF_CUT_VOLTAGE_CONDITION 0x05000F7C //  byte   �����ж�����
#define EPL_COEF_CUT_VOLTAGE_V_START 0x05000F7C // 2 byte NNN.N BCD �����¼���ѹ��������
#define EPL_COEF_CUT_VOLTAGE_I_START 0x05000F7E // 3 byte NN.NNNN BCD �����¼�������������
#define EPL_COEF_CUT_VOLTAGE_TIME 0x05000F81 // 1 byte NN BCD �����¼��ж���ʱʱ��
#define EPL_COEF_UNBALANCE_VOLTAGE_CONDITION 0x05000F82 //  byte   ��ѹ��ƽ���ж�����
#define EPL_COEF_UNBALANCE_VOLTAGE_DATA 0x05000F82 // 2 byte NN.NN BCD ��ѹ��ƽ������ֵ
#define EPL_COEF_UNBALANCE_VOLTAGE_TIME 0x05000F84 // 1 byte NN BCD ��ѹ��ƽ�����ж���ʱʱ��
#define EPL_COEF_UNBALANCE_CURRENT_CONDITION 0x05000F85 //  byte   ������ƽ���ж�����
#define EPL_COEF_UNBALANCE_CURRENT_DATA 0x05000F85 // 2 byte NN.NN BCD ������ƽ������ֵ
#define EPL_COEF_UNBALANCE_CURRENT_TIME 0x05000F87 // 1 byte NN BCD ������ƽ�����ж���ʱʱ��
#define EPL_COEF_LOSS_CURRENT_CONDITION 0x05000F88 //  byte   ʧ���ж�����
#define EPL_COEF_LOSS_CURRENT_V_START 0x05000F88 // 2 byte NNN.N BCD ʧ���¼���ѹ��������
#define EPL_COEF_LOSS_CURRENT_I_START 0x05000F8A // 3 byte NN.NNNN BCD ʧ���¼�������������
#define EPL_COEF_LOSS_CURRENT_I_END 0x05000F8D // 3 byte NN.NNNN BCD ʧ���¼�������������
#define EPL_COEF_LOSS_CURRENT_TIME 0x05000F90 // 1 byte NN BCD ʧ���¼��ж���ʱʱ��
#define EPL_COEF_OVER_CURRENT_CONDITION 0x05000F91 //  byte   �����ж�����
#define EPL_COEF_OVER_CURRENT_I_START 0x05000F91 // 2 byte NNN.N BCD �����¼�������������
#define EPL_COEF_OVER_CURRENT_TIME 0x05000F93 // 1 byte NN BCD �����¼��ж���ʱʱ��
#define EPL_COEF_CUT_CURRENT_CONDITION 0x05000F94 //  byte   �����ж�����
#define EPL_COEF_CUT_CURRENT_V_START 0x05000F94 // 2 byte NNN.N BCD �����¼���ѹ��������
#define EPL_COEF_CUT_CURRENT_I_START 0x05000F96 // 3 byte NN.NNNN BCD �����¼�������������
#define EPL_COEF_CUT_CURRENT_TIME 0x05000F99 // 1 byte NN BCD ����ʱ���ж���ʱʱ��
#define EPL_COEF_REVERSEPOWER_CONDITION 0x05000F9A //  byte   ���������ж�����
#define EPL_COEF_REVERSEPOWER_KW_START 0x05000F9A // 3 byte NN.NNNN BCD ���������¼��й����ʴ�������
#define EPL_COEF_REVERSEPOWER_KW_TIME 0x05000F9D // 1 byte NN BCD ���������¼��ж���ʱʱ��
#define EPL_COEF_OVER_KW_CONDITION 0x05000F9E //  byte   �����ж�����
#define EPL_COEF_OVER_KW_KW_START 0x05000F9E // 3 byte NN.NNNN BCD �����¼��й����ʴ�������
#define EPL_COEF_OVER_KW_TIME 0x05000FA1 // 1 byte NN BCD �����¼��ж���ʱʱ��
#define EPL_COEF_MONITOR_VOLTAGE_CONDITION 0x05000FA2 //  byte   ��ѹ�����ж�����
#define EPL_COEF_MONITOR_VOLTAGE_MAX 0x05000FA2 // 2 byte NNN.N BCD ��ѹ��������
#define EPL_COEF_MONITOR_VOLTAGE_MIN 0x05000FA4 // 2 byte NNN.N BCD ��ѹ��������
#define EPL_COEF_DEMAND_OVER_CONDITION 0x05000FA6 //  byte   ���������ж�����
#define EPL_COEF_DEMAND_OVER_KW_START 0x05000FA6 // 3 byte XX.XXXX kW BCD �й����������¼�������������
#define EPL_COEF_DEMAND_OVER_KVAR_START 0x05000FA9 // 3 byte XX.XXXX kW BCD �޹����������¼�������������
#define EPL_COEF_DEMAND_OVER_TIME 0x05000FAC // 1 byte NN BCD ���������¼��ж���ʱʱ��
#define EPL_COEF_OVERTOTALCOS_CONDITION 0x05000FAD //  byte   �ܹ��������ж�����
#define EPL_COEF_OVERTOTALCOS_START 0x05000FAD // 2 byte N.NNN BCD �ܹ������������޷�ֵ
#define EPL_COEF_OVERTOTALCOS_TIME 0x05000FAF // 1 byte NN BCD �ܹ��������������ж���ʱʱ��
#define EPL_COEF_UNBALANCE_SEVERITY_CURRENT_CONDITION 0x05000FB0 //  byte   �������ز�ƽ���ж�����
#define EPL_COEF_UNBALANCE_SEVERITY_CURRENT_DATA 0x05000FB0 // 2 byte NN.NN BCD �������ز�ƽ������ֵ
#define EPL_COEF_UNBALANCE_SEVERITY_CURRENT_TIME 0x05000FB2 // 1 byte NN BCD �������ز�ƽ�����ж���ʱʱ��
#define EPL_COEF_ALARM_SPEEK 0x05000FB3 // 4 byte XXXXXXXX HEX ������������
#define EPL_COEF_ALARM_LEDYELLOW 0x05000FB7 // 4 byte XXXXXXXX HEX �ƹⱨ��������
#define EPL_COEF_ALARM_LEDGREEN 0x05000FBB // 4 byte XXXXXXXX HEX �̹ⱨ��������
#define EPL_COEF_ALARM_LCD_DISPLLAY 0x05000FBF // 4 byte XXXXXXXX HEX Һ�����Ա���������
#define EPL_COEF_ALARM_LCD_ERROR 0x05000FC3 // 4 byte XXXXXXXX HEX Һ�����󱨾�������
// #define  0x05000FC7 // 4 byte  BCD 
#define EPL_COEF_PROGRAM_TIME 0x05000FCB // 2 byte NN �� BCD ���ά��ʱ��
#define EPL_COEF_DISPLAY_MODE_CHANGE_TIME 0x05000FCD // 2 byte NNNN�� BCD �����л�ʱ��
#define EPL_COEF_REMOTE_WAKEUP_ENABLE 0x05000FCF // 1 byte NN BCD ���⻽��ģʽ
#define EPL_COEF_POWERDOWN_ALLLOSSVOLTAGE_CONDITION 0x05000FD0 // 5 byte XX%Un+XX.XX%Ib+NNs BCD ȫʧѹ�ж�����(ͣ��)
#define EPL_COEF_CLR_METER_ENABLE_TIMES 0x05000FD5 // 1 byte XX BCD �����������<5ģʽ1��ʹ�ù㶫��1003(�㶫ʹ��)FM1_DIANLIANG_CLEAR_COUNT
// #define  0x05000FD6 // 34 byte NNNNNN.NN BCD ��������1��ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD ��������2��ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD �ڻ�������ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD ͸֧������ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD �������1��ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD �������2��ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD ͸֧�����ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD �ڻ������ֵ(��ʹ��)
// #define  0x05000FF8 // 0 byte NNNNNN.NN BCD ��բ��������ֵ(��ʹ��)
#define EPL_COEF_A_G 0x05000FF8 // 0 byte N.NNN BCD A��絼ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_A_B 0x05000FF8 // 0 byte N.NNN BCD A�����ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_A_R 0x05000FF8 // 0 byte N.NNN BCD A�����ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_A_X 0x05000FF8 // 0 byte N.NNN BCD A��翹ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_B_G 0x05000FF8 // 0 byte N.NNN BCD B��絼ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_B_B 0x05000FF8 // 0 byte N.NNN BCD B�����ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_B_R 0x05000FF8 // 0 byte N.NNN BCD B�����ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_B_X 0x05000FF8 // 0 byte N.NNN BCD B��翹ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_C_G 0x05000FF8 // 0 byte N.NNN BCD C��絼ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_C_B 0x05000FF8 // 0 byte N.NNN BCD C�����ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_C_R 0x05000FF8 // 0 byte N.NNN BCD C�����ϵ��(�Ѿ�ɾ������ʹ��)
#define EPL_COEF_C_X 0x05000FF8 // 0 byte N.NNN BCD C��翹ϵ��(�Ѿ�ɾ������ʹ��)
// #define  0x05000FF8 // 0 byte  BCD 
// #define  0x05000FF8 // 0 byte  BCD 
#define EPL_SOFT_TIME 0x05000FF8 // 0 byte hhmmss BCD ʱ��
#define EPL_SOFT_SECOND 0x05000FF8 // 1 byte ss BCD ��
#define EPL_SOFT_MINUTE 0x05000FF9 // 1 byte mm BCD ��
#define EPL_SOFT_HOUR 0x05000FFA // 1 byte hh BCD ʱ
#define EPL_SOFT_DATE 0x05000FFB // 0 byte YYMMDDWW BCD ���ڼ�����
#define EPL_SOFT_DAY 0x05000FFB // 1 byte DD BCD ��
#define EPL_SOFT_MONTH 0x05000FFC // 1 byte MM BCD ��
#define EPL_SOFT_YEAR 0x05000FFD // 1 byte YY BCD ��
#define EPL_SOFT_WEEK 0x05000FFE // 1 byte WW BCD ����
#define EPL_DEMAND_CYCLE_TIME 0x05000FFF // 1 byte XX BCD �����������
#define EPL_DEMAND_PAT_TIME 0x05001000 // 1 byte XX BCD ����ʱ��
#define EPL_POWER_PULSE_TIME 0x05001001 // 2 byte XXXX BCD У��������
#define EPL_COEF_2SEASONCHANGE_TIME 0x05001003 // 5 byte YYMMDDHHMM BCD ����ʱ�����л�ʱ��(�л��꣬�Զ�����)
#define EPL_COEF_2DAYTABLECHANGE_TIME 0x05001008 // 5 byte YYMMDDHHMM BCD ����ʱ�α��л�ʱ��(�л��꣬�Զ�����)
#define EPL_COEF_STEPPRICE_CHANGETIME 0x0500100D // 5 byte YYMMDDHHMM BCD ���׽��ݱ��л�ʱ��(�л��꣬�Զ�����)
#define EPL_COEF_PERIODPRICE_CHANGETIME 0x05001012 // 5 byte YYMMDDHHMM BCD ���׷��ʵ���л�ʱ��(�л��꣬�Զ�����)
#define EPL_COEF_SEASONTABLE_MAX_NUM 0x05001017 // 1 byte XX BCD ��ʱ����PС��14
#define EPL_COEF_DAYTABLE_MAX_NUM 0x05001018 // 1 byte XX BCD ��ʱ�α���QС��8
#define EPL_COEF_PERIOD_MAX_NUM 0x05001019 // 1 byte XX BCD ��ʱ����(ÿ���л���)mС��14
#define EPL_COEF_PRICE_MAX_NUM 0x0500101A // 1 byte XX BCD ������kС��63
#define EPL_COEF_HOLIDAY_MAX_MUN 0x0500101B // 2 byte XXXX BCD ����������nС��254
#define EPL_COEF_HUMOROUS_MAX_NUM 0x0500101D // 1 byte XX BCD г����������
#define EPL_COEF_STEP_NUM 0x0500101E // 1 byte XX BCD ���ݸ���
#define EPL_COEF_AUTO_TURNPAGE_NUM 0x0500101F // 1 byte XX BCD �Զ�ѭ����ʾ����
#define EPL_COEF_TURNPAGE_TIME 0x05001020 // 1 byte XX BCD ÿ����ʾʱ��
#define EPL_COEF_POWER_POINT_NUM 0x05001021 // 1 byte XX BCD ��ʾ����С��λ��
#define EPL_COEF_DEMAND_POINT_NUM 0x05001022 // 1 byte XX BCD ��ʾ����(�������)С��λ��
#define EPL_COEF_KEY_TURNPAGE_NUM 0x05001023 // 1 byte XX BCD ����ѭ����ʾ����
#define EPL_COEF_PT_NUM 0x05001024 // 3 byte XXXXXX BCD �������������
#define EPL_COEF_CT_NUM 0x05001027 // 3 byte XXXXXX BCD ��ѹ���������
#define EPL_COEF_PULSEMODE 0x0500102A // 1 byte  BCD �๦������ź����
#define EPL_CURRENT_MODULE_DATA 0x0500102B // 1 byte  BCD ����ͨѶ���߼��ź�ǿ��ָʾ
#define EPL_COEF_DATA_END 0x0500102C // 0 byte   �������ݽ���
// #define  0x0500102C // 188 byte   ����
#define EPL_PUBLIC_HOLIDAY_START 0x050010E8 // 0 byte YYMMDDNN BCD ���������ڼ���ʱ�α��
#define EPL_PUBLIC_HOLIDAY001 0x050010E8 // 4 byte YYMMDDNN BCD ��001�����������ڼ���ʱ�α��
#define EPL_PUBLIC_HOLIDAY002 0x050010EC // 1016 byte YYMMDDNN BCD ��002�����������ڼ���ʱ�α��(������254��)
#define EPL_PUBLIC_HOLIDAY256 0x050014E4 // 4 byte YYMMDDNN BCD ��256�����������ڼ���ʱ�α��
#define EPL_DISPLAY_ALL_START 0x050014E8 // 0 byte   ������������ʼ
#define EPL_DISPLAY_AUTOSET_START 0x050014E8 // 0 byte   �Զ�ѭ����ʾ��������ʼ
#define EPL_DISPLAY_AUTOSET_001 0x050014E8 // 5 byte NNNNNNNN BCD �Զ�ѭ����ʾ��1����ʾ������
#define EPL_DISPLAY_AUTOSET_002 0x050014ED // 1270 byte NNNNNNNN BCD �Զ�ѭ����ʾ��2����ʾ������(������254��)
#define EPL_DISPLAY_AUTOSET_256 0x050019E3 // 5 byte NNNNNNNN BCD �Զ�ѭ����ʾ��256����ʾ������
// #define  0x050019E8 // 256 byte  BCD �Զ�ѭ����ʾ�������
#define EPL_DISPLAY_KEYSET_START 0x05001AE8 // 0 byte  BCD ����ѭ����ʾ������ʼ
#define EPL_DISPLAY_KEYSET_001 0x05001AE8 // 5 byte NNNNNNNN BCD ����ѭ����ʾ��1����ʾ������
#define EPL_DISPLAY_KEYSET_002 0x05001AED // 1270 byte NNNNNNNN BCD ����ѭ����ʾ��2����ʾ������
#define EPL_DISPLAY_KEYSET_256 0x05001FE3 // 5 byte NNNNNNNN BCD ����ѭ����ʾ��256����ʾ������
// #define  0x05001FE8 // 0 byte   ����ѭ����ʾ�������
// #define  0x05001FE8 // 0 byte   ����
// #define  0x05001FE8 // 0 byte   ͨѶ������
#define EPL_METER_ASCII_TYPE_UN 0x05001FE8 // 6 byte  ASCII ���ѹ(ASCII��)
#define EPL_METER_ASCII_TYPE_IB 0x05001FEE // 6 byte  ASCII �������������(ASCII��)
#define EPL_METER_ASCII_TYPE_IMAX 0x05001FF4 // 6 byte  ASCII ������(ASCII��)
#define EPL_METER_ASCII_ACTIVE_PRECISION 0x05001FFA // 4 byte  ASCII �й�׼ȷ�ȵȼ�(ASCII��)
#define EPL_METER_ASCII_REACTIVE_PRECISION 0x05001FFE // 4 byte  ASCII �޹�׼ȷ�ȵȼ�(ASCII��)
#define EPL_METER_ASCII_PRODUCE_TIME 0x05002002 // 10 byte  ASCII ��������(ASCII��)
#define EPL_METER_ASCII_METER_TYPE 0x0500200C // 10 byte  ASCII ����ͺ�(ASCII 645-2007ͨѶ��Լ)
#define EPL_METER_ASCII_COMM_VER 0x05002016 // 16 byte  ASCII Э��汾��(ASCII 645-2007ͨѶ��Լ)
#define EPL_METER_ASCII_SOFT_VER 0x05002026 // 32 byte  ASCII ����汾��(ASCII 645-2007ͨѶ��Լ)
#define EPL_METER_ASCII_HARD_VER 0x05002046 // 32 byte  ASCII Ӳ���汾��(ASCII 645-2007ͨѶ��Լ)
#define EPL_METER_ASCII_FACTORY_NUM 0x05002066 // 32 byte  ASCII ���ұ��(ASCII 645-2007ͨѶ��Լ)
// #define  0x05002086 // 98 byte   ����
#define EPL_KWH_ALL_CHECK_START 0x05002168 // 256 byte   A��������У��
// #define  0x050020E8 // 128 byte   ����
#define EPL_KWH_RESIDUE_CLAC_START 0x05002268 // 268 byte   �����������β����ʼ
// #define  0x05002168 // 32 byte   ����
#define EPL_KWH_RESIDUE_LOST_COPPER_IRON_START 0x05002374 // 32 byte XXXX HEX ͭ���������β����ʼ
// #define  0x05002394 // 0 byte   ����
// #define  0x05002394 // 0 byte   
#define EPL_APHOUR_CLACL_START 0x05002394 // 0 byte   ����Сʱ�����ݼ�����ʼ
#define EPL_APHOUR_LOSS_V_START 0x05002394 // 0 byte   ʧѹ�ڼ��ܵİ���Сʱ��β��
#define EPL_APHOUR_LOSS_AV_A_START 0x05002394 // 2 byte XXXX HEX A��ʧѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_AV_B_START 0x05002396 // 2 byte XXXX HEX A��ʧѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_AV_C_START 0x05002398 // 2 byte XXXX HEX A��ʧѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_BV_A_START 0x0500239A // 2 byte XXXX HEX B��ʧѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_BV_B_START 0x0500239C // 2 byte XXXX HEX B��ʧѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_BV_C_START 0x0500239E // 2 byte XXXX HEX B��ʧѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_CV_A_START 0x050023A0 // 2 byte XXXX HEX C��ʧѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_CV_B_START 0x050023A2 // 2 byte XXXX HEX C��ʧѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_LOSS_CV_C_START 0x050023A4 // 2 byte XXXX HEX C��ʧѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_V_START 0x050023A6 // 0 byte   Ƿѹ�ڼ��ܵİ���Сʱ��β��
#define EPL_APHOUR_DOWN_AV_A_START 0x050023A6 // 2 byte XXXX HEX A��Ƿѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_AV_B_START 0x050023A8 // 2 byte XXXX HEX A��Ƿѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_AV_C_START 0x050023AA // 2 byte XXXX HEX A��Ƿѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_BV_A_START 0x050023AC // 2 byte XXXX HEX B��Ƿѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_BV_B_START 0x050023AE // 2 byte XXXX HEX B��Ƿѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_BV_C_START 0x050023B0 // 2 byte XXXX HEX B��Ƿѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_CV_A_START 0x050023B2 // 2 byte XXXX HEX C��Ƿѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_CV_B_START 0x050023B4 // 2 byte XXXX HEX C��Ƿѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_DOWN_CV_C_START 0x050023B6 // 2 byte XXXX HEX C��Ƿѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_OVER_V_START 0x050023B8 // 0 byte   ��ѹ�ڼ��ܵİ���Сʱ��β��
#define EPL_APHOUR_OVER_AV_A_START 0x050023B8 // 2 byte XXXX HEX A���ѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_OVER_AV_B_START 0x050023BA // 2 byte XXXX HEX A���ѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_OVER_AV_C_START 0x050023BC // 2 byte XXXX HEX A���ѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_OVER_BV_A_START 0x050023BE // 2 byte XXXX HEX B���ѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_OVER_BV_B_START 0x050023C0 // 2 byte XXXX HEX B���ѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_OVER_BV_C_START 0x050023C2 // 2 byte XXXX HEX B���ѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_OVER_CV_A_START 0x050023C4 // 2 byte XXXX HEX C���ѹ�ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_OVER_CV_B_START 0x050023C6 // 2 byte XXXX HEX C���ѹ�ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_OVER_CV_C_START 0x050023C8 // 2 byte XXXX HEX C���ѹ�ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_CUT_V_START 0x050023CA // 0 byte   �����ڼ��ܵİ���Сʱ��β��
#define EPL_APHOUR_CUT_AV_A_START 0x050023CA // 2 byte XXXX HEX A������ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_CUT_AV_B_START 0x050023CC // 2 byte XXXX HEX A������ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_CUT_AV_C_START 0x050023CE // 2 byte XXXX HEX A������ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_CUT_BV_A_START 0x050023D0 // 2 byte XXXX HEX B������ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_CUT_BV_B_START 0x050023D2 // 2 byte XXXX HEX B������ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_CUT_BV_C_START 0x050023D4 // 2 byte XXXX HEX B������ڼ�C��İ���Сʱ��β��
#define EPL_APHOUR_CUT_CV_A_START 0x050023D6 // 2 byte XXXX HEX C������ڼ�A��İ���Сʱ��β��
#define EPL_APHOUR_CUT_CV_B_START 0x050023D8 // 2 byte XXXX HEX C������ڼ�B��İ���Сʱ��β��
#define EPL_APHOUR_CUT_CV_C_START 0x050023DA // 2 byte XXXX HEX C������ڼ�C��İ���Сʱ��β��
// #define  0x050023DC // 0 byte   ����
// #define  0x050023DC // 184 byte   ����
// #define  0x05002494 // 512 byte   ����
#define EPL_TWOTABLE_ADDR_START 0x05002694 // 512 byte XXXXXX BCD ���α�����ָ����ʼ
#define EPL_CURRENT_BAT_USETIME 0x05002894 // 4 byte XXXXXXXX BCD �ڲ���ع���ʱ��
#define EPL_TOTAL_DATA_START 0x05002898 // 0 byte  BCD �ۼ�������ʼ
#define EPL_PROGRAM_COUNT 0x05002898 // 4 byte XXXXXX BCD ����ܴ���
#define EPL_CLR_METER_COUNT 0x0500289C // 4 byte XXXXXX BCD ��������ܴ���
#define EPL_CLR_DEMAND_COUNT 0x050028A0 // 4 byte XXXXXX BCD ���������ܴ���
#define EPL_CLR_EVENT_COUNT 0x050028A4 // 4 byte XXXXXX BCD �¼������ܴ���
#define EPL_PROGRAM_TIME_COUNT 0x050028A8 // 4 byte XXXXXX BCD Уʱ�ܴ���
#define EPL_PROGRAM_PERIOD_COUNT 0x050028AC // 4 byte XXXXXX BCD ʱ�α���ܴ���
#define EPL_PROGRAM_SEASON_COUNT 0x050028B0 // 4 byte XXXXXX BCD ʱ�������ܴ���
#define EPL_PROGRAM_CHARACTER_REST_COUNT 0x050028B4 // 4 byte XXXXXX BCD �����ձ���ܴ���
#define EPL_PROGRAM_PUBLIC_HOLIDAY_COUNT 0x050028B8 // 4 byte XXXXXX BCD �ڼ��ձ���ܴ���
#define EPL_PROGRAM_ACTIVE_COM_COUNT 0x050028BC // 4 byte XXXXXX BCD �й���Ϸ�ʽ����ܴ���
#define EPL_PROGRAM_REACTIVE1_COM_COUNT 0x050028C0 // 4 byte XXXXXX BCD �޹���Ϸ�ʽ1����ܴ���
#define EPL_PROGRAM_REACTIVE2_COM_COUNT 0x050028C4 // 4 byte XXXXXX BCD �޹���Ϸ�ʽ2����ܴ���
#define EPL_PROGRAM_BALANCE_DAY_COUNT 0x050028C8 // 4 byte XXXXXX BCD �����ձ���ܴ���
#define EPL_POWER_DOWN_COUNT 0x050028CC // 4 byte XXXXXX BCD �����ܴ���
// #define  0x050028D0 // 68 byte   ����
#define EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START 0x05002914 // 0 byte   ���µ�ѹ�ϸ���ͳ�����ݿ�
#define EPL_VOLTAGE_ALL_MONITOR_ERR_TIME 0x05002914 // 3 byte XXXXXX BCD ��ѹ��ⲻ�ϸ�ʱ��(��)
#define EPL_VOLTAGE_ALL_MONITOR_TIME 0x05002917 // 3 byte XXXXXX BCD ��ѹ���ʱ��(��)
#define EPL_VOLTAGE_ALL_MONITOR_OK 0x0500291A // 3 byte XXXX.XX BCD ��ѹ�ϸ���(%)
#define EPL_VOLTAGE_ALL_MONITOR_ERR 0x0500291D // 3 byte XXXX.XX BCD ��ѹ������(%)
#define EPL_VOLTAGE_ALL_MONITOR_OVER_TIME 0x05002920 // 3 byte XXXXXX BCD ��ѹ������ʱ��(��)
#define EPL_VOLTAGE_ALL_MONITOR_DOWN_TIME 0x05002923 // 3 byte XXXXXX BCD ��ѹ������ʱ��(��)
#define EPL_VOLTAGE_ALL_MONITOR_MAX_VOLTAGE 0x05002926 // 2 byte XXX.X BCD ��ߵ�ѹ
#define EPL_VOLTAGE_ALL_MONITOR_MAX_VOLTAGE_TIME 0x05002928 // 4 byte MMDDhhmm BCD ��ߵ�ѹ����ʱ��
#define EPL_VOLTAGE_ALL_MONITOR_MIN_VOLTAGE 0x0500292C // 2 byte XXX.X BCD ��͵�ѹ
#define EPL_VOLTAGE_ALL_MONITOR_MIN_VOLTAGE_TIME 0x0500292E // 4 byte MMDDhhmm BCD ��͵�ѹ����ʱ��
#define EPL_VOLTAGE_A_MONITOR_STAT_BLOCK_START 0x05002932 // 0 byte   ����A���ѹ�ϸ���ͳ�����ݿ�
#define EPL_VOLTAGE_A_MONITOR_TIME 0x05002932 // 3 byte XXXXXX BCD A���ѹ���ʱ��(��)
#define EPL_VOLTAGE_A_MONITOR_OK 0x05002935 // 3 byte XXXX.XX BCD A���ѹ�ϸ���(%)
#define EPL_VOLTAGE_A_MONITOR_ERR 0x05002938 // 3 byte XXXX.XX BCD A���ѹ������(%)
#define EPL_VOLTAGE_A_MONITOR_OVER_TIME 0x0500293B // 3 byte XXXXXX BCD A���ѹ������ʱ��(��)
#define EPL_VOLTAGE_A_MONITOR_DOWN_TIME 0x0500293E // 3 byte XXXXXX BCD A���ѹ������ʱ��(��)
#define EPL_VOLTAGE_A_MONITOR_MAX_VOLTAGE 0x05002941 // 2 byte XXX.X BCD A����ߵ�ѹ
#define EPL_VOLTAGE_A_MONITOR_MAX_VOLTAGE_TIME 0x05002943 // 4 byte MMDDhhmm BCD A����ߵ�ѹ����ʱ��
#define EPL_VOLTAGE_A_MONITOR_MIN_VOLTAGE 0x05002947 // 2 byte XXX.X BCD A����͵�ѹ
#define EPL_VOLTAGE_A_MONITOR_MIN_VOLTAGE_TIME 0x05002949 // 4 byte MMDDhhmm BCD A����͵�ѹ����ʱ��
#define EPL_VOLTAGE_B_MONITOR_STAT_BLOCK_START 0x0500294D // 0 byte   ����B���ѹ�ϸ���ͳ�����ݿ�
#define EPL_VOLTAGE_B_MONITOR_TIME 0x0500294D // 3 byte XXXXXX BCD B���ѹ���ʱ��(��)
#define EPL_VOLTAGE_B_MONITOR_OK 0x05002950 // 3 byte XXXX.XX BCD B���ѹ�ϸ���(%)
#define EPL_VOLTAGE_B_MONITOR_ERR 0x05002953 // 3 byte XXXX.XX BCD B���ѹ������(%)
#define EPL_VOLTAGE_B_MONITOR_OVER_TIME 0x05002956 // 3 byte XXXXXX BCD B���ѹ������ʱ��(��)
#define EPL_VOLTAGE_B_MONITOR_DOWN_TIME 0x05002959 // 3 byte XXXXXX BCD B���ѹ������ʱ��(��)
#define EPL_VOLTAGE_B_MONITOR_MAX_VOLTAGE 0x0500295C // 2 byte XXX.X BCD B����ߵ�ѹ
#define EPL_VOLTAGE_B_MONITOR_MAX_VOLTAGE_TIME 0x0500295E // 4 byte MMDDhhmm BCD B����ߵ�ѹ����ʱ��
#define EPL_VOLTAGE_B_MONITOR_MIN_VOLTAGE 0x05002962 // 2 byte XXX.X BCD B����͵�ѹ
#define EPL_VOLTAGE_B_MONITOR_MIN_VOLTAGE_TIME 0x05002964 // 4 byte MMDDhhmm BCD B����͵�ѹ����ʱ��
#define EPL_VOLTAGE_C_MONITOR_STAT_BLOCK_START 0x05002968 // 0 byte   ����C���ѹ�ϸ���ͳ�����ݿ�
#define EPL_VOLTAGE_C_MONITOR_TIME 0x05002968 // 3 byte XXXXXX BCD C���ѹ���ʱ��(��)
#define EPL_VOLTAGE_C_MONITOR_OK 0x0500296B // 3 byte XXXX.XX BCD C���ѹ�ϸ���(%)
#define EPL_VOLTAGE_C_MONITOR_ERR 0x0500296E // 3 byte XXXX.XX BCD C���ѹ������(%)
#define EPL_VOLTAGE_C_MONITOR_OVER_TIME 0x05002971 // 3 byte XXXXXX BCD C���ѹ������ʱ��(��)
#define EPL_VOLTAGE_C_MONITOR_DOWN_TIME 0x05002974 // 3 byte XXXXXX BCD C���ѹ������ʱ��(��)
#define EPL_VOLTAGE_C_MONITOR_MAX_VOLTAGE 0x05002977 // 2 byte XXX.X BCD C����ߵ�ѹ
#define EPL_VOLTAGE_C_MONITOR_MAX_VOLTAGE_TIME 0x05002979 // 4 byte MMDDhhmm BCD C����ߵ�ѹ����ʱ��
#define EPL_VOLTAGE_C_MONITOR_MIN_VOLTAGE 0x0500297D // 2 byte XXX.X BCD C����͵�ѹ
#define EPL_VOLTAGE_C_MONITOR_MIN_VOLTAGE_TIME 0x0500297F // 4 byte MMDDhhmm BCD C����͵�ѹ����ʱ��
#define EPL_ALLLOSS_VOLTAGE_COUNT 0x05002983 // 3 byte XXXXXX BCD ȫʧѹ�ܴ���
#define EPL_ALLLOSS_VOLTAGE_TIME 0x05002986 // 3 byte XXXXXX BCD ȫʧѹ���ۼ�ʱ��
#define EPL_ACPOWER_LOSS_COUNT 0x05002989 // 3 byte XXXXXX BCD ������Դʧ���ܴ���
#define EPL_ACPOWER_LOSS_TIME 0x0500298C // 3 byte XXXXXX BCD ������Դʧ�����ۼ�ʱ��
// #define  0x0500298F // 5 byte   ����
#define EPL_TOTAL_TIME_TOTAL_START 0x05002994 // 0 byte   �����¼��ۼ�ʱ����ʼ
#define EPL_TOTAL_LOSS_V_TIME_TOTAL 0x05002994 // 3 byte NNNNNN BCD ʧѹ���ۼ�ʱ��(��)
#define EPL_TOTAL_LOSS_AV_TIME_TOTAL 0x05002997 // 3 byte NNNNNN BCD A��ʧѹ���ۼ�ʱ��
#define EPL_TOTAL_LOSS_BV_TIME_TOTAL 0x0500299A // 3 byte NNNNNN BCD B��ʧѹ���ۼ�ʱ��
#define EPL_TOTAL_LOSS_CV_TIME_TOTAL 0x0500299D // 3 byte NNNNNN BCD C��ʧѹ���ۼ�ʱ��
// #define  0x050029A0 // 0 byte   Ƿѹ���ۼ�ʱ��(��)TOTAL_DOWN_V_TIME_TOTAL
#define EPL_TOTAL_DOWN_AV_TIME_TOTAL 0x050029A0 // 3 byte NNNNNN BCD A��Ƿѹ���ۼ�ʱ��
#define EPL_TOTAL_DOWN_BV_TIME_TOTAL 0x050029A3 // 3 byte NNNNNN BCD B��Ƿѹ���ۼ�ʱ��
#define EPL_TOTAL_DOWN_CV_TIME_TOTAL 0x050029A6 // 3 byte NNNNNN BCD C��Ƿѹ���ۼ�ʱ��
// #define  0x050029A9 // 0 byte   ��ѹ���ۼ�ʱ��(��)TOTAL_OVER_V_TIME_TOTAL
#define EPL_TOTAL_OVER_AV_TIME_TOTAL 0x050029A9 // 3 byte NNNNNN BCD A���ѹ���ۼ�ʱ��
#define EPL_TOTAL_OVER_BV_TIME_TOTAL 0x050029AC // 3 byte NNNNNN BCD B���ѹ���ۼ�ʱ��
#define EPL_TOTAL_OVER_CV_TIME_TOTAL 0x050029AF // 3 byte NNNNNN BCD C���ѹ���ۼ�ʱ��
// #define  0x050029B2 // 0 byte   �������ۼ�ʱ��(��)TOTAL_CUT_V_TIME_TOTAL
#define EPL_TOTAL_CUT_AV_TIME_TOTAL 0x050029B2 // 3 byte NNNNNN BCD A��������ۼ�ʱ��
#define EPL_TOTAL_CUT_BV_TIME_TOTAL 0x050029B5 // 3 byte NNNNNN BCD B��������ۼ�ʱ��
#define EPL_TOTAL_CUT_CV_TIME_TOTAL 0x050029B8 // 3 byte NNNNNN BCD C��������ۼ�ʱ��
// #define  0x050029BB // 0 byte   ʧ�����ۼ�ʱ��(��)TOTAL_LOSS_I_TIME_TOTAL
#define EPL_TOTAL_LOSS_AI_TIME_TOTAL 0x050029BB // 3 byte NNNNNN BCD A��ʧ�����ۼ�ʱ��
#define EPL_TOTAL_LOSS_BI_TIME_TOTAL 0x050029BE // 3 byte NNNNNN BCD B��ʧ�����ۼ�ʱ��
#define EPL_TOTAL_LOSS_CI_TIME_TOTAL 0x050029C1 // 3 byte NNNNNN BCD C��ʧ�����ۼ�ʱ��
// #define  0x050029C4 // 0 byte   �������ۼ�ʱ��(��)TOTAL_OVER_I_TIME_TOTAL
#define EPL_TOTAL_OVER_AI_TIME_TOTAL 0x050029C4 // 3 byte NNNNNN BCD A��������ۼ�ʱ��
#define EPL_TOTAL_OVER_BI_TIME_TOTAL 0x050029C7 // 3 byte NNNNNN BCD B��������ۼ�ʱ��
#define EPL_TOTAL_OVER_CI_TIME_TOTAL 0x050029CA // 3 byte NNNNNN BCD C��������ۼ�ʱ��
// #define  0x050029CD // 0 byte   �������ۼ�ʱ��(��)TOTAL_CUT_I_TIME_TOTAL
#define EPL_TOTAL_CUT_AI_TIME_TOTAL 0x050029CD // 3 byte NNNNNN BCD A��������ۼ�ʱ��
#define EPL_TOTAL_CUT_BI_TIME_TOTAL 0x050029D0 // 3 byte NNNNNN BCD B��������ۼ�ʱ��
#define EPL_TOTAL_CUT_CI_TIME_TOTAL 0x050029D3 // 3 byte NNNNNN BCD C��������ۼ�ʱ��
#define EPL_TOTAL_ORDER_VOLTAGE_TIME_TOTAL 0x050029D6 // 3 byte NNNNNN BCD ��ѹ���������ۼ�ʱ��
#define EPL_TOTAL_ORDER_CURRENT_TIME_TOTAL 0x050029D9 // 3 byte NNNNNN BCD �������������ۼ�ʱ��
#define EPL_TOTAL_UNBALANCE_VOLTAGE_TIME_TOTAL 0x050029DC // 3 byte NNNNNN BCD ��ѹ��ƽ�����ۼ�ʱ��
#define EPL_TOTAL_UNBALANCE_CURRENT_TIME_TOTAL 0x050029DF // 3 byte NNNNNN BCD ������ƽ�����ۼ�ʱ��
#define EPL_TOTAL_UNBALANCE_SEVERITY_CURRENT_TIME_TOTAL 0x050029E2 // 3 byte NNNNNN BCD �������ز�ƽ�����ۼ�ʱ��
#define EPL_TOTAL_OVERTOTALCOS_TIME_TOTAL 0x050029E5 // 3 byte NNNNNN BCD �ܹ��������������ۼ�ʱ��
#define EPL_TOTAL_REVERSE_ALL_TIME_TOTAL 0x050029E8 // 3 byte NNNNNN BCD �ܹ��ʷ������ۼ�ʱ��
#define EPL_TOTAL_REVERSE_A_TIME_TOTAL 0x050029EB // 3 byte NNNNNN BCD A�ೱ���������ۼ�ʱ��
#define EPL_TOTAL_REVERSE_B_TIME_TOTAL 0x050029EE // 3 byte NNNNNN BCD B�ೱ���������ۼ�ʱ��
#define EPL_TOTAL_REVERSE_C_TIME_TOTAL 0x050029F1 // 3 byte NNNNNN BCD C�ೱ���������ۼ�ʱ��
#define EPL_TOTAL_POWEROVER_ALL_TIME_TOTAL 0x050029F4 // 3 byte NNNNNN BCD �ܹ��ʹ������ۼ�ʱ��
#define EPL_TOTAL_POWEROVER_A_TIME_TOTAL 0x050029F7 // 3 byte NNNNNN BCD A��������ۼ�ʱ��
#define EPL_TOTAL_POWEROVER_B_TIME_TOTAL 0x050029FA // 3 byte NNNNNN BCD B��������ۼ�ʱ��
#define EPL_TOTAL_POWEROVER_C_TIME_TOTAL 0x050029FD // 3 byte NNNNNN BCD C��������ۼ�ʱ��
#define EPL_TOTAL_LOSS_V_BLOCK_ALL_START 0x05002A00 // 0 byte   ����ʧѹ�ۼ����ݿ��׵�ַ
#define EPL_TOTAL_LOSS_V_COUNT_TOTAL 0x05002A00 // 4 byte NNNNNN BCD ʧѹ���ۼƴ���(��)
#define EPL_TOTAL_LOSS_AV_COUNT_TOTAL 0x05002A04 // 4 byte NNNNNN BCD A��ʧѹ���ۼƴ���
#define EPL_TOTAL_LOSS_BV_COUNT_TOTAL 0x05002A08 // 4 byte NNNNNN BCD B��ʧѹ���ۼƴ���
#define EPL_TOTAL_LOSS_CV_COUNT_TOTAL 0x05002A0C // 4 byte NNNNNN BCD C��ʧѹ���ۼƴ���
#define EPL_TOTAL_LOSS_V_LAST_START 0x05002A10 // 6 byte YYMMDDhhmmss BCD ���1��ʧѹ����ʱ��(��)
#define EPL_TOTAL_LOSS_V_LAST_END 0x05002A16 // 6 byte YYMMDDhhmmss BCD ���1��ʧѹ����ʱ��(��)
#define EPL_TOTAL_DOWN_V_BLOCK_ALL_START 0x05002A1C // 0 byte   ����Ƿѹ�ۼ����ݿ��׵�ַ
// #define  0x05002A1C // 0 byte   Ƿѹ���ۼƴ���(��)TOTAL_DOWN_V_COUNT_TOTAL
#define EPL_TOTAL_DOWN_AV_COUNT_TOTAL 0x05002A1C // 4 byte NNNNNN BCD A��Ƿѹ���ۼƴ���
#define EPL_TOTAL_DOWN_BV_COUNT_TOTAL 0x05002A20 // 4 byte NNNNNN BCD B��Ƿѹ���ۼƴ���
#define EPL_TOTAL_DOWN_CV_COUNT_TOTAL 0x05002A24 // 4 byte NNNNNN BCD C��Ƿѹ���ۼƴ���
// #define  0x05002A28 // 0 byte   ���1��Ƿѹ����ʱ��(��)TOTAL_DOWN_V_LAST_START
// #define  0x05002A28 // 0 byte   ���1��Ƿѹ����ʱ��(��)TOTAL_DOWN_V_LAST_END
#define EPL_TOTAL_OVER_V_BLOCK_ALL_START 0x05002A28 // 0 byte   ���й�ѹ�ۼ����ݿ��׵�ַ
// #define  0x05002A28 // 0 byte   ��ѹ���ۼƴ���(��)TOTAL_OVER_V_COUNT_TOTAL
#define EPL_TOTAL_OVER_AV_COUNT_TOTAL 0x05002A28 // 4 byte NNNNNN BCD A���ѹ���ۼƴ���
#define EPL_TOTAL_OVER_BV_COUNT_TOTAL 0x05002A2C // 4 byte NNNNNN BCD B���ѹ���ۼƴ���
#define EPL_TOTAL_OVER_CV_COUNT_TOTAL 0x05002A30 // 4 byte NNNNNN BCD C���ѹ���ۼƴ���
// #define  0x05002A34 // 0 byte   ���1�ι�ѹ����ʱ��(��)TOTAL_OVER_V_LAST_START
// #define  0x05002A34 // 0 byte   ���1�ι�ѹ����ʱ��(��)TOTAL_OVER_V_LAST_END
#define EPL_TOTAL_CUT_V_BLOCK_ALL_START 0x05002A34 // 0 byte   ���ж����ۼ����ݿ��׵�ַ
// #define  0x05002A34 // 0 byte   �������ۼƴ���(��)TOTAL_CUT_V_COUNT_TOTAL
#define EPL_TOTAL_CUT_AV_COUNT_TOTAL 0x05002A34 // 4 byte NNNNNN BCD A��������ۼƴ���
#define EPL_TOTAL_CUT_BV_COUNT_TOTAL 0x05002A38 // 4 byte NNNNNN BCD B��������ۼƴ���
#define EPL_TOTAL_CUT_CV_COUNT_TOTAL 0x05002A3C // 4 byte NNNNNN BCD C��������ۼƴ���
// #define  0x05002A40 // 0 byte   ���1�ζ��෢��ʱ��(��)TOTAL_CUT_V_LAST_START
// #define  0x05002A40 // 0 byte   ���1�ζ������ʱ��(��)TOTAL_CUT_V_LAST_END
#define EPL_TOTAL_LOSS_I_BLOCK_ALL_START 0x05002A40 // 0 byte   ����ʧ���ۼ����ݿ��׵�ַ
// #define  0x05002A40 // 0 byte   ʧ�����ۼƴ���(��)TOTAL_LOSS_I_COUNT_TOTAL
#define EPL_TOTAL_LOSS_AI_COUNT_TOTAL 0x05002A40 // 4 byte NNNNNN BCD A��ʧ�����ۼƴ���
#define EPL_TOTAL_LOSS_BI_COUNT_TOTAL 0x05002A44 // 4 byte NNNNNN BCD B��ʧ�����ۼƴ���
#define EPL_TOTAL_LOSS_CI_COUNT_TOTAL 0x05002A48 // 4 byte NNNNNN BCD C��ʧ�����ۼƴ���
// #define  0x05002A4C // 0 byte   ���1��ʧ������ʱ��(��)TOTAL_LOSS_I_LAST_START
// #define  0x05002A4C // 0 byte   ���1��ʧ������ʱ��(��)TOTAL_LOSS_I_LAST_END
#define EPL_TOTAL_OVER_I_BLOCK_ALL_START 0x05002A4C // 0 byte   ���й����ۼ����ݿ��׵�ַ
// #define  0x05002A4C // 0 byte   �������ۼƴ���(��)TOTAL_OVER_I_COUNT_TOTAL
#define EPL_TOTAL_OVER_AI_COUNT_TOTAL 0x05002A4C // 4 byte NNNNNN BCD A��������ۼƴ���
#define EPL_TOTAL_OVER_BI_COUNT_TOTAL 0x05002A50 // 4 byte NNNNNN BCD B��������ۼƴ���
#define EPL_TOTAL_OVER_CI_COUNT_TOTAL 0x05002A54 // 4 byte NNNNNN BCD C��������ۼƴ���
// #define  0x05002A58 // 0 byte   ���1�ι�������ʱ��(��)TOTAL_OVER_I_LAST_START
// #define  0x05002A58 // 0 byte   ���1�ι�������ʱ��(��)TOTAL_OVER_I_LAST_END
#define EPL_TOTAL_CUT_I_BLOCK_ALL_START 0x05002A58 // 0 byte   ���ж����ۼ����ݿ��׵�ַ
// #define  0x05002A58 // 0 byte   �������ۼƴ���(��)TOTAL_CUT_I_COUNT_TOTAL
#define EPL_TOTAL_CUT_AI_COUNT_TOTAL 0x05002A58 // 4 byte NNNNNN BCD A��������ۼƴ���
#define EPL_TOTAL_CUT_BI_COUNT_TOTAL 0x05002A5C // 4 byte NNNNNN BCD B��������ۼƴ���
#define EPL_TOTAL_CUT_CI_COUNT_TOTAL 0x05002A60 // 4 byte NNNNNN BCD C��������ۼƴ���
// #define  0x05002A64 // 0 byte   ���1�ζ�������ʱ��(��)TOTAL_CUT_I_LAST_START
// #define  0x05002A64 // 0 byte   ���1�ζ�������ʱ��(��)TOTAL_CUT_I_LAST_END
#define EPL_TOTAL_ORDER_VOLTAGE_BLOCK_START 0x05002A64 // 0 byte   ��ѹ�������ۼ����ݿ��׵�ַ
#define EPL_TOTAL_ORDER_VOLTAGE_COUNT_TOTAL 0x05002A64 // 4 byte NNNNNN BCD ��ѹ���������ۼƴ���
#define EPL_TOTAL_ORDER_CURRENT_BLOCK_START 0x05002A68 // 0 byte   �����������ۼ����ݿ��׵�ַ
#define EPL_TOTAL_ORDER_CURRENT_COUNT_TOTAL 0x05002A68 // 4 byte NNNNNN BCD �������������ۼƴ���
#define EPL_TOTAL_UNBALANCE_VOLTAGE_BLOCK_START 0x05002A6C // 0 byte   ��ѹ��ƽ���ۼ����ݿ��׵�ַ
#define EPL_TOTAL_UNBALANCE_VOLTAGE_COUNT_TOTAL 0x05002A6C // 4 byte NNNNNN BCD ��ѹ��ƽ�����ۼƴ���
#define EPL_TOTAL_UNBALANCE_CURRENT_BLOCK_START 0x05002A70 // 0 byte   ������ƽ���ۼ����ݿ��׵�ַ
#define EPL_TOTAL_UNBALANCE_CURRENT_COUNT_TOTAL 0x05002A70 // 4 byte NNNNNN BCD ������ƽ�����ۼƴ���
#define EPL_TOTAL_UNBALANCE_SEVERITY_CURRENT_BLOCK_START 0x05002A74 // 0 byte   �������ز�ƽ���ۼ����ݿ��׵�ַ
#define EPL_TOTAL_UNBALANCE_SEVERITY_CURRENT_COUNT_TOTAL 0x05002A74 // 4 byte NNNNNN BCD �������ز�ƽ�����ۼƴ���
#define EPL_TOTAL_OVERTOTALCOS_BLOCK_START 0x05002A78 // 0 byte   �ܹ������������ۼ����ݿ��׵�ַ
#define EPL_TOTAL_OVERTOTALCOS_COUNT_TOTAL 0x05002A78 // 4 byte NNNNNN BCD �ܹ��������������ۼƴ���
#define EPL_TOTAL_REVERSE_ALL_BLOCK_START 0x05002A7C // 0 byte   �ܹ��ʷ����ۼ����ݿ��׵�ַ
#define EPL_TOTAL_REVERSE_ALL_COUNT_TOTAL 0x05002A7C // 4 byte NNNNNN BCD �ܹ��ʷ������ۼƴ���
#define EPL_TOTAL_REVERSE_A_COUNT_TOTAL 0x05002A80 // 4 byte NNNNNN BCD A�ೱ���������ۼƴ���
#define EPL_TOTAL_REVERSE_B_COUNT_TOTAL 0x05002A84 // 4 byte NNNNNN BCD B�ೱ���������ۼƴ���
#define EPL_TOTAL_REVERSE_C_COUNT_TOTAL 0x05002A88 // 4 byte NNNNNN BCD C�ೱ���������ۼƴ���
#define EPL_TOTAL_POWEROVER_ALL_BLOCK_START 0x05002A8C // 0 byte   �ܹ��ʹ����ۼ����ݿ��׵�ַ
#define EPL_TOTAL_POWEROVER_ALL_COUNT_TOTAL 0x05002A8C // 4 byte NNNNNN BCD �ܹ��ʹ������ۼƴ���
#define EPL_TOTAL_POWEROVER_A_COUNT_TOTAL 0x05002A90 // 4 byte NNNNNN BCD A��������ۼƴ���
#define EPL_TOTAL_POWEROVER_B_COUNT_TOTAL 0x05002A94 // 4 byte NNNNNN BCD B��������ۼƴ���
#define EPL_TOTAL_POWEROVER_C_COUNT_TOTAL 0x05002A98 // 4 byte NNNNNN BCD C��������ۼƴ���
#define EPL_DEMAND_OVER_BLOCK_START 0x05002A9C // 0 byte   �����������ݿ�
#define EPL_DEMAND_OVER_KW_F_COUNT 0x05002A9C // 4 byte XXXXXX BCD �����й����������ܴ���
#define EPL_DEMAND_OVER_KW_R_COUNT 0x05002AA0 // 4 byte XXXXXX BCD �����й����������ܴ���
#define EPL_DEMAND_OVER_KVAR_Q1_COUNT 0x05002AA4 // 4 byte XXXXXX BCD ��1�����޹����������ܴ���
#define EPL_DEMAND_OVER_KVAR_Q2_COUNT 0x05002AA8 // 4 byte XXXXXX BCD ��2�����޹����������ܴ���
#define EPL_DEMAND_OVER_KVAR_Q3_COUNT 0x05002AAC // 4 byte XXXXXX BCD ��3�����޹����������ܴ���
#define EPL_DEMAND_OVER_KVAR_Q4_COUNT 0x05002AB0 // 4 byte XXXXXX BCD ��4�����޹����������ܴ���
#define EPL_DEMAND_OVER_KVAR_C1_COUNT 0x05002AB4 // 4 byte XXXXXX BCD �޹����1���������ܴ���
#define EPL_DEMAND_OVER_KVAR_C2_COUNT 0x05002AB8 // 4 byte XXXXXX BCD �޹����2���������ܴ���
#define EPL_TOTAL_COVER_BLOCK_START 0x05002ABC // 0 byte   ����ǿ����¼����ݿ�
#define EPL_TOTAL_COVER_COUNT 0x05002ABC // 4 byte XXXXXX BCD ������ܴ���
// #define  0x05002AC0 // 0 byte   ��������ۼ�ʱ��TOTAL_COVER_TIME
#define EPL_TOTAL_TERMINAL_BLOCK_START 0x05002AC0 //  byte   ����ť�п����¼����ݿ�
#define EPL_TOTAL_TERMINAL_COUNT 0x05002AC0 // 4 byte XXXXXX BCD ����ť���ܴ���
// #define  0x05002AC4 // 0 byte   ����ť�����ۼ�ʱ��TOTAL_TERMINAL_TIME
#define EPL_TOTAL_PROGRAM_BLOCK_START 0x05002AC4 //  byte   ��̸ǿ����¼����ݿ�
#define EPL_TOTAL_PROGRAM_COUNT 0x05002AC4 // 4 byte XXXXXX BCD ����̸��ܴ���
// #define  0x05002AC8 // 0 byte   ����̸����ۼ�ʱ��TOTAL_PROGRAM_TIME
#define EPL_TOTAL_CLR_KWH_COUNT 0x05002AC8 // 4 byte XXXXXX BCD �ۼƵ���ת�����
#define EPL_TOTAL_CLR_KWHUSE_COUNT 0x05002ACC // 4 byte XXXXXX BCD �ۼ��õ���ת�����
#define EPL_TOTAL_CLR_DEMAND_COUNT 0x05002AD0 // 4 byte XXXXXX BCD �ۼ�����ת�����

#define EPL_TOTAL_CLR_MONITER_COUNT 0x05002AD4 // 4 byte XXXXXX BCD �ۼƵ������ת�����
#define EPL_TOTAL_PROGRAM_DAYTABLE_MODULE_COUNT 0x05002AD8 // 4 byte XXXXXX BCD Զ������ʱ���¼��ܴ���
#define EPL_TOTAL_MONEY_BUY_ALL 0x05002ADC // 5 byte XXXXXXXXXX BCD �ۼƹ�����
#define EPL_TOTAL_MONEY_BUY_COUNT 0x05002AE1 // 2 byte XXXX BCD �ۼƹ����ܴ���
#define EPL_TOTAL_RELAY_OPEN_COUNT 0x05002AE3 // 3 byte XXXXXX BCD ��բ�ܴ���
#define EPL_TOTAL_RELAY_OPEN_TIME 0x05002AE6 // 3 byte XXXXXX BCD ��բ��ʱ��
#define EPL_TOTAL_RELAY_CLOSE_COUNT 0x05002AE9 // 3 byte XXXXXX BCD ��բ�ܴ���
#define EPL_TOTAL_RELAY_CLOSE_TIME 0x05002AEC // 3 byte XXXXXX BCD ��բ��ʱ��
#define EPL_TOTAL_BROADCASTTIME_COUNT 0x05002AEF // 3 byte XXXXXX BCD �㲥Уʱ�ܴ���(�㶫ʹ��)
#define EPL_TOTAL_BROADCASTTIME_TIME 0x05002AF2 // 3 byte XXXXXX BCD �㲥Уʱ��ƫ��ʱ��(���λ��ʾ����λ)(�㶫ʹ��)
// #define  0x05002AF5 // 13 byte   ����
// #define  0x05002B02 // 146 byte   ����
#define EPL_PASSWORD_START 0x05002B94 // 0 byte   ��ǰ������ʼ
#define EPL_PASSWORD_0 0x05002B94 // 4 byte   ��ǰ0������
#define EPL_PASSWORD_1 0x05002B98 // 4 byte   ��ǰ1������
#define EPL_PASSWORD_2 0x05002B9C // 4 byte   ��ǰ2������
#define EPL_PASSWORD_3 0x05002BA0 // 4 byte   ��ǰ3������
#define EPL_PASSWORD_4 0x05002BA4 // 4 byte   ��ǰ4������
#define EPL_PASSWORD_5 0x05002BA8 // 4 byte   ��ǰ5������
#define EPL_PASSWORD_6 0x05002BAC // 4 byte   ��ǰ6������
#define EPL_PASSWORD_7 0x05002BB0 // 4 byte   ��ǰ7������
#define EPL_PASSWORD_8 0x05002BB4 // 4 byte   ��ǰ8������
#define EPL_PASSWORD_9 0x05002BB8 // 4 byte   ��ǰ9������
#define EPL_PASSWORD_ERR_COUNT_START 0x05002BBC // 0 byte   ��ǰ������������ʼ
#define EPL_PASSWORD_ERR_COUNT_0 0x05002BBC // 1 byte   ��0������������
#define EPL_PASSWORD_ERR_COUNT_1 0x05002BBD // 1 byte   ��1������������
#define EPL_PASSWORD_ERR_COUNT_2 0x05002BBE // 1 byte   ��2������������
#define EPL_PASSWORD_ERR_COUNT_3 0x05002BBF // 1 byte   ��3������������
#define EPL_PASSWORD_ERR_COUNT_4 0x05002BC0 // 1 byte   ��4������������
#define EPL_PASSWORD_ERR_COUNT_5 0x05002BC1 // 1 byte   ��5������������
#define EPL_PASSWORD_ERR_COUNT_6 0x05002BC2 // 1 byte   ��6������������
#define EPL_PASSWORD_ERR_COUNT_7 0x05002BC3 // 1 byte   ��7������������
#define EPL_PASSWORD_ERR_COUNT_8 0x05002BC4 // 1 byte   ��8������������
#define EPL_PASSWORD_ERR_COUNT_9 0x05002BC5 // 1 byte   ��9������������
#define EPL_PASSWORD_LOCK_TIME_START 0x05002BC6 // 0 byte   ��ǰ��������ʱ����ʼ
#define EPL_PASSWORD_LOCK_TIME_0 0x05002BC6 // 2 byte   ��ǰ��0����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_1 0x05002BC8 // 2 byte   ��ǰ��1����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_2 0x05002BCA // 2 byte   ��ǰ��2����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_3 0x05002BCC // 2 byte   ��ǰ��3����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_4 0x05002BCE // 2 byte   ��ǰ��4����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_5 0x05002BD0 // 2 byte   ��ǰ��5����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_6 0x05002BD2 // 2 byte   ��ǰ��6����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_7 0x05002BD4 // 2 byte   ��ǰ��7����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_8 0x05002BD6 // 2 byte   ��ǰ��8����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_LOCK_TIME_9 0x05002BD8 // 2 byte   ��ǰ��9����������ʱ��(ʣ��ʱ��)
#define EPL_PASSWORD_ERR_COUNT_SECURITY 0x05002BDA // 1 byte   ��ȫ��֤����������
#define EPL_PASSWORD_LOCK_TIME_SECURITY 0x05002BDB // 2 byte   ��ȫ��֤��������ʱ��(ʣ��ʱ��)
// #define  0x05002BDD //  byte   
#define EPL_LAST_CHANNELS01_BROADCASTTIME 0x05002BDD // 6 byte YYMMDDHHMMSS BCD ͨ��01�ϴι㲥Уʱʱ��
#define EPL_LAST_CHANNELS02_BROADCASTTIME 0x05002BE3 // 6 byte YYMMDDHHMMSS BCD ͨ��02�ϴι㲥Уʱʱ��
#define EPL_LAST_CHANNELS03_BROADCASTTIME 0x05002BE9 // 6 byte YYMMDDHHMMSS BCD ͨ��03�ϴι㲥Уʱʱ��
// #define  0x05002BEF //  byte   
// #define  0x05002BEF //  byte   
#define EPL_HADECHANGE_2SEASONTABLECHANGETIME 0x05002BEF // 5 byte YYMMDDHHMM BCD ���л���2��ʱ�����л�ʱ��
#define EPL_HADECHANGE_2SEASONTABLECHANGENUM 0x05002BF4 // 1 byte XX BCD ���л���2��ʱ����ǰʱ��
#define EPL_HADECHANGE_2DAYTABLECHANGETIME 0x05002BF5 // 5 byte YYMMDDHHMM BCD ���л���2����ʱ�α��л�ʱ��
#define EPL_HADECHANGE_2DAYTABLECHANGENUM 0x05002BFA // 1 byte XX BCD ���л���2����ʱ�ε�ǰ����ʱ�α�
#define EPL_HADECHANGE_STEPPRICE_CHANGETIME 0x05002BFB // 5 byte YYMMDDHHMM BCD ���л������׽��ݱ��л�ʱ��
#define EPL_HADECHANGE_STEPPRICE_CHANGENUM 0x05002C00 // 1 byte XX BCD ���л������׽��ݱ��л��ױ�
#define EPL_HADECHANGE_PERIODPRICE_CHANGETIME 0x05002C01 // 5 byte YYMMDDHHMM BCD ���л������׷��ʵ���л�ʱ��
#define EPL_HADECHANGE_PERIODPRICE_CHANGENUM 0x05002C06 // 1 byte XX BCD ���л������׷��ʵ���л��ױ�
// #define  0x05002C07 //  byte   
#define EPL_HADECHANGE_DAYTABLECHANGE_LASTTIME 0x05002C07 // 5 byte YYMMDDHHMM BCD ���һ����ʱ�α��л�ʱ�����ڡ�
// #define  0x05002C0C //  byte   
#define EPL_RESTOREPOWER_LASTTIME 0x05002C0C // 5 byte YYMMDDHHMM BCD ���һ�γ����յ���ת��ʱ��
#define EPL_RESTOREPOWERUSE_LASTTIME 0x05002C11 // 5 byte YYMMDDHHMM BCD ���һ�γ������õ���ת��ʱ��
#define EPL_RESTOREDEMAND_LASTTIME 0x05002C16 // 5 byte YYMMDDHHMM BCD ���һ�γ���������ת��ʱ��
#define EPL_RESTOREMONITER_LASTTIME 0x05002C1B // 5 byte YYMMDDHHMM BCD ���һ�ε������ת��ʱ��
// #define  0x05002C20 //  byte   
#define EPL_RECORD_LASTTIME_START 0x05002C20 // 0 byte   ���1�θ���ͨ�����ɼ�¼ʱ����ʼ
#define EPL_RECORD_CHANNELS01_LASTTIME 0x05002C20 // 5 byte YYMMDDHHMM BCD ���1��ͨ��1���ɼ�¼ʱ��
#define EPL_RECORD_CHANNELS02_LASTTIME 0x05002C25 // 0 byte YYMMDDHHMM BCD ���1��ͨ��2���ɼ�¼ʱ��
#define EPL_RECORD_CHANNELS03_LASTTIME 0x05002C25 // 0 byte YYMMDDHHMM BCD ���1��ͨ��3���ɼ�¼ʱ��
#define EPL_RECORD_CHANNELS04_LASTTIME 0x05002C25 // 0 byte YYMMDDHHMM BCD ���1��ͨ��4���ɼ�¼ʱ��
#define EPL_RECORD_CHANNELS05_LASTTIME 0x05002C25 // 0 byte YYMMDDHHMM BCD ���1��ͨ��5���ɼ�¼ʱ��
#define EPL_RECORD_CHANNELS06_LASTTIME 0x05002C25 // 0 byte YYMMDDHHMM BCD ���1��ͨ��6���ɼ�¼ʱ��
#define EPL_RECORD_CHANNELS14_LASTTIME 0x05002C25 // 0 byte YYMMDDHHMM BCD ���1��ͨ��14���ɼ�¼ʱ��
#define EPL_RECORD_STATUS_START 0x05002C25 // 0 byte   ����ͨ�����ɼ�¼״̬��ʼ
#define EPL_RECORD_CHANNELS01_STATUS 0x05002C25 // 8 byte XXXXXXXX+XXXXXXXX HEX ͨ��01���ɼ�¼״̬(��ǰָ��+ͨ����¼����)
#define EPL_RECORD_CHANNELS02_STATUS 0x05002C2D // 0 byte XXXXXXXX+XXXXXXXX HEX ͨ��02���ɼ�¼״̬(��ǰָ��+ͨ����¼����)
#define EPL_RECORD_CHANNELS03_STATUS 0x05002C2D // 0 byte XXXXXXXX+XXXXXXXX HEX ͨ��03���ɼ�¼״̬(��ǰָ��+ͨ����¼����)
#define EPL_RECORD_CHANNELS04_STATUS 0x05002C2D // 0 byte XXXXXXXX+XXXXXXXX HEX ͨ��04���ɼ�¼״̬(��ǰָ��+ͨ����¼����)
#define EPL_RECORD_CHANNELS05_STATUS 0x05002C2D // 0 byte XXXXXXXX+XXXXXXXX HEX ͨ��05���ɼ�¼״̬(��ǰָ��+ͨ����¼����)
#define EPL_RECORD_CHANNELS06_STATUS 0x05002C2D // 0 byte XXXXXXXX+XXXXXXXX HEX ͨ��06���ɼ�¼״̬(��ǰָ��+ͨ����¼����)
// #define  0x05002C2D // 7 byte   ����
#define EPL_RECORD_SECTOR_STATUS 0x05002C34 // 256 byte XX HEX ÿ��Sector��¼���ɵ�״̬
#define EPL_RECORD_FLASH2_CHECK 0x05002D34 // 2 byte XXXX HEX flashУ���֣�0xA55A
#define EPL_FREEZE_EVERYTIME_LASTTIME 0x05002D36 // 5 byte YYMMDDHHMM BCD ���1�ζ�ʱ�����¼ʱ��
#define EPL_FREEZE_INSTANT_LASTTIME 0x05002D3B // 5 byte YYMMDDHHMM BCD ���1��˲ʱ�����¼ʱ��
#define EPL_FREEZE_EVERYHOUR_LASTTIME 0x05002D40 // 5 byte YYMMDDHHMM BCD ���1�����㶳���¼ʱ��
#define EPL_FREEZE_EVERYDAY_LASTTIME 0x05002D45 // 5 byte YYMMDDHHMM BCD ���1���ն����¼ʱ��
#define EPL_LAST_MONEY_BUY_TIME 0x05002D4A // 6 byte YYMMDDhhmmss BCD ���1�ι��絥ʱ��
#define EPL_LAST_MONEY_BUY_NO 0x05002D50 // 2 byte XXXX BCD ���1�ι��絥���
#define EPL_PROGRAM_TIME_REMAIN 0x05002D52 // 2 byte XX HEX ���ʱ��ʣ��
#define EPL_PROGRAM_RECORD_STATUS 0x05002D54 // 1 byte XX HEX ����¼���¼״̬(0δ��¼��1�Ѿ���¼��
#define EPL_POWERDOWN_ALLLOSSVOLTAGE_STATUS 0x05002D55 // 1 byte XX HEX ��ǰû�е�ѹ״̬(ȫʧѹ0xAA,����=����)
#define EPL_RELAY_ALARM_TIME_COUNT 0x05002D56 // 2 byte XXXX HEX �̵�������ʣ��ʱ��
// #define  0x05002D58 // 60 byte   ����
// #define  0x05002D94 // 510 byte   ����
#define EPL_EPL_DATA_FREQ_OFFSET 0x05002F92 // 2 byte NNNN BCD ʱ�ӻ�׼(���λΪ����λ)
#define EPL_DATA_PROGRAM_START 0x05002F94 // 256 byte   �ڲ��̶����ò���(��ַ�̶�)
// #define  0x05003094 // 256 byte   �ڲ��̶����ò�������
// #define  0x05003194 //  byte   
#define EPL_DATA_ADREG_START 0x05003194 // 768 byte  HEX ����оƬ��������(��ַ�̶�)
// #define  0x05003494 //  byte   
#define EPL_DATA_COEF_START 0x05003494 // 2048 byte  BCD �ڲ���������
// #define  0x05003C94 //  byte   
// #define  0x05003C94 //  byte   
// #define  0x05003C94 //  byte   
#define EPL_PREPAY_DATA_START 0x05003C94 // 0 byte   Ԥ�������е�ַ��ʼ
#define EPL_RELAY_CONTROL_PARA 0x05003C94 // 0 byte   
#define EPL_LOAD_LIMIT_COUNT 0x05003C94 // 1 byte   �����û��������޴���
#define EPL_LOAD_DELAY_CLOSE 0x05003C95 // 1 byte   ��������բ��ʱʱ��
#define EPL_LOAD_DELAY_OPEN 0x05003C96 // 1 byte   �����ɺ�բ��ʱʱ��
#define EPL_LOAD_LIMIT 0x05003C97 // 4 byte   �û�������
#define EPL_RELAY_OPEN_VALVE 0x05003C9B // 4 byte   �̵�����բ��������
#define EPL_RELAY_OPEN_DELAY_TIME 0x05003C9F // 2 byte   ��բ��ʱʱ�䣨NNNNΪ��բǰ�澯ʱ�䣩
#define EPL_RELAY_CLOSE_DELAY_TIME 0x05003CA1 // 2 byte   ��բ��ʱʱ�䣨NNNNΪ��բͨ��ǰ�澯ʱ�䣩
#define EPL_RELAY_CLOSE_MEMORY_LIMIT 0x05003CA3 // 4 byte   ��բ��������ֵ
#define EPL_PREPAY_RELAY_FLAG 0x05003CA7 // 4 byte   �̵�����־
#define EPL_PREPAY_ALARM12_FLAG 0x05003CAB // 2 byte   ������־
#define EPL_LOAD_STATUS 0x05003CAD // 2 byte   ����״̬��
#define EPL_PREPAY_VARIABLE 0x05003CAF // 0 byte   
#define EPL_PREPAY_ENERGY_SUM_BUY 0x05003CAF // 4 byte   �ۼƹ�����
#define EPL_PREPAY_SUM_BUY_NUMBER 0x05003CB3 // 4 byte   �ۼƹ������
#define EPL_PREPAY_ENERGY_PRESENT_BUY 0x05003CB7 // 4 byte   ���ι�����
#define EPL_PREPAY_ENERGY_CARD_SUB 0x05003CBB // 5 byte   Ҫ�ۿ��ĵ���
#define EPL_PREPAY_ENERGY_READY_SUB 0x05003CC0 // 4 byte   ׼��Ҫ�۵ĵ���
#define EPL_PREPAY_OPERATE_ERROR_NUMBER 0x05003CC4 // 3 byte   �������������
#define EPL_PREPAY_CHANGE_KEY_CARDNO 0x05003CC7 // 8 byte   ��Կ��Ƭ��Ϣ
#define EPL_PREPAY_CHANGE_KEY_CLOCK 0x05003CCF // 5 byte   ������Կʱ��
#define EPL_PREPAY_CARD_RESET_INFORMATION 0x05003CD4 // 0 byte   
#define EPL_PREPAY_CARD_FACTORY 0x05003CD4 // 1 byte  BCD ������ʶ
#define EPL_PREPAY_CARD_INFORMATION 0x05003CD5 // 8 byte  BCD ��Ƭ��λ��Ϣ
#define EPL_PREPAY_VARIABLE_PARA 0x05003CDD // 0 byte   
#define EPL_KAY_PUBLIC_STATE 0x05003CDD // 1 byte   ��Կ״̬
#define EPL_METER_SYSTEM_NO 0x05003CDE // 2 byte   ϵͳ���к�
#define EPL_METER_CARD_NO 0x05003CE0 // 1 byte   �����
#define EPL_METER_USER_ID 0x05003CE1 // 6 byte  BCD �û���
#define EPL_METER_DEVICE_ID 0x05003CE7 // 6 byte   �豸��
#define EPL_METER_MULTIPLE_RATE 0x05003CED // 2 byte   ����
#define EPL_AREACODE 0x05003CEF // 2 byte   �������
#define EPL_PREPAY_RUN_PARA 0x05003CF1 // 0 byte   
#define EPL_PREPAY_ENERGY_ALARM1 0x05003CF1 // 4 byte   ��������1
#define EPL_PREPAY_ENERGY_ALARM2 0x05003CF5 // 4 byte   ��������2
#define EPL_PREPAY_ENERGY_OVEDRAFT 0x05003CF9 // 4 byte   ͸֧�޶����
#define EPL_PREPAY_ENERGY_REGRATE 0x05003CFD // 4 byte   �ڻ��޶����
#define EPL_PREPAY_USER_TYPE 0x05003D01 // 1 byte   �û�����
#define EPL_PREPAY_PARACHANGE_FLAG 0x05003D02 // 1 byte   �������±�־λ
#define EPL_PREPAY_KEY_INFO 0x05003D03 // 0 byte   ��Կ��Ϣ��ʼ
#define EPL_KEY_INFO_KEY_STATUS 0x05003D03 // 1 byte   ��Կ״̬
#define EPL_KEY_INFO_UPDATE_WAY 0x05003D04 // 1 byte   ���·�ʽ
#define EPL_KEY_INFO_KEY_NUM 0x05003D05 // 1 byte   ��Կ����
#define EPL_KEY_INFO_KEY_VERSION 0x05003D06 // 1 byte   ��Կ�汾
#define EPL_PREPAY_KEY_INFO_FAR 0x05003D07 // 0 byte   Զ����Կ��Ϣ��ʼ
#define EPL_KEY_INFO_KEY_STATUS_FAR 0x05003D07 // 1 byte   Զ����Կ״̬
#define EPL_KEY_INFO_UPDATE_WAY_FAR 0x05003D08 // 1 byte   Զ�̸��·�ʽ
#define EPL_KEY_INFO_KEY_NUM_FAR 0x05003D09 // 1 byte   Զ����Կ����
#define EPL_KEY_INFO_KEY_VERSION_FAR 0x05003D0A // 1 byte   Զ����Կ�汾
#define EPL_CERTIFICATION_ACTIVE_TIME 0x05003D0B // 2 byte ���� BCD �����֤ʱЧ��
#define EPL_PARA_SET_CARD_VER 0x05003D0D // 4 byte   �������ÿ��汾��
// #define  0x05003D11 // 0 byte   
#define EPL_FAR_CONTROL_ERR_MESSAGE 0x05003D11 // 0 byte   
#define EPL_MAC_ERR_COUNT 0x05003D11 // 1 byte   MAC���������
#define EPL_ESAM_HANDLE_COUNT 0x05003D12 // 1 byte   ESAM���������
// #define  0x05003D13 // 0 byte   
#define EPL_PREPAY_REMAIN_ENERGY 0x05003D13 // 4 byte  HEX ʣ�����
#define EPL_PREPAY_TICK_ENERGY 0x05003D17 // 4 byte  HEX ��Ƿ����
#define EPL_PREPAY_TROBLE_ENERGY 0x05003D1B // 0 byte  HEX ���ϵ���
// #define  0x05003D1B // 0 byte   
#define EPL_REMAIN_ENERGY_DECIMAL 0x05003D1B // 5 byte   ʣ�������С��
// #define  0x05003D20 // 116 byte   ����
// #define  0x05003D94 //  byte   
#define EPL_LAST_PROGRAM_RECORD_START 0x05003D94 // 0 byte   ��ʷ����¼����ݼ�¼��ʼ
#define EPL_LAST00_PROGRAM_RECORD_START 0x05003D94 // 64 byte   ��ʷ��0�α���¼����ݼ�¼��ʼ(��������50)
#define EPL_LAST01_PROGRAM_RECORD_START 0x05003DD4 // 64 byte   ��ʷ��1�α���¼����ݼ�¼��ʼ
#define EPL_LAST02_PROGRAM_RECORD_START 0x05003E14 // 64 byte   ��ʷ��2�α���¼����ݼ�¼��ʼ
#define EPL_LAST03_PROGRAM_RECORD_START 0x05003E54 // 64 byte   ��ʷ��3�α���¼����ݼ�¼��ʼ
#define EPL_LAST04_PROGRAM_RECORD_START 0x05003E94 // 64 byte   ��ʷ��4�α���¼����ݼ�¼��ʼ
#define EPL_LAST05_PROGRAM_RECORD_START 0x05003ED4 // 64 byte   ��ʷ��5�α���¼����ݼ�¼��ʼ
#define EPL_LAST06_PROGRAM_RECORD_START 0x05003F14 // 64 byte   ��ʷ��6�α���¼����ݼ�¼��ʼ
#define EPL_LAST07_PROGRAM_RECORD_START 0x05003F54 // 64 byte   ��ʷ��7�α���¼����ݼ�¼��ʼ
#define EPL_LAST08_PROGRAM_RECORD_START 0x05003F94 // 64 byte   ��ʷ��8�α���¼����ݼ�¼��ʼ
#define EPL_LAST09_PROGRAM_RECORD_START 0x05003FD4 // 64 byte   ��ʷ��9�α���¼����ݼ�¼��ʼ
// #define  0x05004014 // 0 byte   ��ʷ����¼�����
#define EPL_LAST_COVER_OPEN_RECORD_START 0x05004014 // 0 byte  BCD ��ʷ��ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST00_COVER_OPEN_RECORD_START 0x05004014 // 72 byte  BCD ��ʷ��0�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST01_COVER_OPEN_RECORD_START 0x0500405C // 72 byte  BCD ��ʷ��1�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST02_COVER_OPEN_RECORD_START 0x050040A4 // 72 byte  BCD ��ʷ��2�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST03_COVER_OPEN_RECORD_START 0x050040EC // 72 byte  BCD ��ʷ��3�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST04_COVER_OPEN_RECORD_START 0x05004134 // 72 byte  BCD ��ʷ��4�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST05_COVER_OPEN_RECORD_START 0x0500417C // 72 byte  BCD ��ʷ��5�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST06_COVER_OPEN_RECORD_START 0x050041C4 // 72 byte  BCD ��ʷ��6�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST07_COVER_OPEN_RECORD_START 0x0500420C // 72 byte  BCD ��ʷ��7�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST08_COVER_OPEN_RECORD_START 0x05004254 // 72 byte  BCD ��ʷ��8�α�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST09_COVER_OPEN_RECORD_START 0x0500429C // 72 byte  BCD ��ʷ��9�α�ǿ����¼����ݼ�¼��ʼ
// #define  0x050042E4 // 48 byte   ��ʷ��ǿ����¼�����
#define EPL_LAST_TERMINAL_OPEN_RECORD_START 0x05004314 // 0 byte  0 ��ʷ��ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST00_TERMINAL_OPEN_RECORD_START 0x05004314 // 72 byte  BCD ��ʷ��0�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST01_TERMINAL_OPEN_RECORD_START 0x0500435C // 72 byte  BCD ��ʷ��1�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST02_TERMINAL_OPEN_RECORD_START 0x050043A4 // 72 byte  BCD ��ʷ��2�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST03_TERMINAL_OPEN_RECORD_START 0x050043EC // 72 byte  BCD ��ʷ��3�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST04_TERMINAL_OPEN_RECORD_START 0x05004434 // 72 byte  BCD ��ʷ��4�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST05_TERMINAL_OPEN_RECORD_START 0x0500447C // 72 byte  BCD ��ʷ��5�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST06_TERMINAL_OPEN_RECORD_START 0x050044C4 // 72 byte  BCD ��ʷ��6�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST07_TERMINAL_OPEN_RECORD_START 0x0500450C // 72 byte  BCD ��ʷ��7�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST08_TERMINAL_OPEN_RECORD_START 0x05004554 // 72 byte  BCD ��ʷ��8�ζ�ť�ǿ����¼����ݼ�¼��ʼ
#define EPL_LAST09_TERMINAL_OPEN_RECORD_START 0x0500459C // 72 byte  BCD ��ʷ��9�ζ�ť�ǿ����¼����ݼ�¼��ʼ
// #define  0x050045E4 // 48 byte   ��ʷ��ť�ǿ����¼�����
#define EPL_LAST_ACPOWER_LOSS_RECORD_START 0x05004614 // 0 byte  0 ��ʷ������Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST00_ACPOWER_LOSS_RECORD_START 0x05004614 // 16 byte  BCD ��ʷ��0�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST01_ACPOWER_LOSS_RECORD_START 0x05004624 // 16 byte  BCD ��ʷ��1�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST02_ACPOWER_LOSS_RECORD_START 0x05004634 // 16 byte  BCD ��ʷ��2�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST03_ACPOWER_LOSS_RECORD_START 0x05004644 // 16 byte  BCD ��ʷ��3�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST04_ACPOWER_LOSS_RECORD_START 0x05004654 // 16 byte  BCD ��ʷ��4�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST05_ACPOWER_LOSS_RECORD_START 0x05004664 // 16 byte  BCD ��ʷ��5�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST06_ACPOWER_LOSS_RECORD_START 0x05004674 // 16 byte  BCD ��ʷ��6�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST07_ACPOWER_LOSS_RECORD_START 0x05004684 // 16 byte  BCD ��ʷ��7�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST08_ACPOWER_LOSS_RECORD_START 0x05004694 // 16 byte  BCD ��ʷ��8�θ�����Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST09_ACPOWER_LOSS_RECORD_START 0x050046A4 // 16 byte  BCD ��ʷ��9�θ�����Դ�����¼����ݼ�¼��ʼ
// #define  0x050046B4 // 32 byte   ��ʷ������Դ�����¼�����
#define EPL_LAST_LOSS_ALL_VOLTAGE_RECORD_START 0x050046D4 // 0 byte  0 ��ʷȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST00_LOSS_ALL_VOLTAGE_RECORD_START 0x050046D4 // 16 byte  BCD ��ʷ��0��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST01_LOSS_ALL_VOLTAGE_RECORD_START 0x050046E4 // 16 byte  BCD ��ʷ��1��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST02_LOSS_ALL_VOLTAGE_RECORD_START 0x050046F4 // 16 byte  BCD ��ʷ��2��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST03_LOSS_ALL_VOLTAGE_RECORD_START 0x05004704 // 16 byte  BCD ��ʷ��3��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST04_LOSS_ALL_VOLTAGE_RECORD_START 0x05004714 // 16 byte  BCD ��ʷ��4��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST05_LOSS_ALL_VOLTAGE_RECORD_START 0x05004724 // 16 byte  BCD ��ʷ��5��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST06_LOSS_ALL_VOLTAGE_RECORD_START 0x05004734 // 16 byte  BCD ��ʷ��6��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST07_LOSS_ALL_VOLTAGE_RECORD_START 0x05004744 // 16 byte  BCD ��ʷ��7��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST08_LOSS_ALL_VOLTAGE_RECORD_START 0x05004754 // 16 byte  BCD ��ʷ��8��ȫʧѹ�¼����ݼ�¼��ʼ
#define EPL_LAST09_LOSS_ALL_VOLTAGE_RECORD_START 0x05004764 // 16 byte  BCD ��ʷ��9��ȫʧѹ�¼����ݼ�¼��ʼ
// #define  0x05004774 // 32 byte   ��ʷȫʧѹ�¼�����
#define EPL_LAST_POWER_DOWN_RECORD_START 0x05004794 // 0 byte  0 ��ʷϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST00_POWER_DOWN_RECORD_START 0x05004794 // 16 byte  BCD ��ʷ��0��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST01_POWER_DOWN_RECORD_START 0x050047A4 // 16 byte  BCD ��ʷ��1��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST02_POWER_DOWN_RECORD_START 0x050047B4 // 16 byte  BCD ��ʷ��2��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST03_POWER_DOWN_RECORD_START 0x050047C4 // 16 byte  BCD ��ʷ��3��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST04_POWER_DOWN_RECORD_START 0x050047D4 // 16 byte  BCD ��ʷ��4��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST05_POWER_DOWN_RECORD_START 0x050047E4 // 16 byte  BCD ��ʷ��5��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST06_POWER_DOWN_RECORD_START 0x050047F4 // 16 byte  BCD ��ʷ��6��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST07_POWER_DOWN_RECORD_START 0x05004804 // 16 byte  BCD ��ʷ��7��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST08_POWER_DOWN_RECORD_START 0x05004814 // 16 byte  BCD ��ʷ��8��ϵͳ��Դ�����¼����ݼ�¼��ʼ
#define EPL_LAST09_POWER_DOWN_RECORD_START 0x05004824 // 16 byte  BCD ��ʷ��9��ϵͳ��Դ�����¼����ݼ�¼��ʼ
// #define  0x05004834 // 32 byte   ��ʷϵͳ��Դ�����¼�����
// #define  0x05004854 // 88 byte   ����
#define EPL_POWEROFF_SAVEDATA_ADDR 0x050048AC // 512 byte   ���籣����������
// #define  0x05004AAC // 256 byte   ���籣������������
#define EPL_BKP_VIRTURL_BAK_ADDR 0x05004BAC // 256 byte   ԭST BKP���ݱ���
#define EPL_MAX_SIZE_STACK 0x05004CAC // 2 byte   ������
#define EPL_FACTORY_INIT_INDICATE 0x05007FFF // 16 byte   


