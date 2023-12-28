#include"./head.h"
char result[32] = { 0 };//�洢ת����Ľ�����ɸ�����Ҫת���������ʵ�����/�������鳤��
const char* cNum[] = { "��", "һ", "��", "��", "��", "��", "��", "��", "��", "��" };
const char* unit[] = { "","ʮ","��","ǧ" };
const char* bigUnit[] = { "","��","��"};//��������Ӹ���ĵ�λ�����ڵ�λ�Ľ���Ϊ1000���������˵�λ����ע��result����ĳ�����֮��ƥ��
const int maxLength = 4 * sizeof(bigUnit) / sizeof(bigUnit[0]);
int flag = 0;
//��������ַ����ĺϷ��ԣ����붼�ɰ�����������������λ��Ϊ0��֧��12λ������������
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
//��λ��������ת��������
static void convert(char part[5], char* result)
{
    if (!strcmp(part, "0000"))
    {
        flag++;
        return;
    }
    //num[0]ǧλ  num[1]��λ  num[2]ʮλ  num[3]��λ
    int num[4] = { 0 };
    int partLength = (int)strlen(part);
    //���ܲ���4λ����λ��0
    for (int i = 0; i < partLength; i++)
    {
        num[3 - i] = part[partLength - 1 - i] - 48;
    }
    int start = 0;
    if (partLength < 4)
    {
        //����4λ����λ��0����
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
/// ����������ת�������֣�֧��12λ�����ڵ�������
/// </summary>
/// <param name="num">����һ���ַ������͵İ���������</param>
/// <returns>����ɾ�̬���鱣�棬����char*</returns>
char* arabic2Chinese(char* num)
{
    memset(result, 0, sizeof(result));//�����һ�ε�����

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