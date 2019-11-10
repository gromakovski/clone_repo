#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"

#include <iostream>

// DOM vs SAX models

int main() {
    auto json = "{\"login\":\"admin\",\"password\":\"admin\"}";

    auto doc = rapidjson::Document{};
    doc.Parse(json);
    std::cout << doc["login"].GetString() << std::endl;

    for (auto itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {

        std::cout << itr->name.GetString() << ": " << itr->name.GetString() << std::endl;
    }

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartObject();
    writer.Key("message");
    writer.String("OK");
    writer.Key("success");
    writer.Bool(true);
    writer.Key("extra");
    writer.Null();
    writer.Key("error");
    writer.Uint(0);
    writer.Key("elapsed");
    writer.Double(0.193);
    writer.Key("result");
    writer.StartArray();
    for (auto i = 0; i < 4; i++)
        writer.Uint(i);
    writer.EndArray();
    writer.EndObject();

    std::cout << s.GetString() << std::endl;

    return 0;
}