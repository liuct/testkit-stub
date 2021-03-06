#include <string>
#include <json/json.h>
#include <stdlib.h>

#include "testcase.h"

using namespace std;

TestCase::TestCase() {
	result = "N/A";

	std_out = "";

	is_executed = false;
}

TestCase::~TestCase() {
}

void TestCase::init(const Json::Value value) {
	m_case = value;
	purpose = value["purpose"].asString(); // server will use this string directly
	case_id = value["case_id"].asString();
	if (value["timeout"].isString())
		timeout_value = atoi(value["timeout"].asString().c_str());
	else timeout_value = 90;
}

Json::Value TestCase::to_json() {
	return m_case;
}

Json::Value TestCase::result_to_json() {
	Json::Value root;

	root["order"] = m_case["order"];
	root["case_id"] = m_case["case_id"];
	root["result"] = result;

	if (std_out != "") {
		root["stdout"] = std_out;
		root["start_at"] = start_at;
		root["end_at"] = end_at;
	}

	return root;
}

void TestCase::set_result(Json::Value paras) {
	is_executed = true;

	result = paras["result"].asString();

	std_out = paras["msg"].asString();

	getCurrentTime();
	end_at = m_str_time;
}

void TestCase::set_start_at() {
	getCurrentTime();
	start_at = m_str_time;
}

void TestCase::getCurrentTime() {
	memset(m_str_time, 0, 32);
	time_t timer;
	struct tm* t_tm;
	time(&timer);
	t_tm = localtime(&timer);
	sprintf(m_str_time, "%4d-%02d-%02d %02d:%02d:%02d", t_tm->tm_year + 1900,
			t_tm->tm_mon + 1, t_tm->tm_mday, t_tm->tm_hour, t_tm->tm_min,
			t_tm->tm_sec);
}