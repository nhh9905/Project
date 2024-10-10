//Created by nhh
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <map>
#include <variant>
#define ll long long
#define NAME "bai1"
using namespace std;

//ham sinh ngau nhien
template <typename T>
T Rand(T l, T r) {
    static random_device rd;
    static mt19937 gen(rd());
    if constexpr (is_integral_v<T>) {
        uniform_int_distribution<T> dis(l, r);
        return dis(gen);
    } else if constexpr (is_floating_point_v<T>) {
        uniform_real_distribution<T> dis(l, r);
        return dis(gen);
    }
    return T();
}

//copy kq file source sang file dest
void copyFile(const string& sourceFile, const string& destFile) {
    ifstream source(sourceFile);
    ofstream dest(destFile);
    dest << source.rdbuf();
    source.close();
    dest.close();
}

//khai bao
bool numofTests, existArray;
int NFile, aTest, bTest, numofInp, inpType[105], numofArray, arrayType[105], sizeofArray[105], hang[105], cot[105];
int asizeArray[105], bsizeArray[105], ahang[105], bhang[105], acot[105], bcot[105], astringLen[105], bstringLen[105];
vector<variant<int, ll, char, double>> aArray(105), bArray(105), aInp(105), bInp(105);
variant<int> stringlen[105];

//Cac cau hoi de sinh test
void Question() {
    cout << "Ban muon bao nhieu file testcase: "; cin >> NFile;
    cout << "+------------------------------------------------+" << endl;
    cout << "| Hay tra loi cac cau hoi duoi day de sinh input |" << endl;
    cout << "+------------------------------------------------+" << endl;
    cout << "==================================================" << endl;
    cout << "Co test t hay khong? (1: Co; 0: Khong) "; cin >> numofTests;

    //neu ton tai test t
    if (numofTests) {
        cout << endl << "**************************";
        cout << endl << "t nam trong khoang: [a, b]";
        cout << endl << "a = "; cin >> aTest;
        cout << "b = "; cin >> bTest;
        cout << "**************************";
    }
    cout << endl << "==================================================";
    cout << endl << "Moi test co may input co dinh (khong tinh kich thuoc mang): "; cin >> numofInp;
    cout << "******************************" << endl;
    cout << endl << "------------------------------";
    cout << endl << "| Input co kieu du lieu nao? |";
    cout << endl << "| 1. int                     |";
    cout << endl << "| 2. long long               |";
    cout << endl << "| 3. double                  |";
    cout << endl << "| 4. char                    |";
    cout << endl << "| 5. string                  |";
    cout << endl << "------------------------------";
    cout << endl << "******************************" << endl;

    //nhap kieu du lieu cho input
    for (int i = 1; i <= numofInp; i++) {
        if (i != 1)
            cout << endl;
        cout << "Nhap kieu du lieu cua input " << i << ": "; cin >> inpType[i];
        if (inpType[i] == 5) {
            cout << "Khoang gia tri cua do dai chuoi thu " << i << ":" << endl;
            cout << "a = "; cin >> astringLen[i];
            cout << "b = "; cin >> bstringLen[i];
            continue;
        }
        cout << "Khoang gia tri cua input " << i << ": [a, b]";
        cout << endl << "a = ";
        if (inpType[i] == 1) {
            int value; cin >> value;
            aInp[i] = value;
        }
        if (inpType[i] == 2) {
            ll value; cin >> value;
            aInp[i] = value;
        }
        if (inpType[i] == 3) {
            double value; cin >> value;
            aInp[i] = value;
        }
        if (inpType[i] == 4) {
            char value; cin >> value;
            aInp[i] = value;
        }
        
        cout << "b = ";
        if (inpType[i] == 1) {
            int value; cin >> value;
            bInp[i] = value;
        }
        if (inpType[i] == 2) {
            ll value; cin >> value;
            bInp[i] = value;
        }
        if (inpType[i] == 3) {
            double value; cin >> value;
            bInp[i] = value;
        }
        if (inpType[i] == 4) {
            char value; cin >> value;
            bInp[i] = value;
        }
    }
    if (numofInp)
        cout << "==================================================";

    cout << endl << "Trong input co mang khong? (1: Co; 0: Khong) "; cin >> existArray;
    //neu ton tai mang
    if (existArray) {
        cout << endl << "Co tat ca bao nhieu mang: "; cin >> numofArray;
        cout << endl << "Hay chon kieu mang:";
        cout << endl << "1. Mang 1 chieu kieu int";
        cout << endl << "2. Mang 1 chieu kieu long long";
        cout << endl << "3. Mang 1 chieu kieu double";
        cout << endl << "4. Mang 1 chieu kieu char";
        cout << endl << "5. Mang 2 chieu kieu int";
        cout << endl << "6. Mang 2 chieu kieu long long";
        cout << endl << "7. Mang 2 chieu kieu double";
        cout << endl << "8. Mang 2 chieu kieu char" << endl;
        for (int i = 1; i <= numofArray; i++) {
            cout << "Nhap kieu mang thu " << i << ": "; cin >> arrayType[i];
            if (arrayType[i] <= 4) {
                cout << "Khoang gia tri cua kich thuoc mang thu " << i << ":" << endl;
                cout << "a = "; cin >> asizeArray[i];
                cout << "b = "; cin >> bsizeArray[i];
            }
            else {
                cout << "Khoang gia tri so hang cua mang thu " << i << ":" << endl;
                cout << "a = "; cin >> ahang[i];
                cout << "b = "; cin >> bhang[i];
                cout << "Khoang gia tri so cot cua mang thu " << i << ":" << endl;
                cout << "a = "; cin >> acot[i];
                cout << "b = "; cin >> bcot[i];
            }
            cout << "Khoang gia tri cac phan tu trong mang: [a, b]";
            cout << endl << "a = ";
            if (arrayType[i] == 1 || arrayType[i] == 5) {
                int value; cin >> value;
                aArray[i] = value;
            }
            if (arrayType[i] == 2 || arrayType[i] == 6) {
                ll value; cin >> value;
                aArray[i] = value;
            }
            if (arrayType[i] == 3 || arrayType[i] == 7) {
                double value; cin >> value;
                aArray[i] = value;
            }
            if (arrayType[i] == 4 || arrayType[i] == 8) {
                char value; cin >> value;
                aArray[i] = value;
            }
            
            cout << "b = ";
            if (arrayType[i] == 1 || arrayType[i] == 5) {
                int value; cin >> value;
                bArray[i] = value;
            }
            if (arrayType[i] == 2 || arrayType[i] == 6) {
                ll value; cin >> value;
                bArray[i] = value;
            }
            if (arrayType[i] == 3 || arrayType[i] == 7) {
                double value; cin >> value;
                bArray[i] = value;
            }
            if (arrayType[i] == 4 || arrayType[i] == 8) {
                char value; cin >> value;
                bArray[i] = value;
            }
        }
    }
}

