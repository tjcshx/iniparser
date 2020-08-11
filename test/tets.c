/*********************************************************************************
 *      Copyright:  (C) 2020 ysn
 *                  All rights reserved.
 *
 *       Filename:  tets.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(11/08/20)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "11/08/20 07:38:08"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "iniparser.h"
#include "dictionary.h"
#define  INI_PATH "init_param.conf"
int iniparser_save(dictionary * d, const char *inipath);
int main(void)
{
    dictionary *ini;

    ini = iniparser_load(INI_PATH);//parser the file

    printf("%s:\n",iniparser_getsecname(ini,0));//get section name
    int n = iniparser_getint(ini,"comport:nSpeed",-1);
    printf("speed : %d\n",n);

    const char *str = iniparser_getstring(ini,"comport:device_name","null");
    printf("device_name : %s\n",str);

    printf("\n%s:\n",iniparser_getsecname(ini,1));
    const char *ip = iniparser_getstring(ini,"ppp:ping_ipaddr","null");
    printf("ping_ipaddr : %s\n",ip);


    printf("\n%s:\n",iniparser_getsecname(ini,2));
    iniparser_set(ini, "mosquitto:keepalive", "60");

    iniparser_save(ini, INI_PATH);
    iniparser_freedict(ini);//free dirctionary object

    return 0;
}
int iniparser_save(dictionary * d, const char *inipath)
{
    int ret = 0;
    FILE *fp = NULL;

    if (inipath == NULL || d == NULL) {
        ret = -1;
        printf("saveConfig error:%d from (filepath == NULL || head == NULL)\n",ret);
        return ret;
    }

    fp = fopen(inipath,"w");
    if (fp == NULL) {
        ret = -2;
        printf("saveConfig:open file error:%d from %s\n",ret,inipath);
        return ret;
    }

    iniparser_dump_ini(d,fp);

    fclose(fp);

    return 0;
}

