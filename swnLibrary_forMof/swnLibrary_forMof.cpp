#include <iostream>
#include "swnLibrary.h"

int main()
{
    JSON jobj = FileAction::ReadJSON("data.json");

    // JSONオブジェクトからJSON文字列をダンプ:
    std::cout << "\nJSONをダンプ: " << jobj.dump() << std::endl; // 整形無しで出力
    // JSONオブジェクトからプロパティ値を取得:
    std::cout << "\njobj[\"str\"]の値を取得: " << jobj["str"] << std::endl;
    FileAction::WriteNew("output.txt", jobj["str"]);
    // JSONオブジェクトのプロパティ値を更新:
    jobj["str"] = "string aaaaaaaaaaaaa";
    jobj.erase("hoge"); // hogeプロパティを削除
    jobj["num"] = 999999.999999;
    jobj["isFoo"] = true;
    jobj["person"]["surname"] = "SUZUKI"; // person.surnameを変更
    jobj["person"]["age"] = 20; // person.ageという新しいプロパティを追加
    jobj["person"]["favorites"].push_back("banana"); // 配列に値を追加
    // JSONオブジェクトからJSON文字列を整形してダンプ:
    std::cout << "\n値変更後のJSONを整形してダンプ: " << jobj.dump(2) << std::endl;


    return 0;

    std::string path = "text.txt";

    FileAction::WriteNew(path, "hello world");

    std::string read = FileAction::Read(path);
    std::cout << read;
}
