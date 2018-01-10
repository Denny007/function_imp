/******************************************************************
  File Name   : function_imp.c
  Description : 标准库函数的部分实现
  Date        : 2018-1-4
  Author      : Denny
 *******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief 实现标准库的atoi函数
 * @param const char *str 
 *      数字字符串
 * @return 
 *      对应的int型数字
 */
int atoi_m(const char *str)
{
    int value = 0;
    int flag = 1; /* 判断符号，1为正 */
    /* 跳过前面的空格 */
    while(*str == ' ')
    {   
        str++;
    }
    /* 如果字符串最前面时负号 */
    if(*str == '-')
    {
        flag = 0;
        str++;
    }
    else if(*str == '+')
    {
        flag = 1;
        str++;
    }
   
    /* 字符不为空字符， */
    while((*str != '\0') && (*str <= '9') && (*str >= '0'))
    {
        value = value * 10 + *str - '0';  /* 最高位每次进一位，并且最低位使用ASCII去减 */
        str++;
    }
    if(flag == 0)
    {
        value = -value;
    }
    return value;
}

/* 
 * @brief 标准库strcpy函数实现
 * @param char *dest
 *      复制的目标字符串指针
 * @param const char *src
 *      被复制的字符串指针
 * @return
 *      复制的目标字符串指针
 */
char *strcpy_m(char *dest, const char *src)
{
    assert(dest != NULL && src != NULL );
    char *temp = dest;
    /* 末尾的'\0'也要复制过来
     * 上面先执行 *temp++ = *src++ ，再判断 *src 是否等于'\0'
     * 所以保证了'\0'先复制后判断
     */
    while((*temp++ = *src++) != '\0');

    return dest;
}

/**
 @brief 标准库strncpy函数实现
 * @param char *dest
 *      复制的目标字符串指针
 * @param const char *src
 *      被复制的字符串指针
 * @return
 *      复制的目标字符串指针
**/
char *strncpy_m(char *dest, const char *src, int n)
{
    assert(dest != NULL && src != NULL );
    char *temp = dest;

    /* 两种终止情况：
     * 1. n = 0，此时下面的语句也不执行，如果未达到src末尾
     * 不会自动在dest末尾添加'\0'的，所以需要使用者自己添加
     * 2. n > 0 但是src已经到达末尾，那么执行下面语句，将
     * dest填充'\0'达到长度n（ANSI C规定）*/
    while(n-- > 0 && (*temp++ = *src++) != '\0');

    /* 当n > 0 但是src已经到达末尾，那么执行下面语句，将
     * dest填充'\0'达到长度n（ANSI C规定） */
    while (n-- > 0) 
    {
        *temp++ = '\0';
    }

    return dest;

}

/*
 * @breif 比较字符串
 * @param const char *str1
 *      字符串1
 * @param const char *str2
 *      字符串2
 * @return
 * 
**/
int strcmp_m(const char *str1, const char *str2)
{
    assert(NULL != str1 && NULL != str2);
    while(*str1 && *str2 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}


/*
 * @breif 标准库内存拷贝函数memcpy的实现 
 *      从源src所指的内存地址的起始位置开始
 *      拷贝n个字节到目标dest所指的内存地址的起始位置中
 * @param void *dst
 *      目标dest所指的内存地址的起始位置
 * @param void *src
 *      源src所指的内存地址的起始位置
 * @param size_t count
 *      拷贝的字节数目
 * @return 
 *       目标dest所指的内存地址的起始位置
**/
void memcpy_m(void *dst, void *src, size_t count)
{
    assert(NULL != dst && NULL != src);
    char *pdst = (char *)dst;
    char *psrc = (char *)src;
    

    while(count-- > 0)
    {
        *pdst++ = *psrc++; 
    }

    return dst;
}

/* 
 * @breif 标准库内存拷贝函数memcpy的实现 
 *      从源src所指的内存地址的起始位置开始
 *      拷贝n个字节到目标dest所指的内存地址的起始位置中
 *      能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中
 * @param void *dst
 *      目标dest所指的内存地址的起始位置
 * @param void *src
 *      源src所指的内存地址的起始位置
 * @param size_t count
 *      拷贝的字节数目
 * @return 
 *       目标dest所指的内存地址的起始位置
 */
void* memmove_m(void* dst, const void* src, size_t count)
{
    assert(dst != NULL && src != NULL);
    char* pbTo = (char*)dst;
    char* pbFrom = (char*)src;

    if (dst <= src || pbTo >= pbFrom + count) /* 没有overlap的情况，直接拷贝 */
    {
        while (count-- > 0)
        {
            *pbTo++ = *pbFrom++;
        }
    }
    else
    {
        pbTo = pbTo + count -1; /* overlap的情况，从高位地址向低位拷贝 */
        pbFrom = pbFrom + count -1;
        while (count-- > 0)
        {
            *pbTo-- = *pbFrom--;
        }
    }
    return dst;
}



int main(int argc, char *argv[])
{
    char *p = "1234";
    char *m = "123a";
    char *a;
    int n;
    printf("the num=%d\n", atoi_m(p));
    
    a = (char *)malloc(5 * sizeof(char));
   // strcpy_m(a, p);
   // printf("the string is %s\n", a);

    //strncpy_m(a, p, 4);
    //printf("the string is %s\n", a);

    n = strcmp_m(p, m);
    printf("the result is %d\n", n);
    
    memmove_m(a, p, 4);
    printf("the string is %s\n", a);

    if(a != NULL)
    {
        free(a);
        a = NULL;
    }
    return 0;
}
