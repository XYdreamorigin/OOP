#pragma once
#include"class.h"
#include<vector>

//在main里面定义
extern vector<player> all_player; //所有闯关者
extern vector<test_maker> all_test_maker;//所有出题者
extern vector<player>::iterator cur_player;//当前的闯关者
extern vector<test_maker>::iterator cur_test_maker; //当前出题者
extern vector<string> all_words; //单词题库
