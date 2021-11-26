#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>
using namespace std;

struct expense{
    char date[20];      //日期
    char category;      //分類
    int amount;         //金額
    char payment;       //付款方式
    char memo[40];      //備註
};

//日期由進到遠
bool datecmp(expense x, expense y){
    return strcmp(x.date, y.date) > 0;
}

void print_data(expense v){
    map<char, string> map_category;
    map_category['1'] = "飲食";
    map_category['2'] = "雜貨";
    map_category['3'] = "交通";
    map_category['4'] = "學習";
    map_category['5'] = "娛樂";
    map_category['6'] = "繳費";
    map_category['7'] = "其他";

    map<char, string> map_payment;
    map_payment['1'] = "現金";
    map_payment['2'] = "信用卡";

    cout << "消費日期: " << v.date << endl;
    cout << "消費類別: " << map_category[v.category] << endl;
    cout << "消費金額: " << v.amount << endl;
    cout << "付款方式: " << map_payment[v.payment] << endl;
    cout << "備註: " << v.memo << endl;
    cout << "================" << endl << endl;
}

int main(){
    map<char, string> map_category;
    map_category['1'] = "飲食";
    map_category['2'] = "雜貨";
    map_category['3'] = "交通";
    map_category['4'] = "學習";
    map_category['5'] = "娛樂";
    map_category['6'] = "繳費";
    map_category['7'] = "其他";

    map<char, string> map_payment;
    map_payment['1'] = "現金";
    map_payment['2'] = "信用卡";

    expense E;
    vector<expense> v;
    vector<expense>::iterator it;
    char file_name[20], extension[] = ".txt", full_file_name[40];
    char op, check;
    char find_date[20];
    int find_amount, max_amount;
    int n=0, found=0, action=0;
    FILE *file;

    cout << "=== 歡迎使用記帳本 ===" << endl;
    cout << "請輸入您的帳號: ";
    cin >> file_name;
    strcpy(full_file_name, file_name);
    strcat(full_file_name, extension);
    //開檔，讀取n共有幾筆
    file = fopen(full_file_name, "r");
    if(file!=NULL){
        cout << file_name << "歡迎回來!" << endl;
    }
    else{
        cout << "帳號不存在，第一次使用!" << endl;
    }
    fscanf(file, "%d\n", &n);
    for(int i=0;i<n;i++){
        fscanf(file, "%s\n", &E.date);
        if(feof(file))
            break;
        fscanf(file, "%c\n", &E.category);
        fscanf(file, "%d\n", &E.amount);
        fscanf(file, "%s\n", &E.payment);
        fscanf(file, "%s\n", &E.memo);
        v.push_back(E);
    }


    while(1){
        cout << "<< " << file_name << " 的記帳本 >>" << endl;
        cout << "i. 新增" << endl;
        cout << "d. 刪除" << endl;
        cout << "l. 查看紀錄" << endl;
        cout << "s. 儲存變更" << endl;
        cout << "q. 離開" << endl;
        cout << ">";

        cin >> op;
        cin.ignore();
        switch(op){
        case 'i':
            cout << "消費日期(格式YYYY/MM/DD)" << endl << "> ";
            cin >> E.date;

            while(1){
                cout << "消費種類: (1)飲食 (2)雜貨 (3)交通 (4)學習 (5)娛樂 (6)繳費 (7)其他" << endl << "> ";
                cin >> E.category;
                if(E.category=='1' || E.category=='2' || E.category=='3' || E.category=='4' ||
                   E.category=='5' || E.category=='6' || E.category=='7'){
                    break;
                }
                else{
                    cout << "輸入錯誤! 請重新輸入" << endl;
                }
            }

            cout << "消費金額: ";
            cin >> E.amount;

            while(1){
                cout << "付款方式: (1)現金 (2)信用卡" << endl << "> ";
                cin >> E.payment;
                if(E.payment=='1' || E.payment=='2'){
                    break;
                }
                else{
                    cout << "輸入錯誤! 請重新輸入" << endl;
                }
            }

            cout << "備註: ";
            cin.ignore();
            cin.getline(E.memo, 40);


            v.push_back(E);
            sort(v.begin(), v.end(), datecmp);
            cout << "新增成功!" <<endl;
            n++;

            break;

        case 'd':
            found = 0;
            cout << "請輸入該消費紀錄的日期: ";
            cin >> find_date;
            //列出該日期的所有帳目
            for(it=v.begin();it<v.end();it++){
                if(strcmp(it->date, find_date) == 0){
                    cout << "消費日期: " << it->date << endl;
                    cout << "消費類別: " << map_category[it->category] << endl;
                    cout << "消費金額: " << it->amount << endl;
                    cout << "付款方式: " << map_payment[it->payment] << endl;
                    cout << "備註: " << it->memo << endl;
                    cout << "================" << endl << endl;
                }
            }
            cout << "請輸入要該消費紀錄的金額: ";
            cin >> find_amount;
            for(it=v.begin();it<v.end();it++){
                if(strcmp(it->date, find_date) == 0 && (it->amount == find_amount)){
                    v.erase(it);
                    found = 1;
                    break;
                }
            }
            if(found)
                cout << "刪除成功!" << endl;
            else
                cout << "刪除失敗!" << endl;
            n--;
            break;

        case 'l':
            //sort(v.begin(), v.end(), datecmp);
            while(1){
                action = 0;
                cout << "(1)過去所有消費紀錄 (2)某月份消費紀錄 (3)歷史最高消費" << endl << "> ";
                cin >> check;
                if(check=='1' || check=='2' || check=='3'){
                    switch(check){
                        case '1':
                            for_each(v.begin(), v.end(), print_data);
                            action = 1;
                            break;
                        case '2':
                            found = 0;
                            cout << "請輸入月份(格式YYYY/MM)" << endl << "> ";
                            cin >> find_date;
                            //列出該日期的所有帳目
                            for(it=v.begin();it<v.end();it++){
                                //比較日期字串，年月相同者，比較長度依find_date
                                if(strncmp(it->date, find_date, strlen(find_date)) == 0){
                                    cout << "消費日期: " << it->date << endl;
                                    cout << "消費類別: " << map_category[it->category] << endl;
                                    cout << "消費金額: " << it->amount << endl;
                                    cout << "付款方式: " << map_payment[it->payment] << endl;
                                    cout << "備註: " << it->memo << endl;
                                    cout << "================" << endl << endl;
                                    found = 1;
                                }
                            }
                            if(!found)
                                cout << "該月份無消費紀錄" <<endl;
                            action = 1;
                            break;
                        case '3':
                            max_amount = 0;
                            for(it=v.begin();it<v.end();it++){
                                if(it->amount > max_amount){
                                    max_amount = it->amount;
                                }
                            }
                            for(it=v.begin();it<v.end();it++){
                                if(it->amount == max_amount){
                                    cout << "消費日期: " << it->date << endl;
                                    cout << "消費類別: " << map_category[it->category] << endl;
                                    cout << "消費金額: " << it->amount << endl;
                                    cout << "付款方式: " << map_payment[it->payment] << endl;
                                    cout << "備註: " << it->memo << endl;
                                    cout << "================" << endl << endl;
                                }
                            }
                            action = 1;
                            break;
                    }
                }
                else{
                    cout << "輸入錯誤! 請重新輸入" << endl;
                }
                if(action==1){
                    break;
                }
            }
            break;

        case 's':
            file = fopen(full_file_name, "w");
            fprintf(file, "%d\n", n);
            for(it=v.begin();it<v.end();it++){
                fprintf(file, "%s\n", it->date);
                fprintf(file, "%c\n", it->category);
                fprintf(file, "%d\n", it->amount);
                fprintf(file, "%c\n", it->payment);
                fprintf(file, "%s\n", it->memo);
            }
            cout << "儲存成功!" << endl;
            break;
        case 'q':
            fclose(file);
            cout << "已登出!" << endl;
            return 0;
        default:
            break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}
