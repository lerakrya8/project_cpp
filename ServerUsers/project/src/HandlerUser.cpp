//
// Created by lerakry on 04.12.2020.
//

#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../includes/HandlerUser.h"

using std::string;
using boost::property_tree::ptree;

std::map<string, string> HandlerUser::parser_json(std::stringstream& request) {
    ptree pt;
    if (!request.str().empty()) {
        boost::property_tree::read_json(request, pt);
        std::map<string, string> result;
        ptree::const_iterator end = pt.end();
        char alf = 'A';
        for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
            result[alf + std::string(it->first)] = it->second.get_value<string>();
            alf++;
        }
        return result;
    }
    return {};
}
void HandlerUser::handle_request(string& request) {

	std::cout << "handler" << std::endl;
    std::stringstream stream_request(request);
    int number_request, priority;
    string method;
    stream_request >> number_request;
    stream_request >> priority;
    stream_request >> method;
    std::map<string, string> parse_request = parser_json(stream_request);
    string str;
    if (method == "create") {
        create_user(parse_request, number_request);
    }
    else if (method == "data") {
        auto id = std::atoi(parse_request["Aid"].c_str());
        data_user(id, number_request);
    }
    else if (method == "all") {
        all_users(number_request);
    }
    else if (method == "delete") {
        int id = std::atoi(parse_request["Aid"].c_str());
        std::cout << parse_request["Aid"]<< std::endl;
        delete_user(id, number_request);
    }
    else if (method == "change") {
        change_user_data(parse_request, number_request);
    }
}

void HandlerUser::create_user(std::map<string, string>& data_user, int number_request) {
    int result = data_base_.insert_user(data_user);
    string str_result = std::to_string(number_request);
    if (result == 200) {
        str_result += "{\n \"response\": \"success create user\"\n}";
    }
    else {
        str_result += "{\n \"response\": \"fail create user\"\n}";
    }
    session_.send_answer(str_result);
}

void HandlerUser::data_user(int id, int number_request) {
    data_base_.data_user(id);
    string result = std::to_string(number_request) + "\n";
    string new_result = data_base_.data_user(id);
    if(result == "No user") {
        result += "{\n \"response\": \"fail data user\"\n}";
    } else {
        result += new_result;
    }
    session_.send_answer(result);
}

void HandlerUser::all_users(int number_request) {
    data_base_.all_users();
    string result = std::to_string(number_request) + "\n";
    string new_result = data_base_.all_users();
    if(result == "No users") {
        result += "{\n \"response\": \"fail all users\"\n}";
    } else {
        result += new_result;
    }
    session_.send_answer(result);
}

void HandlerUser::delete_user(int id, int number_request) {
    int result = data_base_.delete_user(id);
    string str_result = std::to_string(number_request);
    if (result == 200) {
        str_result += "{\n \"response\": \"success delete user\"\n}";
    }
    else {
        str_result += "{\n \"response\": \"fail delete user\"\n}";
    }
    session_.send_answer(str_result);
}


void HandlerUser::change_user_data(std::map<string, string>& user_data, int number_request) {
    int result = data_base_.update_data(user_data);
    string str_result = std::to_string(number_request);
    if (result == 200) {
        str_result += "{\n \"response\": \"success update user\"\n}";
    }
    else {
        str_result += "{\n \"response\": \"fail update user\"\n}";
    }
    session_.send_answer(str_result);
}


