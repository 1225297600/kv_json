/********************************************************************************
* @name: kv_json.c
* @author: zhangzhilin
* @description: 1225297600@qq.com
* @version: 1.0
* @date: 2025-4-29
* @brief: The function of JSON decode and encode
********************************************************************************/
#include <stdio.h>
#include <string.h>

#include "kv_json.h"
#include "algo.h"

static char *find_value_end(char *start, char *end);
static int find_key(char *start, char *end, char **key_start, char **key_end);

/**
 * @brief 格式化 JSON 字符串，保留可打印字符（不包括空格）
 * @param buf 输入的 JSON 字符串缓冲区
 * @param len 缓冲区的长度
 * @return 处理后字符串的长度
 */
uint32_t kv_json_format(char *buf, uint32_t len) {
	char *src = buf, *dst = buf;
	char *end = buf + len;
	
	while (src < end && *src != '\0') {
		char c = *src++;
		// 保留可打印字符（不包括空格）
		if (c > ' ' && c <= '~') {
			*dst++ = c;
		}
	}
	*dst = '\0';
	
	return (uint32_t)(dst - buf);
}


/**
 * @brief 解析 JSON 字符串，并调用回调函数处理每个键值对
 * @param buf 输入的 JSON 字符串缓冲区
 * @param len 缓冲区的长度
 * @param callback 处理键值对的回调函数
 * @note 函数会调用kv_json_format，会改变原本buf字符串的内容
 */
int kv_json_decode_poller(char *buf, uint32_t len, int (*callback)(uint16_t index, char *key, uint16_t key_len, char *value, uint16_t value_len))
{
	if (callback == NULL)	return -1;
	if (buf == NULL || len == 0) return -2;
	
	len = kv_json_format(buf, len);
	
	char *start = buf;
	char *end = buf+len;
	char *tmp = NULL;
	
	uint16_t index = 0;
	
  	char *k_start, *k_end, *v_end;
	
	for(;;)
	{
		//查找 key 开始
		if( find_key(start, end, &k_start, &k_end) != 0 )
		{
			return -1;
		}
		
		v_end = find_value_end(k_end+2, end);
		if(v_end == NULL)
		{
			return -2;
		}
		
		int err = callback(index, k_start+1, k_end-k_start-1, k_end+2, v_end-(k_end+2));
		if(err) return -3;
		
		index++;
		start = v_end+1;
	}
	return 0;
}

static int find_key(char *start, char *end, char **key_start, char **key_end)
{
	*key_start = NULL;
	*key_end = NULL;
	for(; start<end; start++){
		if(*key_start == NULL)
		{
			//找头
			if(*start == '\"'){
				*key_start = start;//找到头
			}
		}else{
			//找尾
			if((start+2)<end && *start == '\"' && *(start+1) == ':')
			{
				if(*(start+2) == '{')
				{
					//排除结构体对象
					start+=2;
					*key_start = NULL;
				}else{
					*key_end = start;
					return 0;//找到尾
				}
			}
		}
	}
	return -1;
}

static char *find_value_end(char *start, char *end)
{
	for(; start<end; start++){
		if(*start == ',' || *start == '}'){
			return start;
		}
	}
	return NULL;
}


/* kv_json.c file end */