//Sinh test
void MakeTest(int iTest) {
    ofstream inpFile(NAME ".inp");
    variant<int> t;
    vector<variant<int, ll, double, char>> n(105), a(1005);

    //sinh so luong test
    if (numofTests) {
        t = Rand(aTest, bTest);
        inpFile << get<int>(t) << endl;
    }
    else
        t = 1;

    //sinh input co dinh
    for (int k = 1; k <= get<int>(t); k++) {
        for (int i = 1; i <= numofInp; i++) {
            if (inpType[i] == 1) {
                n[i] = Rand(get<int>(aInp[i]), get<int>(bInp[i]));
                inpFile << get<int>(n[i]) << " ";
            }
            if (inpType[i] == 2) {
                n[i] = Rand(get<ll>(aInp[i]), get<ll>(bInp[i]));
                inpFile << get<ll>(n[i]) << " ";
            }
            if (inpType[i] == 3) {
                n[i] = Rand(get<double>(aInp[i]), get<double>(bInp[i]));
                inpFile << get<double>(n[i]) << " ";
            }
            if (inpType[i] == 4) {
                n[i] = Rand(get<char>(aInp[i]), get<char>(bInp[i]));
                inpFile << get<char>(n[i]) << " ";
            }
            if (inpType[i] == 5) {
                stringlen[i] = Rand(astringLen[i], bstringLen[i]);
                for (int j = 0; j < get<int>(stringlen[i]); j++) {
                    variant<char> value = Rand('a', 'z');
                    inpFile << get<char>(value);
                }
                inpFile << " ";
            }
        }
        if (numofInp)
            inpFile << endl;
        
        //sinh mang
        if (existArray) {
            for (int i = 1; i <= numofArray; i++) {
                //mang 1 chieu
                if (arrayType[i] <= 4) {
                    sizeofArray[i] = Rand(asizeArray[i], bsizeArray[i]);
                    inpFile << sizeofArray[i] << endl;
                    for (int j = 1; j <= sizeofArray[i]; j++) {
                        if (arrayType[i] == 1) {
                            a[j] = Rand(get<int>(aArray[i]), get<int>(bArray[i]));
                            inpFile << get<int>(a[j]) << " ";
                        }
                        if (arrayType[i] == 2) {
                            a[j] = Rand(get<ll>(aArray[i]), get<ll>(bArray[i]));
                            inpFile << get<ll>(a[j]) << " ";
                        }
                        if (arrayType[i] == 3) {
                            a[j] = Rand(get<double>(aArray[i]), get<double>(bArray[i]));
                            inpFile << get<double>(a[j]) << " ";
                        }
                        if (arrayType[i] == 4) {
                            a[j] = Rand(get<char>(aArray[i]), get<char>(bArray[i]));
                            inpFile << get<char>(a[j]) << " ";
                        }
                    }
                }
                //mang 2 chieu
                else {
                    hang[i] = Rand(ahang[i], bhang[i]);
                    cot[i] = Rand(acot[i], bcot[i]);
                    inpFile << hang[i] << " " << cot[i] << endl;
                    for (int l = 1; l <= hang[i]; l++) {
                        for (int r = 1; r <= cot[i]; r++) {
                            if (arrayType[i] == 5) {
                                a[r] = Rand(get<int>(aArray[i]), get<int>(bArray[i]));
                                inpFile << get<int>(a[r]) << " ";
                            }
                            if (arrayType[i] == 6) {
                                a[r] = Rand(get<ll>(aArray[i]), get<ll>(bArray[i]));
                                inpFile << get<ll>(a[r]) << " ";
                            }
                            if (arrayType[i] == 7) {
                                a[r] = Rand(get<double>(aArray[i]), get<double>(bArray[i]));
                                inpFile << get<double>(a[r]) << " ";
                            }
                            if (arrayType[i] == 8) {
                                a[r] = Rand(get<char>(aArray[i]), get<char>(bArray[i]));
                                inpFile << get<char>(a[r]) << " ";
                            }
                        }
                        inpFile << endl;
                    }
                }
                inpFile << endl;
            }
        }
    }
    inpFile.close();
    copyFile(NAME ".inp", to_string(iTest) + ".inp");
}

int main() {
    srand(time(NULL));
    Question();
    for (int i = 1; i <= NFile; i++) {
        MakeTest(i);
        //ko co freopen
        system(NAME "_trau.exe <" NAME ".inp> " NAME ".ans");
        system(NAME ".exe <" NAME ".inp> " NAME ".out");

        copyFile(NAME ".out", to_string(i) + ".out");

        //so sanh kq 2 file out va ans
        if (system("fc " NAME ".out " NAME ".ans") != 0) {
            cout << "Test " << i << ": WRONG\n";
            return 0;
        }
        cout << "Test " << i << ": CORRECT\n";
    }
}