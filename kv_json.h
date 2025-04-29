/********************************************************************************
* @name: kv_json.h
* @author: zhangzhilin
* @description: 1225297600@qq.com
* @version: 1.0
* @date:  2025-4-29
* @brief: The function of JSON decode and encode
********************************************************************************/
#ifndef __KV_JSON_H
#define __KV_JSON_H
#include <stdint.h>
#include <stdbool.h>

uint32_t json_format(char *buf, uint32_t len);


// will do 'kv_json_format', make 'buf' change
int kv_json_decode_poller(char *buf, uint32_t len, int (*callback)(uint16_t index, char *key, uint16_t key_len, char *value, uint16_t value_len));


#endif

/* kv_json.h file end */
