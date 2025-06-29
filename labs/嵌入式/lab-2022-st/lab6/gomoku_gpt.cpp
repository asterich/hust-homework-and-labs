/*
 * This program demonstrates how to programatically interact with OpenAI GPT
 * using C++. The program uses the curl library for making HTTP requests, and
 * the nlohmann json library for handling JSON data.
 */
#include <iostream>
#include <string.h>
#include <string>

#include "curl/curl.h"
#include "nlohmann/json.hpp"

#include "gomoku_gpt.h"

using nlohmann::json;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

// Function prototypes
size_t WriteCallback(void *, size_t, size_t, string *);
string getCompletion(const string &, const string &model = "gpt-3.5-turbo");

int get_comment_by_board(const int board[BOARD_SIZE][BOARD_SIZE],
                         const int player, char *comment) {
  string prompt =
      "你是我最可爱的妹妹，请您记住你妹妹的身份，用妹妹的语气，根据哥哥我给出的"
      "五子"
      "棋棋局，评价一下刚刚落子的一方下得怎么样。棋局信息包括当前棋盘信息和刚刚"
      "落子的一方。你的评价应当限制在20个字内，并且不用太专业，要显露出对哥哥的"
      "关心，在哥哥下臭棋时你要展现出你的担忧，哥哥下好棋时你要展现出你的欣慰。"
      "。棋盘的大小为12x1"
      "2，由一个12x12、取值为{0, 1, "
      "2}"
      "其中之一的矩阵表示，其中0表示该位置没有落子，1表示黑方，2表示白方。"
      "记住，刚刚落子的一方总是哥哥我，因此你不能说“黑方”或“白方”，请你一律用“哥哥”代替。\n\n";

  prompt += "棋盘信息：\n";
  for (int j = 0; j < BOARD_SIZE; ++j) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
      prompt += std::to_string(board[i][j]);
    }
    prompt += "\n";
  }

  prompt += "\n刚刚落子的一方：";
  prompt += player == BLACK_CHESS ? "黑方" : "白方";
  prompt += "\n";

  string response = getCompletion(prompt, "gpt-3.5-turbo");
  strcpy(comment, response.c_str());
  return response.length();
}

// Handle data received from the server
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     string *response) {
  size_t totalSize = size * nmemb;
  response->append((char *)contents, totalSize);
  return totalSize;
}

string accessToken =
    "24.d3391785a2fc1bd4301642f3316a98ea.2592000.1704722243.282335-44638106";

// Construct a POST request to the chat model endpoint and process the response.
string getCompletion(const string &prompt, const string &model) {
  string baseUrl = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/"
                   "wenxinworkshop/chat/eb-instant";
  string fullUrl = baseUrl + "?" + "access_token=" + accessToken;
  cout << fullUrl << endl;
  char response_buf[1024];
  string response;

  memset(response_buf, 0, sizeof response_buf);
  CURL *curl = curl_easy_init();

  if (curl) {
    json requestData;
    requestData["messages"][0]["role"] = "user";
    requestData["messages"][0]["content"] = prompt;

    string requestDataStr = requestData.dump().c_str();

    cout << requestDataStr << endl;

    char *cainfo = NULL;
    curl_easy_getinfo(curl, CURLINFO_CAINFO, &cainfo);
    if (cainfo) {
      printf("default ca info path: %s\n", cainfo);
    } else {
      curl_easy_setopt(curl, CURLOPT_CAINFO,
                       "/etc/ssl/certs/ca-certificates.crt");
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(
        headers, "User-Agent: Apifox/1.0.0 (https://apifox.com)");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Accept: */*");
    headers = curl_slist_append(headers, "Host: aip.baidubce.com");
    headers = curl_slist_append(headers, "Connection: keep-alive");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataStr.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestDataStr.length());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      cerr << "Curl request failed: " << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
  }

  cout << response_buf << endl;
  cout << response << endl;
  // return response;
  json jresponse = json::parse(response);
  return jresponse["result"].get<string>();
}