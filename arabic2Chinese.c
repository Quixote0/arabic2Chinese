#include"./head.h"
char result[32] = { 0 };//存储转换后的结果，可根据需要转换的数字适当增加/减少数组长度
const char* cNum[] = { "零", "一", "二", "三", "四", "五", "六", "七", "八", "九" };
const char* unit[] = { "","十","百","千" };
const char* bigUnit[] = { "","万","亿"};//可往后添加更大的单位，相邻单位的进制为1000。若增加了单位，请注意result数组的长度与之相匹配
const int maxLength = 4 * sizeof(bigUnit) / sizeof(bigUnit[0]);
int flag = 0;
//检查输入字符串的合法性，必须都由阿拉伯数字组成且最高位不为0，支持12位及以内正整数
static int check(char* num)
{
    if (strlen(num) > maxLength || strlen == 0) return 1;
    if ('0' == *num) return 1;
    char* pnum = num;
    while (*pnum)
    {
        if (*pnum < '0' && *pnum>'9') return 1;
        else pnum++;
    }
    return 0;
}
//四位数及以下转中文数字
static void convert(char part[5], char* result)
{
    if (!strcmp(part, "0000"))
    {
        flag++;
        return;
    }
    //num[0]千位  num[1]百位  num[2]十位  num[3]个位
    int num[4] = { 0 };
    int partLength = (int)strlen(part);
    //可能不足4位，高位补0
    for (int i = 0; i < partLength; i++)
    {
        num[3 - i] = part[partLength - 1 - i] - 48;
    }
    int start = 0;
    if (partLength < 4)
    {
        //不足4位，高位的0不读
        start = 4 - partLength;
    }
    for (int i = start; i < 4; i++)
    {
		if (!num[i])
        {
            flag++;
            continue;
		}
        if (flag)
        {
            strcat(result, cNum[0]);
            flag = 0;
        }
        if (!(partLength == 2 && i == 2 && num[i] == 1)) strcat(result, cNum[num[i]]);
        if (num[i]) strcat(result, unit[3 - i]);
    }
    flag = 0;
}
/// <summary>
/// 阿拉伯数字转中文数字，支持12位及以内的正整数
/// </summary>
/// <param name="num">传入一个字符串类型的阿拉伯数字</param>
/// <returns>结果由静态数组保存，返回char*</returns>
char* arabic2Chinese(char* num)
{
    memset(result, 0, sizeof(result));//清除上一次的数据

    if (check(num)) return NULL;

    int numLength = (int)strlen(num);

    int extra = numLength % 4;
    int col = numLength / 4 + !!extra;
    char* pnum = num;
    char part[5] = { 0 };
    strncpy(part, pnum, !extra ? 4 : extra);
    convert(part, result);
    strcat(result, bigUnit[col - 1]);
    memset(part, 0, sizeof(part));
    pnum += !extra ? 4 : extra;
    for (int i = 1; i < col; i++)
    {
        strncpy(part, pnum, 4);
        convert(part, result);
        if (strcmp(part, "0000")) strcat(result, bigUnit[col - 1 - i]);
        memset(part, 0, sizeof(part));
        pnum += 4;
    }
    flag = 0;
    return result;
}