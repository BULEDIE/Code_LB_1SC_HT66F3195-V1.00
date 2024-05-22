#include "Main.h"

void F_Buz1KHzCntBiBi()
{
    if(B_BuzAlramEn||B_BuzKeyAlramEn)
    {   R_Buz10HzCnt++;
        if(R_Buz10HzCnt >= D_BUZ10HZ)
        {   R_Buz10HzCnt = 0;
            R_BuzCycleCnt++;
            // if((R_BuzCycleCnt == 1)||(R_BuzCycleCnt == 3)||(R_BuzCycleCnt == 5)||
            //    ((R_BuzCycleCnt >= 7)&&(R_BuzCycleCnt <= 10)))
            // {
            //     F_BUZON();
            // }else{
            //     F_BUZOFF();
            // }
        }
        if(R_BuzCycleCnt >= 14)
        {   R_BuzCycleCnt = 0;
            F_BUZOFF();
            B_BuzKeyAlramEn = 0;
        }
    }
}

u8 F_KeyBreakFault()
{
    if(B_BuzAlramEn){
        B_BuzKeyBreak = 1;
        B_BuzAlramEn = 0;/* 失能、与IO关闭、要有先后顺序 */
        B_BuzKeyAlramEn = 0;
        F_BUZOFF();          /* 关闭蜂鸣器 */
        R_Buz10HzCnt = 0;
        R_BuzCycleCnt = 0;
        Key.Value = 0;/* 打断蜂鸣器其它键值不响应 */
        return 1;
    }
    return 0;
}
