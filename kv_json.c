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

int kv_json_decode_poller(char *buf, uint32_t len, int (*callback)(uint16_t index, char *key, uint16_t key_len, char *value, uint16_t value_len))
{
	if (callback == NULL)	return -1;
	if (buf == NULL || len == 0) return -2;
	
	len = kv_json_format(buf, len);
	
	char *start = buf;
	char *end = buf+len;
	
	uint16_t index = 0;
	
  char *k_start = NULL, *k_end = NULL, *v_end = NULL;
	
	for(char *p = start; p!=end; p++){
		//查找 key 开始
		if(k_start == NULL){
			if(*p == '\"'){
				for(char *tmp = p+1; tmp!=end; tmp++){
					if(tmp + 2 < end && *tmp == '\"'){
						if(*(tmp + 2) == '{'){
							p = tmp + 2;
							break;//排除结构对象
						}else{
							k_start = p + 1;
						}
					}
				}
			}
			continue;
		}
		
		//查找 key 结束
		if(k_end == NULL){
			if(p + 1 < end && *p == '\"' && *(p + 1) == ':'){
				k_end = p;
			}
			continue;
		}
		
		//查找 value 结束
		if(v_end == NULL){
			if(p + 1 < end && (*p == ']' || *p == ',' || *p == '}')){
				if(*(p+1) == ']' || *(p+1) == ',' || *(p+1) == '}' 
					|| *(p+1) == '\"' || *(p+1) == '{'){
					v_end = p;
				}
			}else{
				continue;
			}
		}
		
		int err = callback(index, k_start, k_end-k_start, k_end+2, v_end-(k_end+2));
		if(err) return -3;
		
		k_start = NULL;
		k_end = NULL;
		v_end = NULL;
		index++;
	}

	return 0;
}


/* kv_json.c file end */

